#pragma once

#include "flite/hrg/item.hpp"
#include "flite/utils/features.hpp"
#include "flite/utils/file.hpp"
#include "flite/utils/val.hpp"

struct cst_phoneset_struct {
    const char* name;
    const char* const* featnames;
    const cst_val* const* featvals;
    const char* const* phonenames;
    const char* silence;
    const int num_phones;
    const int* const* fvtable;
    int freeable; /* 0 if const in memory, 1 if we alloc'd it */
};
typedef struct cst_phoneset_struct cst_phoneset;

/* Constructor functions */
cst_phoneset* new_phoneset();
void delete_phoneset(const cst_phoneset* u);

const cst_val* phone_feature(const cst_phoneset* ps, const char* phonename, const char* featname);
const char* phone_feature_string(const cst_phoneset* ps, const char* phonename, const char* featname);
int phone_id(const cst_phoneset* ps, const char* phonename);
int phone_feat_id(const cst_phoneset* ps, const char* featname);

const cst_phoneset* item_phoneset(const cst_item* i);

CST_VAL_USER_TYPE_DCLS(phoneset, cst_phoneset)
