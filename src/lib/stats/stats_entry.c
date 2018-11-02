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

typedef struct stats_counter_t {
  size_t value;
} stats_counter_t;

typedef struct stats_entry_t {
  stats_type_t type;
  int is_modified;

  union {
    stats_counter_t counter;
  } u;
} stats_entry_t;

static stats_entry_t *
stats_entry_new(stats_type_t type)
{
  stats_entry_t *entry = NULL;

  entry = raw_malloc(sizeof(stats_entry_t));
  memset(entry, 0, sizeof(stats_entry_t));

  entry->type = type;
  entry->is_modified = 0;

  return entry;
}

stats_entry_t *
stats_entry_new_counter(void)
{
  stats_entry_t *counter;
  counter = stats_entry_new(STATS_TYPE_COUNTER);
  return counter;
}

void
stats_entry_free_(stats_entry_t *entry)
{
  if (! entry)
    return;

  tor_free(entry);
}

stats_type_t
stats_entry_get_type(const stats_entry_t *entry)
{
  tor_assert(entry);

  return entry->type;
}

int
stats_entry_is_modified(const stats_entry_t *entry)
{
  tor_assert(entry);

  return entry->is_modified;
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
  tor_assert(0);
  return 0;
  // LCOV_EXCL_STOP
}

void
stats_entry_update(stats_entry_t *entry, size_t value)
{
  tor_assert(entry);

  entry->is_modified = 1;

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

  entry->is_modified = 0;

  switch (entry->type) {
  case STATS_TYPE_COUNTER:
    entry->u.counter.value = 0;
    break;
  }
}
