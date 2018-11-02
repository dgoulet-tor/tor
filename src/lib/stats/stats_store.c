/* Copyright (c) 2018, The Tor Project, Inc. */
/* See LICENSE for licensing information */

/**
 * \file stats_store.c
 * \brief XXX: Write a brief introduction to this module.
 **/

#define STATS_STORE_PRIVATE

#include "lib/log/util_bug.h"
#include "lib/malloc/malloc.h"

#include "stats_entry.h"
#include "stats_store.h"

#define PREFIX(s) ("tor." s)

static stats_entry_t *entries[STAT_LAST];

void
stats_store_init(void)
{
  /* src/common/util.c: ... */
  entries[STAT_MALLOC_BYTES] = stats_entry_new_counter();
  entries[STAT_MALLOC_COUNT] = stats_entry_new_counter();
  entries[STAT_REALLOC_BYTES] = stats_entry_new_counter();
  entries[STAT_REALLOC_COUNT] = stats_entry_new_counter();

  /* FIXME(ahf): ... */
  entries[STAT_CONNECTION_WRITTEN] = stats_entry_new_counter();
  entries[STAT_CONNECTION_READ] = stats_entry_new_counter();

  /* src/or/main.c stats. */
  entries[STAT_MAIN_LOOP_SUCCESS] = stats_entry_new_counter();

  /* src/or/dos.c stats. */
  entries[STAT_DOS_REJECTED_ADDRS] = stats_entry_new_counter();
  entries[STAT_DOS_REJECTED_CELLS] = stats_entry_new_counter();
  entries[STAT_DOS_MARKED_ADDRESSES] = stats_entry_new_counter();

  /* src/or/command.c stats. */
  entries[STAT_COMMAND_CREATE_CELLS_PROCESSED] = stats_entry_new_counter();
  entries[STAT_COMMAND_CREATED_CELLS_PROCESSED] = stats_entry_new_counter();
  entries[STAT_COMMAND_RELAY_CELLS_PROCESSED] = stats_entry_new_counter();
  entries[STAT_COMMAND_DESTROY_CELLS_PROCESSED] = stats_entry_new_counter();
}

void
stats_store_cleanup(void)
{
  for (int i = 0; i < STAT_LAST; ++i)
    stats_entry_free(entries[i]);
}

void
stats_store_update(stats_store_key_t key, size_t value)
{
  tor_assert(key < STAT_LAST);

  stats_entry_t *entry = entries[key];
  tor_assert(entry != NULL);

  stats_entry_update(entry, value);
}

size_t
stats_store_get_value(stats_store_key_t key)
{
  tor_assert(key < STAT_LAST);

  stats_entry_t *entry = entries[key];
  tor_assert(entry != NULL);

  return stats_entry_get_value(entry);
}

int
stats_store_is_modified(stats_store_key_t key)
{
  tor_assert(key < STAT_LAST);

  stats_entry_t *entry = entries[key];
  tor_assert(entry != NULL);

  return stats_entry_is_modified(entry);
}

void
stats_store_reset_all(void)
{
  for (int i = 0; i < STAT_LAST; ++i)
    stats_store_reset(i);
}

const char *
stats_store_key_string(stats_store_key_t key)
{
  switch (key) {
  case STAT_MALLOC_BYTES:
    return PREFIX("internal.memory.malloc.bytes");
  case STAT_MALLOC_COUNT:
    return PREFIX("internal.memory.malloc.count");
  case STAT_REALLOC_BYTES:
    return PREFIX("internal.memory.realloc.bytes");
  case STAT_REALLOC_COUNT:
    return PREFIX("internal.memory.realloc.count");
  case STAT_CONNECTION_WRITTEN:
    return PREFIX("network.connection.written");
  case STAT_CONNECTION_READ:
    return PREFIX("network.connection.read");
  case STAT_MAIN_LOOP_SUCCESS:
    return PREFIX("internal.mainloop.successful");
  case STAT_DOS_REJECTED_ADDRS:
    return PREFIX("dos.rejected_addrs");
  case STAT_DOS_REJECTED_CELLS:
    return PREFIX("dos.rejected_cells");
  case STAT_DOS_MARKED_ADDRESSES:
    return PREFIX("dos.marked_addresses");
  case STAT_COMMAND_CREATE_CELLS_PROCESSED:
    return PREFIX("command.cells.processed.create");
  case STAT_COMMAND_CREATED_CELLS_PROCESSED:
    return PREFIX("command.cells.processed.created");
  case STAT_COMMAND_RELAY_CELLS_PROCESSED:
    return PREFIX("command.cells.processed.relay");
  case STAT_COMMAND_DESTROY_CELLS_PROCESSED:
    return PREFIX("command.cells.processed.destroy");

  /* Fall through. */
  case STAT_LAST:
  default:
    goto err;
  }

  // LCOV_EXCL_START
 err:
  tor_assert(0);
  return "";
  // LCOV_EXCL_STOP
}

STATIC void
stats_store_reset(stats_store_key_t key)
{
  tor_assert(key < STAT_LAST);

  stats_entry_t *entry = entries[key];
  tor_assert(entry != NULL);

  stats_entry_reset(entry);
}

