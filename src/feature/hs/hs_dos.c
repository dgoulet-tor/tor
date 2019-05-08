/* Copyright (c) 2019, The Tor Project, Inc. */
/* See LICENSE for licensing information */

/**
 * \file hs_dos.c
 **/

#define HS_DOS_PRIVATE

#include "core/or/circuitlist.h"

#include "hs_dos.h"

/*
 * Public API.
 */

/* Return true iff an INTRODUCE2 cell can be sent on the given service
 * introduction circuit. */
bool
hs_dos_can_send_intro2(const or_circuit_t *service)
{
  tor_assert(service);
  tor_assert(TO_CIRCUIT(service)->purpose == CIRCUIT_PURPOSE_INTRO_POINT);

  /* The way we do it is by looking if we've reached the maximum amount of
   * in-flight cells on the circuit. If so, we consider that we've received
   * way too much from what the service can handle.
   *
   * If we accept cells that we can't send on the service circuit, we
   * accumulate them to almost infinity and will keep hammering the service
   * long after the client circuits are gone of timed out.
   *
   * In other words, this limit allows the intro point relay to soak up the
   * excess introduction attempts which better protects the network from
   * introduction denial of service and reduces the service load.
   *
   * This won't help service availability per-se but if legit clients try
   * enough, at some point they will get through to a service that is not
   * crumbling under the CPU load of a massive amount of introductions and
   * thus be able to properly rendezvous. */
  return TO_CIRCUIT(service)->package_window > 0;
}
