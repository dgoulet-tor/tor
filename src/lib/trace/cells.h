/* Copyright (c) 2017, The Tor Project, Inc. */
/* See LICENSE for licensing information */

#ifndef TOR_TRACE_CELL_H
#define TOR_TRACE_CELL_H

#include "core/or/channel.h"

#include "core/or/cell_queue_st.h"
#include "core/or/cell_st.h"
#include "core/or/connection_st.h"

#if USE_EVENT_TRACING_CELLS

void cell_relay_tracing_free_all(void);
void cell_relay_tracing_init(void);

void cell_relay_tracing_inbuf(cell_t *cell);
void cell_relay_tracing_recognized(cell_t *cell);
void cell_relay_tracing_queue(cell_t *cell);
void cell_relay_tracing_outbuf(cell_t *cell, const connection_t *conn,
                               int wide_circ_ids);
void cell_relay_tracing_outbuf_packed(packed_cell_t *pcell,
                                      const connection_t *conn,
                                      int wide_circ_ids);
void cell_relay_tracing_flush(const connection_t *conn, int flushed_bytes);

#else

void cell_relay_tracing_free_all(void) {}
void cell_relay_tracing_init(void) {}

void cell_relay_tracing_inbuf(cell_t *cell) {}
void cell_relay_tracing_recognized(cell_t *cell) {}
void cell_relay_tracing_queue(cell_t *cell) {}
void cell_relay_tracing_outbuf(cell_t *pcell, const connection_t *conn,
                               int wide_circ_ids) {}
void cell_relay_tracing_outbuf_packed(packed_cell_t *pcell,
                                      const connection_t *conn,
                                      int wide_circ_ids) {}
void cell_relay_tracing_flush(const connection_t *conn, int flushed_bytes) {}

#endif /* USE_EVENT_TRACING_CELLS */

#endif /* TOR_TRACE_CELL_H */

