#include "flite/synthcommon/dur_stat.hpp"

CST_VAL_REGISTER_TYPE_NODEL(dur_stats, dur_stats)

const dur_stat* phone_dur_stat(const dur_stats* ds, const char* ph)
{
    int i;
    for (i = 0; ds[i]; i++)
        if (cst_streq(ph, ds[i]->phone))
            return ds[i];

    return ds[0];
}
