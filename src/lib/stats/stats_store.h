/* Copyright (c) 2018, The Tor Project, Inc. */
/* See LICENSE for licensing information */

/**
 * \file stats_store.h
 * \brief Header file for stats_store.c.
 **/

#ifndef TOR_STATS_STORE_H
#define TOR_STATS_STORE_H

#include "lib/cc/torint.h"
#include "lib/testsupport/testsupport.h"

typedef enum {
  /** Number of allocated bytes. */
  STAT_MALLOC_BYTES,

  /** Number of calls to tor_malloc(). */
  STAT_MALLOC_COUNT,

  /** Number of reallocated bytes. */
  STAT_REALLOC_BYTES,

  /** Number of calls to tor_realloc(). */
  STAT_REALLOC_COUNT,

  /** Number of bytes written on connections. */
  STAT_CONNECTION_WRITTEN,

  /** Number of bytes read on connections. */
  STAT_CONNECTION_READ,

  /** Main loop stats. */
  STAT_MAIN_LOOP_SUCCESS,

  /** DoS subsystem: Rejected cell count. */
  STAT_DOS_REJECTED_CELLS,

  /** DoS subsystem: Number of marked addresses. */
  STAT_DOS_MARKED_ADDRESSES,

  /** DoS subsystem: Rejected address connections. */
  STAT_DOS_REJECTED_ADDRS,

  /** Command: CREATE cells. */
  STAT_COMMAND_CREATE_CELLS_PROCESSED,

  /** Command: CREATED cells. */
  STAT_COMMAND_CREATED_CELLS_PROCESSED,

  /** Command: RELAY cells. */
  STAT_COMMAND_RELAY_CELLS_PROCESSED,

  /** Command: DESTROY cells. */
  STAT_COMMAND_DESTROY_CELLS_PROCESSED,

  /** Onion Handshake: ntor. */
  STAT_HANDSHAKE_NTOR,

  /** Onion Handshake: tap. */
  STAT_HANDSHAKE_TAP,

  /** Last element, make sure this is always the last element of stat_key_t. */
  STAT_LAST
} stats_store_key_t;

void stats_store_init(void);
void stats_store_cleanup(void);

void stats_store_update(stats_store_key_t key, size_t value);
size_t stats_store_get_value(stats_store_key_t key);
int stats_store_is_modified(stats_store_key_t key);
void stats_store_reset_all(void);

const char *stats_store_key_string(stats_store_key_t key);

#ifdef STATS_STORE_PRIVATE

STATIC void stats_store_reset(stats_store_key_t key);

#endif /* STATS_STORE_PRIVATE. */

#endif /* TOR_STATS_STORE_H */

