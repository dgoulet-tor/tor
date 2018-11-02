/* Copyright (c) 2018, The Tor Project, Inc. */
/* See LICENSE for licensing information */

/**
 * \file stats_entry.c
 * \brief XXX: Write a brief introduction to this module.
 **/

#define STATS_ENTRY_PRIVATE

#include <string.h>

#include "lib/log/util_bug.h"
#include "lib/malloc/malloc.h"

#include "stats_entry.h"

void
stats_entry_init(stats_entry_t *entry, stats_entry_type_t type)
{
  tor_assert(entry);
  memset(entry, 0, sizeof(stats_entry_t));
  entry->type = type;
}

size_t
stats_entry_get_value(const stats_entry_t *entry)
{
  tor_assert(entry);

  switch (entry->type) {
  case STATS_TYPE_COUNTER:
    return entry->u.counter.value;
  }

  // LCOV_EXCL_START
  tor_assert_unreached();
  // LCOV_EXCL_STOP
}

void
stats_entry_update(stats_entry_t *entry, size_t value)
{
  tor_assert(entry);

  switch (entry->type) {
  case STATS_TYPE_COUNTER:
    entry->u.counter.value += value;
    break;
  }
}

void
stats_entry_reset(stats_entry_t *entry)
{
  tor_assert(entry);

  switch (entry->type) {
  case STATS_TYPE_COUNTER:
    entry->u.counter.value = 0;
    break;
  }
}
