/* Copyright (c) 2017-2019, The Tor Project, Inc. */
/* See LICENSE for licensing information */

/**
 * \file trace.c
 * \brief Common functions for event-tracing implementation
 *
 * See trace.h and doc/HACKING/Tracing.md for more information.
 **/

#include "lib/trace/trace.h"

#include "cells.h"

/** Initialize the tracing library. */
void
tor_trace_init(void)
{
  cell_relay_tracing_init();
}

void
tor_trace_free_all(void)
{
  cell_relay_tracing_free_all();
}
