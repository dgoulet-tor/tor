/* Copyright (c) 2018, The Tor Project, Inc. */
/* See LICENSE for licensing information */

/**
 * \file stats_store.c
 * \brief XXX: Write a brief introduction to this module.
 **/

#include "lib/log/util_bug.h"
#include "lib/malloc/malloc.h"

#define STATS_ENTRY_PRIVATE
#include "stats_entry.h"
#include "stats_store.h"

/* Contains the data stats that will be reported. */
static stats_entry_t entries[STAT_LAST];

/* Helper: define a stats_config_t of type counter. */
#define COUNTER(val) { val, STATS_TYPE_COUNTER }

static struct stats_config_t {
  /* Entry store key. */
  stats_store_key_t key;
  /* Entry type. */
  stats_entry_type_t type;
} stats_config[] = {
  /* Setup the config array. */
  COUNTER(STAT_MALLOC_BYTES),
  COUNTER(STAT_MALLOC_COUNT),
  COUNTER(STAT_REALLOC_BYTES),
  COUNTER(STAT_REALLOC_COUNT),

  COUNTER(STAT_CONNECTION_WRITTEN),
  COUNTER(STAT_CONNECTION_READ),

  COUNTER(STAT_MAIN_LOOP_SUCCESS),

  COUNTER(STAT_DOS_REJECTED_CELLS),
  COUNTER(STAT_DOS_MARKED_ADDRESSES),
  COUNTER(STAT_DOS_REJECTED_ADDRS),
  COUNTER(STAT_DOS_REFUSED_SINGLE_HOP),

  COUNTER(STAT_COMMAND_CREATE_CELLS_PROCESSED),
  COUNTER(STAT_COMMAND_CREATED_CELLS_PROCESSED),
  COUNTER(STAT_COMMAND_RELAY_CELLS_PROCESSED),
  COUNTER(STAT_COMMAND_DESTROY_CELLS_PROCESSED),

  COUNTER(STAT_HANDSHAKE_NTOR),
  COUNTER(STAT_HANDSHAKE_TAP),

  /* Last element marker. */
  COUNTER(STAT_LAST),
};

void
stats_store_init(void)
{
  /* Initialize entry's type from the config. */
  for (int i = 0; stats_config[i].key != STAT_LAST; ++i) {
    stats_store_key_t key = stats_config[i].key;
    stats_entry_init(&entries[key], stats_config[i].type);
  }
}

inline void
stats_store_update(stats_store_key_t key, size_t value)
{
  tor_assert(key < STAT_LAST);
  stats_entry_update(&entries[key], value);
}

size_t
stats_store_get_value(stats_store_key_t key)
{
  tor_assert(key < STAT_LAST);
  return stats_entry_get_value(&entries[key]);
}

void
stats_store_reset_all(void)
{
  for (int i = 0; i < STAT_LAST; ++i) {
    stats_entry_reset(&entries[i]);
  }
}

#define PREFIX(s) ("tor." s)

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
  case STAT_DOS_REFUSED_SINGLE_HOP:
    return PREFIX("dos.refused_single_hop");
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
