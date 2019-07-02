/* Copyright (c) 2019, The Tor Project, Inc. */
/* See LICENSE for licensing information */

/**
 * \file hs_dos.c
 * \brief Implement denial of service mitigation for the onion service
 *        subsystem.
 *
 * This module defenses:
 *
 * - Introduction Rate Limiting: If enabled by the consensus, an introduction
 *   point will rate limit client introduction towards the service (INTRODUCE2
 *   cells). It uses a token bucket model with a rate and burst per second.
 *
 *   Proposal 305 will expand this module by allowing an operator to define
 *   these values into the ESTABLISH_INTRO cell. Not yet implemented.
 **/

#define HS_DOS_PRIVATE

#include "core/or/or.h"
#include "app/config/config.h"

#include "core/or/circuitlist.h"

#include "feature/hs/hs_circuitmap.h"
#include "feature/nodelist/networkstatus.h"
#include "feature/relay/routermode.h"

#include "lib/evloop/token_bucket.h"

#include "hs_dos.h"

/* Default value of the allowed INTRODUCE2 cell rate per second. Above that
 * value per second, the introduction is denied. */
#define HS_DOS_INTRODUCE_DEFAULT_CELL_RATE_PER_SEC 25

/* Default value of the allowed INTRODUCE2 cell burst per second. This is the
 * maximum value a token bucket has per second. We thus allow up to this value
 * of INTRODUCE2 cell per second but the bucket is refilled by the rate value
 * but never goes above that burst value. */
#define HS_DOS_INTRODUCE_DEFAULT_CELL_BURST_PER_SEC 200

/* Default value of the consensus parameter enabling or disabling the
 * introduction DoS defense. Disabled by default. */
#define HS_DOS_INTRODUCE_ENABLED_DEFAULT 0

/* Consensus parameters. */
static uint32_t hs_dos_introduce_rate_per_sec =
  HS_DOS_INTRODUCE_DEFAULT_CELL_RATE_PER_SEC;
static uint32_t hs_dos_introduce_burst_per_sec =
  HS_DOS_INTRODUCE_DEFAULT_CELL_BURST_PER_SEC;
static uint32_t hs_dos_introduce_enabled =
  HS_DOS_INTRODUCE_ENABLED_DEFAULT;

static uint32_t
get_param_intro_dos_enabled(const networkstatus_t *ns)
{
  return networkstatus_get_param(ns, "HiddenServiceEnableIntroDoSDefense",
                                 HS_DOS_INTRODUCE_ENABLED_DEFAULT, 0, 1);
}

/* Return the parameter for the introduction rate per sec. */
static uint32_t
get_param_rate_per_sec(const networkstatus_t *ns)
{
  return networkstatus_get_param(ns, "HiddenServiceEnableIntroDoSRatePerSec",
                                 HS_DOS_INTRODUCE_DEFAULT_CELL_RATE_PER_SEC,
                                 0, INT32_MAX);
}

/* Return the parameter for the introduction burst per sec. */
static uint32_t
get_param_burst_per_sec(const networkstatus_t *ns)
{
  return networkstatus_get_param(ns, "HiddenServiceEnableIntroDoSBurstPerSec",
                                 HS_DOS_INTRODUCE_DEFAULT_CELL_BURST_PER_SEC,
                                 0, INT32_MAX);
}

/* Go over all introduction circuit relay side and adjust their rate/burst
 * values using the global parameters. This is called right after the
 * consensus parameters might have changed. */
static void
update_intro_circuits(void)
{
  /* Returns all HS version intro circuits. */
  smartlist_t *intro_circs = hs_circuitmap_get_all_intro_circ_relay_side();

  SMARTLIST_FOREACH_BEGIN(intro_circs, circuit_t *, circ) {
    /* Adjust the rate/burst value that might have changed. */
    token_bucket_ctr_adjust(&TO_OR_CIRCUIT(circ)->introduce2_bucket,
                            hs_dos_get_intro2_rate(),
                            hs_dos_get_intro2_burst());
  } SMARTLIST_FOREACH_END(circ);

  smartlist_free(intro_circs);
}

/* Set consensus parameters. */
static void
set_consensus_parameters(const networkstatus_t *ns)
{
  hs_dos_introduce_rate_per_sec = get_param_rate_per_sec(ns);
  hs_dos_introduce_burst_per_sec = get_param_burst_per_sec(ns);
  hs_dos_introduce_enabled = get_param_intro_dos_enabled(ns);

  /* The above might have changed which means we need to go through all
   * introduction circuits (relay side) and update the token buckets. */
  update_intro_circuits();
}

/*
 * Public API.
 */

/* Return the INTRODUCE2 cell rate per second. */
uint32_t
hs_dos_get_intro2_rate(void)
{
  return hs_dos_introduce_rate_per_sec;
}

/* Return the INTRODUCE2 cell burst per second. */
uint32_t
hs_dos_get_intro2_burst(void)
{
  return hs_dos_introduce_burst_per_sec;
}

/* Called when the consensus has changed. We might have new consensus
 * parameters to look at. */
void
hs_dos_consensus_has_changed(const networkstatus_t *ns)
{
  /* No point on updating these values if we are not a public relay that can
   * be picked to be an introduction point. */
  if (!public_server_mode(get_options())) {
    return;
  }

  set_consensus_parameters(ns);
}

/* Return true iff an INTRODUCE2 cell can be sent on the given service
 * introduction circuit. */
bool
hs_dos_can_send_intro2(or_circuit_t *s_intro_circ)
{
  tor_assert(s_intro_circ);

  /* Always allowed if the defense is disabled. */
  if (!hs_dos_introduce_enabled) {
    return true;
  }

  /* Should not happen but if so, scream loudly. */
  if (BUG(TO_CIRCUIT(s_intro_circ)->purpose != CIRCUIT_PURPOSE_INTRO_POINT)) {
    return false;
  }

  /* This is called just after we got a valid and parsed INTRODUCE1 cell. The
   * service has been found and we have its introduction circuit.
   *
   * First, the INTRODUCE2 bucket will be refilled (if any). Then, decremented
   * because we are about to send or not the cell we just got. Finally,
   * evaluate if we can send it based on our token bucket state. */

  /* Refill INTRODUCE2 bucket. */
  token_bucket_ctr_refill(&s_intro_circ->introduce2_bucket,
                          (uint32_t) approx_time());

  /* Decrement the bucket for this valid INTRODUCE1 cell we just got. Don't
   * underflow else we end up with a too big of a bucket. */
  if (token_bucket_ctr_get(&s_intro_circ->introduce2_bucket) > 0) {
    token_bucket_ctr_dec(&s_intro_circ->introduce2_bucket, 1);
  }

  /* Finally, we can send a new INTRODUCE2 if there are still tokens. */
  return token_bucket_ctr_get(&s_intro_circ->introduce2_bucket) > 0;
}

/* Initialize the onion service Denial of Service subsystem. */
void
hs_dos_init(void)
{
  set_consensus_parameters(NULL);
}
