/* Copyright (c) 2020, The Tor Project, Inc. */
/* See LICENSE for licensing information */

/**
 * @file hs_metrics.c
 * @brief DOCDOC
 **/

#include "orconfig.h"

#include "lib/cc/compat_compiler.h"

#include "lib/metrics/hs_metrics.h"
#include "lib/metrics/metrics_common.h"
#include "lib/metrics/metrics_key.h"

/* Per onion address data model. */
const metrics_entry_model_t hs_addr_metrics_model[] =
{
  {
    .key = METRICS_HS_NUM_INTRODUCTIONS, /* Index. */
    .type = METRICS_TYPE_COUNTER,
    .name = "hs_intro_num_total",
    .help = "Total number of introduction received",
  },
  {
    .key = METRICS_HS_NUM_ESTABLISHED_RDV, /* Index */
    .type = METRICS_TYPE_GAUGE,
    .name = "hs_rdv_established_count",
    .help = "Total number of established rendezvous circuit",
  },
  {
    .key = METRICS_HS_NUM_RDV, /* Index */
    .type = METRICS_TYPE_COUNTER,
    .name = "hs_rdv_num_total",
    .help = "Total number of rendezvous circuit created",
  },
};
const size_t hs_addr_metrics_model_size =
  ARRAY_LENGTH(hs_addr_metrics_model);

/* Per onion address + port data model. */
const metrics_entry_model_t hs_addr_port_metrics_model[] =
{
  {
    .key = METRICS_HS_APP_WRITE_BYTES, /* Index. */
    .type = METRICS_TYPE_COUNTER,
    .name = "hs_app_write_bytes_total",
    .help = "Total number of bytes written to the application",
  },
  {
    .key = METRICS_HS_APP_READ_BYTES, /* Index. */
    .type = METRICS_TYPE_COUNTER,
    .name = "hs_app_read_bytes_total",
    .help = "Total number of bytes read from the application",
  },
};
const size_t hs_addr_port_metrics_model_size =
  ARRAY_LENGTH(hs_addr_port_metrics_model);
