/* Copyright (c) 2019, The Tor Project, Inc. */
/* See LICENSE for licensing information */

/**
 * \file providers.h
 * \brief Header file for Tor event LTTng UST tracing.
 **/

#undef TRACEPOINT_PROVIDER
#define TRACEPOINT_PROVIDER tor_cell

#undef TRACEPOINT_INCLUDE
#define TRACEPOINT_INCLUDE "./lib/trace/lttng/providers_cell.h"

#if !defined(_TRACEPOINT_TOR_CELL) || defined(TRACEPOINT_HEADER_MULTI_READ)
#define _TRACEPOINT_TOR_CELL

#include <lttng/tracepoint.h>

#include "core/or/channel.h"

#include "core/or/cell_queue_st.h"
#include "core/or/cell_st.h"

TRACEPOINT_EVENT(tor_cell, inbuf,
  TP_ARGS(const cell_t *, cell),
  TP_FIELDS(
    ctf_integer(uint32_t, cell_id, cell->id)
    ctf_integer(uint32_t, cell_cmd, cell->command)
    ctf_integer(uint32_t, circ_id, cell->circ_id)
  )
)

TRACEPOINT_EVENT(tor_cell, queue,
  TP_ARGS(const cell_t *, cell),
  TP_FIELDS(
    ctf_integer(uint32_t, cell_id, cell->id)
    ctf_integer(uint32_t, cell_cmd, cell->command)
    ctf_integer(uint32_t, circ_id, cell->circ_id)
  )
)

TRACEPOINT_EVENT(tor_cell, outbuf,
  TP_ARGS(const cell_t *, cell),
  TP_FIELDS(
    ctf_integer(uint32_t, cell_id, cell->id)
    ctf_integer(uint32_t, cell_cmd, cell->command)
    ctf_integer(uint32_t, circ_id, cell->circ_id)
  )
)

TRACEPOINT_EVENT(tor_cell, flush,
  TP_ARGS(uint32_t, cell_id, uint32_t, cell_cmd, uint32_t, circ_id),
  TP_FIELDS(
    ctf_integer(uint32_t, cell_id, cell_id)
    ctf_integer(uint32_t, cell_cmd, cell_cmd)
    ctf_integer(uint32_t, circ_id, circ_id)
  )
)

TRACEPOINT_EVENT(tor_cell, error_outbuf,
  TP_ARGS(const cell_t *, cell, const char *, reason),
  TP_FIELDS(
    ctf_integer(uint32_t, cell_id, cell->id)
    ctf_integer(uint32_t, cell_cmd, cell->command)
    ctf_integer(uint32_t, circ_id, cell->circ_id)
    ctf_string(reason, reason)
  )
)

TRACEPOINT_EVENT(tor_cell, error_flush,
  TP_ARGS(const char *, reason),
  TP_FIELDS(
    ctf_string(reason, reason)
  )
)

TRACEPOINT_EVENT(tor_cell, recognized,
  TP_ARGS(const cell_t *, cell),
  TP_FIELDS(
    ctf_integer(uint32_t, cell_id, cell->id)
    ctf_integer(uint32_t, cell_cmd, cell->command)
    ctf_integer(uint32_t, circ_id, cell->circ_id)
  )
)

#endif /* _TRACEPOINT_TOR_CELL */

#include <lttng/tracepoint-event.h>
