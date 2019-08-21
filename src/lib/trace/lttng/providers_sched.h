/* Copyright (c) 2019, The Tor Project, Inc. */
/* See LICENSE for licensing information */

/**
 * \file providers.h
 * \brief Header file for Tor event LTTng UST tracing.
 **/

#undef TRACEPOINT_PROVIDER
#define TRACEPOINT_PROVIDER tor_sched

#undef TRACEPOINT_INCLUDE
#define TRACEPOINT_INCLUDE "./lib/trace/lttng/providers_sched.h"

#if !defined(_TRACEPOINT_TOR_SCHED) || defined(TRACEPOINT_HEADER_MULTI_READ)
#define _TRACEPOINT_TOR_SCHED

#include <lttng/tracepoint.h>

#include "core/or/channel.h"

#include "core/or/connection_st.h"

TRACEPOINT_EVENT(tor_sched, queue,
  TP_ARGS(const channel_t *, chan, unsigned int, n_cells),
  TP_FIELDS(
    ctf_integer(uint64_t, chan_id, chan->global_identifier)
    ctf_integer(unsigned int, chan_state, chan->state)
    ctf_integer(unsigned int, chan_sched_state, chan->scheduler_state)
    ctf_integer(unsigned int, chan_n_cells, n_cells)
  )
)

#endif /* _TRACEPOINT_TOR_SCHED */

#include <lttng/tracepoint-event.h>
