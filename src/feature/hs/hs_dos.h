/* Copyright (c) 2019, The Tor Project, Inc. */
/* See LICENSE for licensing information */

/**
 * \file hs_dos.h
 * \brief Header file containing denial of service defenses for the HS
 *        subsystem for all versions.
 **/

#ifndef TOR_HS_DOS_H
#define TOR_HS_DOS_H

#include "core/or/or_circuit_st.h"

bool hs_dos_can_send_intro2(const or_circuit_t *service);

#ifdef HS_DOS_PRIVATE

#ifdef TOR_UNIT_TESTS

#endif /* define(TOR_UNIT_TESTS) */

#endif /* defined(HS_DOS_PRIVATE) */

#endif /* !defined(TOR_HS_DOS_H) */

