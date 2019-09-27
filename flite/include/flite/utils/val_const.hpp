#pragma once

#include "flite/utils/val.hpp"
#include "flite/utils/val_defs.hpp"

/* There is built-in int to string conversions here for numbers   */
/* up to 20, note if you make this bigger you have to hand change */
/* other things too                                               */
#define CST_CONST_INT_MAX 19

#ifndef NO_UNION_INITIALIZATION

/* This is the simple way when initialization of unions is supported */

#define DEF_CONST_VAL_INT(N, V) const cst_val N = {{.a = {.type = CST_VAL_TYPE_INT, .ref_count = -1, .v = {.ival = V}}}}
#define DEF_CONST_VAL_STRING(N, S) const cst_val N = {{.a = {.type = CST_VAL_TYPE_STRING, .ref_count = -1, .v = {.vval = (void*)S}}}}
#define DEF_CONST_VAL_FLOAT(N, F) const cst_val N = {{.a = {.type = CST_VAL_TYPE_FLOAT, .ref_count = -1, .v = {.fval = F}}}}
#define DEF_CONST_VAL_CONS(N, A, D) const cst_val N = {{.cc = {.car = (cst_val*)A, .cdr = (cst_val*)D}}}

extern const cst_val val_int_0;
extern const cst_val val_int_1;
extern const cst_val val_int_2;
extern const cst_val val_int_3;
extern const cst_val val_int_4;
extern const cst_val val_int_5;
extern const cst_val val_int_6;
extern const cst_val val_int_7;
extern const cst_val val_int_8;
extern const cst_val val_int_9;
extern const cst_val val_int_10;
extern const cst_val val_int_11;
extern const cst_val val_int_12;
extern const cst_val val_int_13;
extern const cst_val val_int_14;
extern const cst_val val_int_15;
extern const cst_val val_int_16;
extern const cst_val val_int_17;
extern const cst_val val_int_18;
extern const cst_val val_int_19;
extern const cst_val val_int_20;
extern const cst_val val_int_21;
extern const cst_val val_int_22;
extern const cst_val val_int_23;
extern const cst_val val_int_24;

extern const cst_val val_string_0;
extern const cst_val val_string_1;
extern const cst_val val_string_2;
extern const cst_val val_string_3;
extern const cst_val val_string_4;
extern const cst_val val_string_5;
extern const cst_val val_string_6;
extern const cst_val val_string_7;
extern const cst_val val_string_8;
extern const cst_val val_string_9;
extern const cst_val val_string_10;
extern const cst_val val_string_11;
extern const cst_val val_string_12;
extern const cst_val val_string_13;
extern const cst_val val_string_14;
extern const cst_val val_string_15;
extern const cst_val val_string_16;
extern const cst_val val_string_17;
extern const cst_val val_string_18;
extern const cst_val val_string_19;
extern const cst_val val_string_20;
extern const cst_val val_string_21;
extern const cst_val val_string_22;
extern const cst_val val_string_23;
extern const cst_val val_string_24;

#else
/* Only GCC seems to currently support the C99 standard for giving      */
/* explicit names for fields for initializing unions, because we want   */
/* things to be const, and to be small structures this is really useful */
/* thus for compilers not supporting no_union_initization we use other  */
/* structure that we know (hope ?) are the same size and use agressive  */
/* casting. The goal here is wholly justified but the method here isn't */
/* pretty                                                               */

/* These structures are defined *solely* to get round initialization    */
/* problems if you need to use these in any code you are using, you are */
/* unquestionably doing the wrong thing                                 */
typedef struct cst_val_atom_struct_float {
#ifdef WORDS_BIGENDIAN
    short ref_count;
    short type; /* order is here important */
#else
#if (defined(__x86_64__) || defined(_M_X64))
    int type; /* order is here important */
    int ref_count;
#else
    short type; /* order is here important */
    short ref_count;
#endif
#endif
#if (defined(__x86_64__) || defined(_M_X64))
    double fval;
#else
    float fval;
#endif
} cst_val_float;

typedef struct cst_val_atom_struct_int {
#ifdef WORDS_BIGENDIAN
    short ref_count;
    short type; /* order is here important (and unintuitive) */
#else
#if (defined(__x86_64__) || defined(_M_X64))
    int type; /* order is here important */
    int ref_count;
#else
    short type; /* order is here important */
    short ref_count;
#endif
#endif
#if (defined(__x86_64__) || defined(_M_X64))
    long long ival;
#else
    int ival;
#endif
} cst_val_int;

typedef struct cst_val_atom_struct_void {
#ifdef WORDS_BIGENDIAN
    short ref_count;
    short type; /* order is here important */
#else
#if (defined(__x86_64__) || defined(_M_X64))
    int type; /* order is here important */
    int ref_count;
#else
    short type; /* order is here important */
    short ref_count;
#endif
#endif
    void* vval;
} cst_val_void;

#ifdef WORDS_BIGENDIAN
#define DEF_CONST_VAL_INT(N, V) const cst_val_int N = {-1, CST_VAL_TYPE_INT, V}
#define DEF_CONST_VAL_STRING(N, S) const cst_val_void N = {-1, CST_VAL_TYPE_STRING, (void*)S}
#define DEF_CONST_VAL_FLOAT(N, F) const cst_val_float N = {-1, CST_VAL_TYPE_FLOAT, (float)F}
#else
#define DEF_CONST_VAL_INT(N, V) const cst_val_int N = {CST_VAL_TYPE_INT, -1, V}
#define DEF_CONST_VAL_STRING(N, S) const cst_val_void N = {CST_VAL_TYPE_STRING, -1, (void*)S}
#define DEF_CONST_VAL_FLOAT(N, F) const cst_val_float N = {CST_VAL_TYPE_FLOAT, -1, (float)F}
#endif
#define DEF_CONST_VAL_CONS(N, A, D) const cst_val_cons N = {A, D}

/* in the non-union intialization version we these consts have to be */
/* more typed than need, we'll cast the back later                   */
extern const cst_val_int val_int_0;
extern const cst_val_int val_int_1;
extern const cst_val_int val_int_2;
extern const cst_val_int val_int_3;
extern const cst_val_int val_int_4;
extern const cst_val_int val_int_5;
extern const cst_val_int val_int_6;
extern const cst_val_int val_int_7;
extern const cst_val_int val_int_8;
extern const cst_val_int val_int_9;
extern const cst_val_int val_int_10;
extern const cst_val_int val_int_11;
extern const cst_val_int val_int_12;
extern const cst_val_int val_int_13;
extern const cst_val_int val_int_14;
extern const cst_val_int val_int_15;
extern const cst_val_int val_int_16;
extern const cst_val_int val_int_17;
extern const cst_val_int val_int_18;
extern const cst_val_int val_int_19;
extern const cst_val_int val_int_20;
extern const cst_val_int val_int_21;
extern const cst_val_int val_int_22;
extern const cst_val_int val_int_23;
extern const cst_val_int val_int_24;

extern const cst_val_void val_string_0;
extern const cst_val_void val_string_1;
extern const cst_val_void val_string_2;
extern const cst_val_void val_string_3;
extern const cst_val_void val_string_4;
extern const cst_val_void val_string_5;
extern const cst_val_void val_string_6;
extern const cst_val_void val_string_7;
extern const cst_val_void val_string_8;
extern const cst_val_void val_string_9;
extern const cst_val_void val_string_10;
extern const cst_val_void val_string_11;
extern const cst_val_void val_string_12;
extern const cst_val_void val_string_13;
extern const cst_val_void val_string_14;
extern const cst_val_void val_string_15;
extern const cst_val_void val_string_16;
extern const cst_val_void val_string_17;
extern const cst_val_void val_string_18;
extern const cst_val_void val_string_19;
extern const cst_val_void val_string_20;
extern const cst_val_void val_string_21;
extern const cst_val_void val_string_22;
extern const cst_val_void val_string_23;
extern const cst_val_void val_string_24;

#endif

#define DEF_STATIC_CONST_VAL_INT(N, V) static DEF_CONST_VAL_INT(N, V)
#define DEF_STATIC_CONST_VAL_STRING(N, S) static DEF_CONST_VAL_STRING(N, S)
#define DEF_STATIC_CONST_VAL_FLOAT(N, F) static DEF_CONST_VAL_FLOAT(N, F)
#define DEF_STATIC_CONST_VAL_CONS(N, A, D) static DEF_CONST_VAL_CONS(N, A, D)

/* Some actual val consts */
/* The have casts as in the non-union intialize case the casts are necessary */
/* but in the union initial case these casts are harmless                    */

#define VAL_INT_0 (cst_val*)&val_int_0
#define VAL_INT_1 (cst_val*)&val_int_1
#define VAL_INT_2 (cst_val*)&val_int_2
#define VAL_INT_3 (cst_val*)&val_int_3
#define VAL_INT_4 (cst_val*)&val_int_4
#define VAL_INT_5 (cst_val*)&val_int_5
#define VAL_INT_6 (cst_val*)&val_int_6
#define VAL_INT_7 (cst_val*)&val_int_7
#define VAL_INT_8 (cst_val*)&val_int_8
#define VAL_INT_9 (cst_val*)&val_int_9
#define VAL_INT_10 (cst_val*)&val_int_10
#define VAL_INT_11 (cst_val*)&val_int_11
#define VAL_INT_12 (cst_val*)&val_int_12
#define VAL_INT_13 (cst_val*)&val_int_13
#define VAL_INT_14 (cst_val*)&val_int_14
#define VAL_INT_15 (cst_val*)&val_int_15
#define VAL_INT_16 (cst_val*)&val_int_16
#define VAL_INT_17 (cst_val*)&val_int_17
#define VAL_INT_18 (cst_val*)&val_int_18
#define VAL_INT_19 (cst_val*)&val_int_19
#define VAL_INT_20 (cst_val*)&val_int_20
#define VAL_INT_21 (cst_val*)&val_int_21
#define VAL_INT_22 (cst_val*)&val_int_22
#define VAL_INT_23 (cst_val*)&val_int_23
#define VAL_INT_24 (cst_val*)&val_int_24

const cst_val* val_int_n(int n);

#define VAL_STRING_0 (cst_val*)&val_string_0
#define VAL_STRING_1 (cst_val*)&val_string_1
#define VAL_STRING_2 (cst_val*)&val_string_2
#define VAL_STRING_3 (cst_val*)&val_string_3
#define VAL_STRING_4 (cst_val*)&val_string_4
#define VAL_STRING_5 (cst_val*)&val_string_5
#define VAL_STRING_6 (cst_val*)&val_string_6
#define VAL_STRING_7 (cst_val*)&val_string_7
#define VAL_STRING_8 (cst_val*)&val_string_8
#define VAL_STRING_9 (cst_val*)&val_string_9
#define VAL_STRING_10 (cst_val*)&val_string_10
#define VAL_STRING_11 (cst_val*)&val_string_11
#define VAL_STRING_12 (cst_val*)&val_string_12
#define VAL_STRING_13 (cst_val*)&val_string_13
#define VAL_STRING_14 (cst_val*)&val_string_14
#define VAL_STRING_15 (cst_val*)&val_string_15
#define VAL_STRING_16 (cst_val*)&val_string_16
#define VAL_STRING_17 (cst_val*)&val_string_17
#define VAL_STRING_18 (cst_val*)&val_string_18
#define VAL_STRING_19 (cst_val*)&val_string_19
#define VAL_STRING_20 (cst_val*)&val_string_20
#define VAL_STRING_21 (cst_val*)&val_string_21
#define VAL_STRING_22 (cst_val*)&val_string_22
#define VAL_STRING_23 (cst_val*)&val_string_23
#define VAL_STRING_24 (cst_val*)&val_string_24

const cst_val* val_string_n(int n);
