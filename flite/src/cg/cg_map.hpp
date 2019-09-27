#pragma once

#include "flite/cg/cg.hpp"

#include "flite/stats/cart.hpp"
#include "flite/synth/synth.hpp"
#include "flite/utils/file.hpp"
#include "flite/utils/val.hpp"

/* If voice to be read was dumped on a platform byteswapped from this one */
#define CST_CG_BYTESWAPPED_VOICE 27

int cst_cg_read_header(cst_file fd);

cst_cg_db* cst_cg_load_db(cst_voice* vox, cst_file fd, int bs);
void cst_cg_free_db(cst_file fd, cst_cg_db*);

char* cst_read_string(cst_file fd, int bs);
void* cst_read_padded(cst_file fd, int* nb, int bs);
char** cst_read_db_types(cst_file fd, int bs);

cst_cart_node* cst_read_tree_nodes(cst_file fd, int bs);
char** cst_read_tree_feats(cst_file fd, int bs);
cst_cart* cst_read_tree(cst_file fd, int bs);
cst_cart** cst_read_tree_array(cst_file fd, int bs);

float* cst_read_float_array(cst_file fd, int bs);
double* cst_read_double_array(cst_file fd, int bs);
unsigned short* cst_read_ushort_array(cst_file fd, int bs);
float** cst_read_2d_float_array(cst_file fd, int bs);
double** cst_read_2d_double_array(cst_file fd, int bs);
unsigned short** cst_read_2d_ushort_array(cst_file fd, int bs);

dur_stat** cst_read_dur_stats(cst_file fd, int bs);

char*** cst_read_phone_states(cst_file fd, int bs);

void cst_read_voice_feature(cst_file fd, char** fname, char** fval, int bs);
int cst_read_int(cst_file fd, int bs);
float cst_read_float(cst_file fd, int bs);

extern const char* const cg_voice_header_string;
