#pragma once

#include "flite/utils/val.hpp"

typedef struct cst_dur_stats_struct {
    const char* phone;
    float mean;
    float stddev;
} dur_stat;
typedef dur_stat* dur_stats; /* only one star, due to funky cst_val magic */

CST_VAL_USER_TYPE_DCLS(dur_stats, dur_stats)

const dur_stat* phone_dur_stat(const dur_stats* ds, const char* ph);
