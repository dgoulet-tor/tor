/* Copyright (c) 2018, The Tor Project, Inc. */
/* See LICENSE for licensing information */

/**
 * \file stats_entry.h
 * \brief Header file for stats_entry.c.
 **/

#ifndef TOR_STATS_ENTRY_H
#define TOR_STATS_ENTRY_H

#include "lib/cc/torint.h"

typedef enum {
  STATS_TYPE_COUNTER
} stats_type_t;

typedef struct stats_entry_t stats_entry_t;

stats_entry_t *stats_entry_new_counter(void);
void stats_entry_free_(stats_entry_t *entry);
#define stats_entry_free(entry) \
  FREE_AND_NULL(stats_entry_t, stats_entry_free_, (entry))

stats_type_t stats_entry_get_type(const stats_entry_t *entry);
size_t stats_entry_get_value(const stats_entry_t *entry);
int stats_entry_is_modified(const stats_entry_t *entry);
void stats_entry_update(stats_entry_t *entry, size_t value);
void stats_entry_reset(stats_entry_t *entry);

#ifdef STATS_ENTRY_PRIVATE

#endif /* STATS_ENTRY_PRIVATE */

#endif /* TOR_STATS_ENTRY_H */

