#pragma once

#include "flite/utils/alloc.hpp"
#include "flite/utils/string.hpp"
#include "flite/utils/val.hpp"

typedef struct cst_featvalpair_struct {
    const char* name;
    cst_val* val;
    struct cst_featvalpair_struct* next;
} cst_featvalpair;

typedef struct cst_features_struct {
    struct cst_featvalpair_struct* head;
    cst_alloc_context ctx;
    cst_val* owned_strings; /* fnames that are owned by this struct */

    /* Link to other cst_features that we search too */
    const struct cst_features_struct* linked;
} cst_features;

/* Constructor functions */
cst_features* new_features(void);
cst_features* new_features_local(cst_alloc_context ctx);
void delete_features(cst_features* f);

/* Accessor functions */
int feat_int(const cst_features* f, const char* name);
float feat_float(const cst_features* f, const char* name);
const char* feat_string(const cst_features* f, const char* name);
const cst_val* feat_val(const cst_features* f, const char* name);

int get_param_int(const cst_features* f, const char* name, int def);
float get_param_float(const cst_features* f, const char* name, float def);
const char* get_param_string(const cst_features* f, const char* name, const char* def);
const cst_val* get_param_val(const cst_features* f, const char* name, cst_val* def);

/* Setting functions */
void feat_set_int(cst_features* f, const char* name, int v);
void feat_set_float(cst_features* f, const char* name, float v);
void feat_set_string(cst_features* f, const char* name, const char* v);
void feat_set(cst_features* f, const char* name, const cst_val* v);

int feat_remove(cst_features* f, const char* name);
int feat_present(const cst_features* f, const char* name);
int feat_length(const cst_features* f);

/* Feature names are expected to be literals -- its *much* faster to do */
/* look ups and less alloc/frees are necesssary.  Almosts always this is */
/* fine, but when you are making up new fnames, you can get a copy of the */
/* string that will be deleted when the cst_features is deleted */
const char* feat_own_string(cst_features* f, const char* name);

CST_VAL_USER_TYPE_DCLS(features, cst_features)

int feat_copy_into(const cst_features* from, cst_features* to);
/* Link FROM into TO so FROM's features will be searched after TO's features */
int feat_link_into(const cst_features* from, cst_features* to);
/* For debugging */
int cst_feat_print(cst_file fd, const cst_features* f);
