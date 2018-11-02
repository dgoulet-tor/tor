/* Copyright (c) 2018, The Tor Project, Inc. */
/* See LICENSE for licensing information */

/**
 * \file stats_reporter.h
 * \brief Header file for stats_reporter.c.
 **/

#ifndef TOR_STATS_REPORTER_H
#define TOR_STATS_REPORTER_H

#include "core/or/connection_st.h"

#include "stats_reporter_connection_st.h"

static inline stats_reporter_connection_t *
TO_STATS_REPORTER_CONN(connection_t *c)
{
  tor_assert(c->magic == STATS_REPORTER_CONNECTION_MAGIC);
  return DOWNCAST(stats_reporter_connection_t, c);
}

int connection_stats_reporter_process_inbuf(stats_reporter_connection_t *);
int connection_stats_reporter_finished_flushing(stats_reporter_connection_t *);
int connection_stats_reporter_reached_eof(stats_reporter_connection_t *);

int stats_reporter_emit_events(time_t now);
int stats_reporter_add_from_config(const tor_addr_t *addr, uint16_t port,
                                   const char *protocol);
const char *stats_reporter_protocol_string(stats_reporter_protocol_t protocol);
stats_reporter_protocol_t stats_reporter_protocol(const char *protocol);
int stats_reporter_is_valid_protocol(const char *protocol);
int stats_reporter_is_valid_prefix(const char *prefix);

#ifdef STATS_REPORTER_PRIVATE

STATIC const char *stats_reporter_graphite_tags(void);

#endif /* STATS_REPORTER_PRIVATE. */

#endif /* TOR_STATS_REPORTER_H */

