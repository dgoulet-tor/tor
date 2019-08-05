/* Copyright (c) 2017, The Tor Project, Inc. */
/* See LICENSE for licensing information */

#include "core/or/channel.h"

#include "core/or/cell_queue_st.h"
#include "core/or/cell_st.h"

#include "cells.h"

#define TRACEPOINT_CREATE_PROBES
#define TRACEPOINT_DEFINE
#include "events.h"

static uint32_t cell_next_id = 1;

static digest256map_t *conn_id_map;

typedef struct cell_info_t {
  uint32_t id;
  uint32_t circ_id;
  uint8_t command;
  ssize_t outbuf_pos;
} cell_info_t;

void
cell_relay_tracing_init(void)
{
  conn_id_map = digest256map_new();
}

void
cell_relay_tracing_free_all(void)
{
  if (conn_id_map == NULL) {
    return;
  }
  DIGEST256MAP_FOREACH_MODIFY(conn_id_map, k, digest256map_t *, infos) {
    MAP_DEL_CURRENT(k);
    digest256map_free(infos, tor_free_);
  } DIGEST256MAP_FOREACH_END;
  digest256map_free(conn_id_map, NULL);
}

void
cell_relay_tracing_inbuf(cell_t *cell)
{
  cell->id = cell_next_id++;
  tor_trace(cell, inbuf, cell);
}

void
cell_relay_tracing_recognized(cell_t *cell)
{
  tor_trace(cell, recognized, cell);
}

void
cell_relay_tracing_queue(cell_t *cell)
{
  /* We can queue cells on a circuit without coming from the inbuf. */
  if (cell->id == 0) {
    cell->id = cell_next_id++;
  }
  tor_trace(cell, queue, cell);
}

static void
cell_relay_tracing_outbuf_(const cell_t *cell, const connection_t *conn,
                           int wide_circ_ids)
{
  uint8_t key[DIGEST256_LEN] = {0};
  digest256map_t *infos;
  cell_info_t *c_info;

  set_uint32(key, (uint32_t) conn->global_identifier);
  infos = digest256map_get(conn_id_map, key);
  if (infos == NULL) {
    infos = digest256map_new();
    digest256map_set(conn_id_map, key, infos);
  }

  memset(key, 0, sizeof(key));
  set_uint32(key, cell->id);
  c_info = digest256map_get(infos, key);
  if (c_info != NULL) {
    tor_trace(cell, error_outbuf, cell, "Cell already in outbuf");
  } else {
    c_info = tor_malloc_zero(sizeof(*c_info));
    c_info->command = cell->command;
    c_info->id = cell->id;
    c_info->circ_id = cell->circ_id;
    c_info->outbuf_pos =
      buf_datalen(conn->outbuf) + get_cell_network_size(wide_circ_ids);
    digest256map_set(infos, key, c_info);
  }

  tor_trace(cell, outbuf, cell);
}

void
cell_relay_tracing_outbuf_packed(packed_cell_t *pcell,
                                 const connection_t *conn, int wide_circ_ids)
{
  cell_t cell;

  /* This cell was put directly into the outbuf. */
  if (pcell->id == 0) {
    pcell->id = cell_next_id++;
  }

  const char *src = pcell->body;

  if (wide_circ_ids) {
    cell.circ_id = ntohl(get_uint32(src));
    src += 4;
  } else {
    cell.circ_id = ntohs(get_uint16(src));
    src += 2;
  }
  cell.command = get_uint8(src);
  cell.id = pcell->id;

  cell_relay_tracing_outbuf_(&cell, conn, wide_circ_ids);
}

void
cell_relay_tracing_outbuf(cell_t *cell, const connection_t *conn,
                          int wide_circ_ids)
{
  /* This cell was put directly into the outbuf. */
  if (cell->id == 0) {
    cell->id = cell_next_id++;
  }

  cell_relay_tracing_outbuf_(cell, conn, wide_circ_ids);
}

void
cell_relay_tracing_flush(const connection_t *conn, int flushed_bytes)
{
  uint8_t key[DIGEST256_LEN] = {0};

  set_uint32(key, (uint32_t) conn->global_identifier);
  digest256map_t *infos = digest256map_get(conn_id_map, key);
  if (infos == NULL) {
    tor_trace(cell, error_flush, "Unknown connection ID");
    return;
  }
  /* Go over all cells and update bytes written. */
  DIGEST256MAP_FOREACH_MODIFY(infos, k, cell_info_t *, c_info) {
    c_info->outbuf_pos -= flushed_bytes;
    if (c_info->outbuf_pos <= 0) {
      tor_trace(cell, flush, c_info->id, c_info->command, c_info->circ_id);
      MAP_DEL_CURRENT(k);
      tor_free(c_info);
    }
  } DIGEST256MAP_FOREACH_END;
}
