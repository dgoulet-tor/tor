/* Copyright (c) 2019, The Tor Project, Inc. */
/* See LICENSE for licensing information */

/**
 * \file providers.h
 * \brief Header file for Tor event LTTng UST tracing.
 **/

#undef TRACEPOINT_PROVIDER
#define TRACEPOINT_PROVIDER tor_circuit

#undef TRACEPOINT_INCLUDE
#define TRACEPOINT_INCLUDE "./lib/trace/lttng/providers_circuit.h"

#if !defined(_TRACEPOINT_TOR_CIRCUIT_H) || defined(TRACEPOINT_HEADER_MULTI_READ)
#define _TRACEPOINT_TOR_CIRCUIT_H

#include <lttng/tracepoint.h>

#include "core/or/circuitlist.h"
#include "core/or/or.h"
#include "core/or/origin_circuit_st.h"

TRACEPOINT_ENUM(tor_circuit, purpose,
  TP_ENUM_VALUES(
    /* OR Side. */
    ctf_enum_value("OR", CIRCUIT_PURPOSE_OR)
    ctf_enum_value("OR_INTRO_POINT", CIRCUIT_PURPOSE_INTRO_POINT)
    ctf_enum_value("OR_REND_POINT_WAITING", CIRCUIT_PURPOSE_REND_POINT_WAITING)
    ctf_enum_value("OR_REND_ESTABLISHED", CIRCUIT_PURPOSE_REND_ESTABLISHED)

    /* Client Side. */
    ctf_enum_value("C_GENERAL", CIRCUIT_PURPOSE_C_GENERAL)
    ctf_enum_value("C_INTRODUCING", CIRCUIT_PURPOSE_C_INTRODUCING)
    ctf_enum_value("C_INTRODUCE_ACK_WAIT", CIRCUIT_PURPOSE_C_INTRODUCE_ACK_WAIT)
    ctf_enum_value("C_INTRODUCE_ACKED", CIRCUIT_PURPOSE_C_INTRODUCE_ACKED)
    ctf_enum_value("C_ESTABLISH_REND", CIRCUIT_PURPOSE_C_ESTABLISH_REND)
    ctf_enum_value("C_REND_READY", CIRCUIT_PURPOSE_C_REND_READY)
    ctf_enum_value("C_REND_READY_INTRO_ACKED",
                   CIRCUIT_PURPOSE_C_REND_READY_INTRO_ACKED)
    ctf_enum_value("C_REND_JOINED", CIRCUIT_PURPOSE_C_REND_JOINED)
    ctf_enum_value("C_HSDIR_GET", CIRCUIT_PURPOSE_C_HSDIR_GET)

    /* Service Side. */
    ctf_enum_value("S_ESTABLISH_INTRO", CIRCUIT_PURPOSE_S_ESTABLISH_INTRO)
    ctf_enum_value("S_INTRO", CIRCUIT_PURPOSE_S_INTRO)
    ctf_enum_value("S_CONNECT_REND", CIRCUIT_PURPOSE_S_CONNECT_REND)
    ctf_enum_value("S_REND_JOINED", CIRCUIT_PURPOSE_S_REND_JOINED)
    ctf_enum_value("S_HSDIR_POST", CIRCUIT_PURPOSE_S_HSDIR_POST)

    /* Misc. */
    ctf_enum_value("TESTING", CIRCUIT_PURPOSE_TESTING)
    ctf_enum_value("CONTROLER", CIRCUIT_PURPOSE_CONTROLLER)
    ctf_enum_value("PATH_BIAS_TESTING", CIRCUIT_PURPOSE_PATH_BIAS_TESTING)

    /* VanGuard */
    ctf_enum_value("HS_VANGUARDS", CIRCUIT_PURPOSE_HS_VANGUARDS)
  )
)

TRACEPOINT_EVENT(tor_circuit, establish,
  TP_ARGS(const origin_circuit_t *, circ),
  TP_FIELDS(
    ctf_integer(uint32_t, circ_id, circ->global_identifier)
    ctf_enum(tor_circuit, purpose, int, purpose, TO_CIRCUIT(circ)->purpose)
  )
)

TRACEPOINT_EVENT(tor_circuit, cannibalized,
  TP_ARGS(const origin_circuit_t *, circ),
  TP_FIELDS(
    ctf_integer(uint32_t, circ_id, circ->global_identifier)
    ctf_enum(tor_circuit, purpose, int, purpose, TO_CIRCUIT(circ)->purpose)
  )
)

TRACEPOINT_EVENT(tor_circuit, timeout,
  TP_ARGS(const origin_circuit_t *, circ, struct timeval *, tv),
  TP_FIELDS(
    ctf_integer(uint32_t, circ_id, circ->global_identifier)
    ctf_enum(tor_circuit, purpose, int, purpose, TO_CIRCUIT(circ)->purpose)
    ctf_integer(time_t, cutoff_sec, tv->tv_sec)
    ctf_integer(int, cutoff_usec, tv->tv_usec)
  )
)

TRACEPOINT_EVENT(tor_circuit, idle_timeout,
  TP_ARGS(const origin_circuit_t *, circ),
  TP_FIELDS(
    ctf_integer(uint32_t, circ_id, circ->global_identifier)
    ctf_enum(tor_circuit, purpose, int, purpose, TO_CIRCUIT(circ)->purpose)
  )
)

#endif /* _TRACEPOINT_TOR_CIRCUIT_H */

#include <lttng/tracepoint-event.h>
