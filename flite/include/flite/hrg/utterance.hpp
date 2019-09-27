#pragma once

#include "flite/hrg/item.hpp"
#include "flite/hrg/relation.hpp"
#include "flite/utils/alloc.hpp"
#include "flite/utils/features.hpp"
#include "flite/utils/file.hpp"
#include "flite/utils/val.hpp"

struct cst_utterance_struct {
    cst_features* features;
    cst_features* ffunctions;
    cst_features* relations;
    cst_alloc_context ctx;
};

/* Constructor functions */
cst_utterance* new_utterance();
void delete_utterance(cst_utterance* u);

cst_relation* utt_relation(const cst_utterance* u, const char* name);
cst_relation* utt_relation_create(cst_utterance* u, const char* name);
int utt_relation_delete(cst_utterance* u, const char* name);
int utt_relation_present(cst_utterance* u, const char* name);

typedef cst_utterance* (*cst_uttfunc)(cst_utterance* i);
CST_VAL_USER_FUNCPTR_DCLS(uttfunc, cst_uttfunc)

/* Allocate memory "locally" to an utterance, on platforms that
   support/require this (currently only WinCE) */
#define cst_utt_alloc(UTT, TYPE, SIZE) ((TYPE*)cst_local_alloc((UTT)->ctx, sizeof(TYPE) * (SIZE)))
#define cst_utt_free(UTT, PTR) cst_local_free((UTT)->ctx, (PTR))
