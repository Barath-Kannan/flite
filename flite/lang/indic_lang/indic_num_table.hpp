#pragma once

typedef const char* const digit_table[11][2];
typedef const char* const two_digit_table[101][4];

typedef struct cst_indic_num_table_struct {
    const char* lang;
    digit_table* digit;
    two_digit_table* two_digit;
    const char* hundred;
    const char* thousand;
    const char* lakh;
    const char* crore;
} indic_num_table;

#define num_table_digit(TABLE, I, J) ((*(TABLE->digit))[I][J])
#define num_table_two_digit(TABLE, I, J) ((*(TABLE->two_digit))[I][J])
