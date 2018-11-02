/* Copyright (c) 2018, The Tor Project, Inc. */
/* See LICENSE for licensing information */

/**
 * \file stats_reporter.c
 * \brief XXX: Write a brief introduction to this module.
 **/

#include <string.h>

#define STATS_REPORTER_PRIVATE

#include "core/or/or.h"

#include "app/config/config.h"

#include "core/mainloop/connection.h"
#include "core/mainloop/mainloop.h"

#include "lib/log/git_revision.h"
#include "lib/net/address.h"
#include "lib/net/socket.h"
#include "lib/smartlist_core/smartlist_core.h"
#include "lib/stats/stats_store.h"

#include "stats_reporter.h"

#define LEGAL_PREFIX_CHARACTERS \
  "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789."

static smartlist_t *connections;

static void connection_printf_to_buf(stats_reporter_connection_t *conn,
                                     const char *format, ...)
  CHECK_PRINTF(2,3);

static void
add_stats_reporter_connection(stats_reporter_connection_t *conn)
{
  tor_assert(conn);

  if (connections == NULL)
    connections = smartlist_new();

  smartlist_add(connections, conn);
}

static void
remove_stats_reporter_connection(stats_reporter_connection_t *conn)
{
  tor_assert(conn);
  smartlist_remove(connections, conn);
}

static void
connection_printf_to_buf(stats_reporter_connection_t *conn,
                         const char *format, ...)
{
  va_list ap;
  char *buf = NULL;
  int len;

  va_start(ap,format);
  len = tor_vasprintf(&buf, format, ap);
  va_end(ap);

  if (len < 0) {
    // LCOV_EXCL_START
    log_err(LD_BUG, "Unable to format string for controller.");
    tor_assert(0);
    // LCOV_EXCL_STOP
  }

  connection_buf_add(buf, (size_t)len, TO_CONN(conn));
  tor_free(buf);
}

int
connection_stats_reporter_process_inbuf(stats_reporter_connection_t *conn)
{
  tor_assert(conn);
  return 0;
}

/**
 * Called when the given <b>conn</b> has no more bytes left in its outbuf.
 **/
int
connection_stats_reporter_finished_flushing(stats_reporter_connection_t *conn)
{
  tor_assert(conn);
  return 0;
}

/**
 * Called when the given <b>conn</b>'s socket is closed.
 **/
int
connection_stats_reporter_reached_eof(stats_reporter_connection_t *conn)
{
  tor_assert(conn);

  log_info(LD_STATS_REPORTER, "Stats reporter connection reached EOF."
                              " Closing.");

  remove_stats_reporter_connection(conn);
  connection_mark_for_close(TO_CONN(conn));

  return 0;
}

/**
 * Emit buffered up events to every stats reporter connection.
 */
int
stats_reporter_emit_events(time_t now)
{
  const char *graphite_tags = stats_reporter_graphite_tags();
  const int granularity = get_options()->StatsReporterGranularity;
  const char *prefix = get_options()->StatsReporterPrefix;
  time_t t = now - (now % granularity);

  const char *key;
  size_t value;

  SMARTLIST_FOREACH_BEGIN(connections, stats_reporter_connection_t *, conn) {
    for (int i = 0; i < STAT_LAST; ++i) {

      /* No updates to our stats entry, continue to the next one. */
      if (! stats_store_is_modified(i))
        continue;

      key = stats_store_key_string(i);
      value = stats_store_get_value(i);

      if (conn->protocol == STATS_REPORTER_PROTOCOL_GRAPHITE) {
        if (prefix == NULL)
          connection_printf_to_buf(conn, "%s%s %zu %ld\n",
                                   key, graphite_tags, value, t);
        else
          connection_printf_to_buf(conn, "%s.%s%s %zu %ld\n",
                                   prefix, key, graphite_tags, value, t);
      }
    }
  } SMARTLIST_FOREACH_END(conn);

  stats_store_reset_all();

  return 0;
}

/**
 * Add a new stats reporter from a StatsReporter entry in torrc.  This function
 * returns 0 on success and a negative value on failure.
 **/
int
stats_reporter_add_from_config(const tor_addr_t *addr, uint16_t port,
                               const char *protocol_str)
{
  stats_reporter_protocol_t protocol;
  stats_reporter_connection_t *conn;

  protocol = stats_reporter_protocol(protocol_str);
  tor_assert(protocol != STATS_REPORTER_PROTOCOL_UNKNOWN);

  log_info(LD_GENERAL, "Succesfully registered stats reporter %s (%s).",
           fmt_addrport(addr, port), stats_reporter_protocol_string(protocol));

  conn = stats_reporter_connection_new(AF_UNSPEC);
  conn->protocol = protocol;

  int socket_error = 0;
  int r = connection_connect(TO_CONN(conn), NULL,
                             addr, port, &socket_error);

  if (r == 0) {
    connection_watch_events(TO_CONN(conn), READ_EVENT | WRITE_EVENT);
    add_stats_reporter_connection(conn);
  }

  return 0;
}

/**
 * Covert a stats_reporter_protocol_t given in <b>protocol</b> to its canonical
 * string representation.
 */
const char *
stats_reporter_protocol_string(stats_reporter_protocol_t protocol)
{
  switch (protocol) {
  case STATS_REPORTER_PROTOCOL_GRAPHITE:
    return "graphite";
  case STATS_REPORTER_PROTOCOL_UNKNOWN:
    return "unknown";
  }

  // LCOV_EXCL_START
  tor_assert(0);
  return "unknown";
  // LCOV_EXCL_STOP
}

/**
 * Convert a given string in <b>protocol</b> to its corresponding
 * stats_reporter_protocol_t instance. Returns STATS_REPORTER_PROTOCOL_UNKNOWN
 * if the input is an unknown stats reporter protocol.
 */

stats_reporter_protocol_t
stats_reporter_protocol(const char *protocol)
{
  if (! strcasecmp(protocol, "graphite"))
    return STATS_REPORTER_PROTOCOL_GRAPHITE;

  return STATS_REPORTER_PROTOCOL_UNKNOWN;
}

/**
 * Check if a given stats reporter protocol given in <b>protocol</b> is valid.
 * Returns 1 on success and otherwise 0.
 */
int
stats_reporter_is_valid_protocol(const char *protocol)
{
  return stats_reporter_protocol(protocol) != STATS_REPORTER_PROTOCOL_UNKNOWN;
}

int
stats_reporter_is_valid_prefix(const char *prefix)
{
  tor_assert(prefix);

  size_t len;
  len = strlen(prefix);
  return len > 0 && strspn(prefix, LEGAL_PREFIX_CHARACTERS) == len;
}

STATIC const char *
stats_reporter_graphite_tags(void)
{
  const or_options_t *options = get_options();

  static char buf[256];
  int written = 0;

#if 0
  /* Add version tag. */
  tor_snprintf(buf + written, sizeof(buf) - written,  ";tor_version=%s",
               VERSION);
  written = strlen(buf);

  /* Add Git commit tag, if it's available. */
  if (strlen(tor_git_revision)) {
    tor_snprintf(buf + written, sizeof(buf) - written, ";tor_git_revision=%s",
                 tor_git_revision);
    written = strlen(buf);
  }
#endif

  /* Add nickname, if it's available. */
  if (options->Nickname) {
    tor_snprintf(buf + written, sizeof(buf) - written, ";nickname=%s",
                 options->Nickname);
    written = strlen(buf);
  }

  return buf;
}

