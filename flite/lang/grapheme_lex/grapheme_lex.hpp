#pragma once

#include "flite/lexicon/lexicon.hpp"

cst_lexicon* cmu_grapheme_lex_init(void);

extern const int num_unicode_sampa_mapping;
extern const char* const unicode_sampa_mapping[16663][5];
