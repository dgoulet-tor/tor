/* Copyright (c) 2017-2019, The Tor Project, Inc. */
/* See LICENSE for licensing information */

/**
 * \file lttng.h
 * \brief Macros for debugging our event-trace support.
 **/

#ifndef TOR_TRACE_LTTNG_H
#define TOR_TRACE_LTTNG_H

#include <lttng/tracepoint.h>

#include "providers.h"

#undef tor_trace
#define tor_trace(subsystem, event_name, args...) \
  tor_trace_##subsystem##_##event_name(args)

/*
 * Tracepoints.
 */

#define tor_trace_cell_inbuf(cell) \
  tracepoint(tor_cell, inbuf, (cell))

#define tor_trace_cell_outbuf(cell) \
  tracepoint(tor_cell, outbuf, (cell))

#define tor_trace_cell_flush(cell_id, cell_cmd, circ_id) \
  tracepoint(tor_cell, flush, (cell_id), (cell_cmd), (circ_id))

#define tor_trace_cell_queue(cell) \
  tracepoint(tor_cell, queue, (cell))

#define tor_trace_cell_error_outbuf(cell, reason) \
  tracepoint(tor_cell, error_outbuf, (cell), (reason))

#define tor_trace_cell_error_flush(reason) \
  tracepoint(tor_cell, error_flush, (reason))

#define tor_trace_cell_recognized(cell) \
  tracepoint(tor_cell, recognized, (cell))

/* HS Client Tracepoints. */

#define tor_trace_hs_client_launch_circ(circ) \
  tracepoint(tor_hs_client, launch_circ, (circ))

#define tor_trace_hs_client_intro_opened(circ) \
  tracepoint(tor_hs_client, intro_opened, (circ))

#define tor_trace_hs_client_intro_established(circ, status) \
  tracepoint(tor_hs_client, intro_established, (circ), (status))

#define tor_trace_hs_client_rendezvous_opened(circ) \
  tracepoint(tor_hs_client, rendezvous_opened, (circ))

#define tor_trace_hs_client_rendezvous_established(circ) \
  tracepoint(tor_hs_client, rendezvous_established, (circ))

#define tor_trace_hs_client_rendezvous2(circ) \
  tracepoint(tor_hs_client, rendezvous2, (circ))

#define tor_trace_hs_client_store_desc(desc) \
  tracepoint(tor_hs_client, store_desc, (desc))

#define tor_trace_hs_client_circ_timeout(circ) \
  tracepoint(tor_hs_client, circ_timeout, (circ))

/* HS Service Tracepoints. */

#define tor_trace_hs_service_desc_cant_upload(reason, num_ips, upload_ts, \
                                              is_next) \
  tracepoint(tor_hs_service, desc_cant_upload, (reason), (num_ips), \
             (upload_ts), (is_next))

#define tor_trace_hs_service_desc_upload(num_ips, upload_ts, is_next) \
  tracepoint(tor_hs_service, desc_upload, (num_ips), (upload_ts), (is_next))

/* Circuit Tracepoints. */

#define tor_trace_circuit_establish(circ) \
  tracepoint(tor_circuit, establish, (circ))

#define tor_trace_circuit_cannibalized(circ) \
  tracepoint(tor_circuit, cannibalized, (circ))

#define tor_trace_circuit_timeout(circ, cutoff) \
  tracepoint(tor_circuit, timeout, (circ), (cutoff))

#define tor_trace_circuit_idle_timeout(circ) \
  tracepoint(tor_circuit, idle_timeout, (circ))

#define tor_trace_circuit_about_to_free_origin(circ) \
  tracepoint(tor_circuit, about_to_free_origin, (circ))

#define tor_trace_circuit_change_purpose(circ, new, old) \
  tracepoint(tor_circuit, change_purpose, (circ), (new), (old))

#define tor_trace_circuit_change_state(circ, new, old) \
  tracepoint(tor_circuit, change_state, (circ), (new), (old))

#define tor_trace_circuit_first_onion_skin(circ, hop) \
  tracepoint(tor_circuit, first_onion_skin, (circ), (hop))

#define tor_trace_circuit_intermediate_onion_skin(circ, hop) \
  tracepoint(tor_circuit, intermediate_onion_skin, (circ), (hop))

#define tor_trace_circuit_opened(circ) \
  tracepoint(tor_circuit, opened, (circ))

#define tor_trace_circuit_mark_for_close(circ) \
  tracepoint(tor_circuit, mark_for_close, (circ))

#endif /* !defined(TOR_TRACE_LTTNG_H) */
