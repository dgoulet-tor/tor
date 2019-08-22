/* Copyright (c) 2019, The Tor Project, Inc. */
/* See LICENSE for licensing information */

/**
 * \file providers.h
 * \brief Header file for Tor event LTTng UST tracing.
 **/

#undef TRACEPOINT_PROVIDER
#define TRACEPOINT_PROVIDER tor_hs_client

#undef TRACEPOINT_INCLUDE
#define TRACEPOINT_INCLUDE "./lib/trace/lttng/providers_hs.h"

#if !defined(_TRACEPOINT_TOR_HS_CLIENT) || defined(TRACEPOINT_HEADER_MULTI_READ)
#define _TRACEPOINT_TOR_HS_CLIENT

#include "core/or/or.h"
#include "core/or/circuitlist.h"
#include "core/or/origin_circuit_st.h"

#include "feature/hs/hs_ident.h"

#include "trunnel/hs/cell_introduce1.h"

TRACEPOINT_ENUM(tor_hs_client, intro_ack_status,
  TP_ENUM_VALUES(
    ctf_enum_value("SUCCESS", TRUNNEL_HS_INTRO_ACK_STATUS_SUCCESS)
    ctf_enum_value("UNKNOWN_ID", TRUNNEL_HS_INTRO_ACK_STATUS_UNKNOWN_ID)
    ctf_enum_value("BAD_FORMAT", TRUNNEL_HS_INTRO_ACK_STATUS_BAD_FORMAT)
  )
)

TRACEPOINT_EVENT(tor_hs_client, launch_circ,
  TP_ARGS(const origin_circuit_t *, circ),
  TP_FIELDS(
    ctf_integer(uint32_t, circ_id, circ->global_identifier)
  )
)

TRACEPOINT_EVENT(tor_hs_client, intro_opened,
  TP_ARGS(const origin_circuit_t *, circ),
  TP_FIELDS(
    ctf_integer(uint32_t, circ_id, circ->global_identifier)
    ctf_enum(tor_circuit, purpose, int, purpose, TO_CIRCUIT(circ)->purpose)
    ctf_array_hex(char, hs_ident_pk,
                   circ->hs_ident->identity_pk.pubkey, 4)
  )
)

TRACEPOINT_EVENT(tor_hs_client, intro_established,
  TP_ARGS(const origin_circuit_t *, circ, unsigned int, status),
  TP_FIELDS(
    ctf_enum(tor_hs_client, intro_ack_status, unsigned int, status, status)
    ctf_integer(uint32_t, circ_id, circ->global_identifier)
    ctf_array_hex(char, hs_ident_pk,
                   circ->hs_ident->identity_pk.pubkey, 4)
  )
)

TRACEPOINT_EVENT(tor_hs_client, rendezvous_opened,
  TP_ARGS(const origin_circuit_t *, circ),
  TP_FIELDS(
    ctf_integer(uint32_t, circ_id, circ->global_identifier)
    ctf_array_hex(char, hs_ident_pk,
                   circ->hs_ident->identity_pk.pubkey, 4)
    ctf_array_hex(char, rdv_cookie,
                   circ->hs_ident->rendezvous_cookie, 4)
  )
)

TRACEPOINT_EVENT(tor_hs_client, rendezvous_established,
  TP_ARGS(const origin_circuit_t *, circ),
  TP_FIELDS(
    ctf_integer(uint32_t, circ_id, circ->global_identifier)
    ctf_array_hex(char, hs_ident_pk,
                   circ->hs_ident->identity_pk.pubkey, 4)
    ctf_array_hex(char, rdv_cookie,
                   circ->hs_ident->rendezvous_cookie, 4)
  )
)

TRACEPOINT_EVENT(tor_hs_client, rendezvous2,
  TP_ARGS(const origin_circuit_t *, circ),
  TP_FIELDS(
    ctf_integer(uint32_t, circ_id, circ->global_identifier)
    ctf_array_hex(char, hs_ident_pk,
                   circ->hs_ident->identity_pk.pubkey, 4)
    ctf_array_hex(char, rdv_cookie,
                   circ->hs_ident->rendezvous_cookie, 4)
  )
)

TRACEPOINT_EVENT(tor_hs_client, store_desc,
  TP_ARGS(const ed25519_public_key_t *, pk),
  TP_FIELDS(
    ctf_array_hex(char, hs_ident_pk, pk->pubkey, 4)
  )
)

#endif /* _TRACEPOINT_TOR_HS_CLIENT */

#include <lttng/tracepoint-event.h>
