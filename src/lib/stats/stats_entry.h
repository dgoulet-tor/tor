/* Copyright (c) 2018, The Tor Project, Inc. */
/* See LICENSE for licensing information */

/**
 * \file stats_entry.h
 * \brief Header file for stats_entry.c.
 **/

#ifndef TOR_STATS_ENTRY_H
#define TOR_STATS_ENTRY_H

#include "lib/cc/torint.h"

/* Only stats_store.c should access this. Nothing outside the library should
 * be including this and directly accessing the ABI. */
#ifdef STATS_ENTRY_PRIVATE

typedef enum {
  STATS_TYPE_COUNTER
} stats_entry_type_t;

typedef struct stats_entry_counter_t {
  size_t value;
} stats_entry_counter_t;

typedef struct stats_entry_t {
  stats_entry_type_t type;

  union {
    stats_entry_counter_t counter;
  } u;
} stats_entry_t;

typedef struct stats_entry_t stats_entry_t;

void stats_entry_init(stats_entry_t *entry, stats_entry_type_t type);
void stats_entry_reset(stats_entry_t *entry);

void stats_entry_update(stats_entry_t *entry, size_t value);
size_t stats_entry_get_value(const stats_entry_t *entry);

#endif /* STATS_ENTRY_PRIVATE */

#endif /* TOR_STATS_ENTRY_H */

