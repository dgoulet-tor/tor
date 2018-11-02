/* Copyright (c) 2018, The Tor Project, Inc. */
/* See LICENSE for licensing information */

#include "core/or/or.h"

/** Stats reporter protocols that are supported by
 *  stats_reporter_connection_t.
 **/
typedef enum {
  /** The Graphite stats reporting protocol. */
  STATS_REPORTER_PROTOCOL_GRAPHITE,

  /** An unknown stats reporting protocol. Used for different error
   * conditions. */
  STATS_REPORTER_PROTOCOL_UNKNOWN
} stats_reporter_protocol_t;

/** Subtype of connection_t for a connection to a stats reporter service. */
struct stats_reporter_connection_t {
  connection_t base_;

  /** The protocol used for the given connection. */
  stats_reporter_protocol_t protocol;
};
