#pragma once

#include "flite/wavesynth/sts.hpp"

#include "flite/hrg/hrg.hpp"
#include "flite/synthcommon/track.hpp"
#include "flite/synthcommon/wave.hpp"
#include "flite/utils/features.hpp"
#include "flite/utils/file.hpp"
#include "flite/utils/val.hpp"

struct cst_diphone_entry_struct {
    const char* name;
    unsigned short start_pm;
    unsigned char pb_pm;
    unsigned char end_pm;
};
typedef struct cst_diphone_entry_struct cst_diphone_entry;

struct cst_diphone_db_struct {
    const char* name;
    int num_entries;
    const cst_diphone_entry* diphones;
    const cst_sts_list* sts;
};
typedef struct cst_diphone_db_struct cst_diphone_db;

CST_VAL_USER_TYPE_DCLS(diphone_db, cst_diphone_db)

cst_utterance* diphone_synth(cst_utterance* utt);
cst_utterance* get_diphone_units(cst_utterance* utt);
