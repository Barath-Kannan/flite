#pragma once

#include "flite/hrg/hrg.hpp"
#include "flite/stats/cart.hpp"
#include "flite/utils/val.hpp"

cst_val* en_exp_number(const char* numstring);
cst_val* en_exp_digits(const char* numstring);
cst_val* en_exp_id(const char* numstring);
cst_val* en_exp_ordinal(const char* numstring);
cst_val* en_exp_letters(const char* lets);
cst_val* en_exp_real(const char* numstring);
int en_exp_roman(const char* roman);

extern const cst_cart us_nums_cart;

cst_utterance* us_textanalysis(cst_utterance* u);
cst_val* us_tokentowords(cst_item* token);

int us_aswd(const char* w);
