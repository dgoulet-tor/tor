/* Copyright (c) 2017-2019, The Tor Project, Inc. */
/* See LICENSE for licensing information */

/**
 * \file debug.h
 * \brief Macros for debugging our event-trace support.
 **/

#ifndef TOR_TRACE_LTTNG_H
#define TOR_TRACE_LTTNG_H

#include "providers_cell.h"

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

#endif /* !defined(TOR_TRACE_LTTNG_H) */
