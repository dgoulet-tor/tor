/* Copyright (c) 2019, The Tor Project, Inc. */
/* See LICENSE for licensing information */

/**
 * \file providers.h
 * \brief Header file for Tor event LTTng UST tracing.
 **/

#undef TRACEPOINT_PROVIDER
#define TRACEPOINT_PROVIDER tor_hs_service

#undef TRACEPOINT_INCLUDE
#define TRACEPOINT_INCLUDE "./lib/trace/lttng/providers_hs_service.h"

#if !defined(_TRACEPOINT_TOR_HS_SERVICE) || defined(TRACEPOINT_HEADER_MULTI_READ)
#define _TRACEPOINT_TOR_HS_SERVICE

TRACEPOINT_ENUM(tor_hs_service, desc_cant_upload,
  TP_ENUM_VALUES(
    ctf_enum_value("MISSING_IPS", 1)
    ctf_enum_value("ESTABLISHED_IPS", 2)
    ctf_enum_value("UPLOAD_TIME", 3)
    ctf_enum_value("LIVE_NS", 4)
    ctf_enum_value("MIN_DIRINFO", 5)
  )
)

TRACEPOINT_EVENT(tor_hs_service, desc_cant_upload,
  TP_ARGS(int, r, unsigned int, num_ips, time_t, upload_ts, bool, is_next),
  TP_FIELDS(
    ctf_string(desc, (is_next) ? "NEXT" : "CURRENT")
    ctf_enum(tor_hs_service, desc_cant_upload, int, reason, r)
    ctf_integer(unsigned int, num_ips, num_ips)
    ctf_integer(time_t, next_upload_time, upload_ts)
  )
)

TRACEPOINT_EVENT(tor_hs_service, desc_upload,
  TP_ARGS(unsigned int, num_ips, time_t, upload_ts, bool, is_next),
  TP_FIELDS(
    ctf_string(desc, (is_next) ? "NEXT" : "CURRENT")
    ctf_integer(unsigned int, num_ips, num_ips)
    ctf_integer(time_t, next_upload_time, upload_ts)
  )
)

#endif /* _TRACEPOINT_TOR_HS_SERVICE */

#include <lttng/tracepoint-event.h>
