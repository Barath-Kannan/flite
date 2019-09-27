#pragma once

#include "flite/lexicon/lexicon.hpp"

cst_lexicon* cmu_indic_lex_init(void);

enum cmu_indic_char_type
{
    IND_INDEPENDENT_VOWEL,
    IND_CONSONANT,
    IND_VOWEL,
    IND_ANUSWAAR,
    IND_VISARGA,
    IND_NUKTA,
    IND_AVAGRAHA,
    IND_HALANT,
    IND_DIGIT,
    IND_PUNC,
    IND_IGNORE,
    IND_ADDAK
};

struct cmu_indic_char {
    enum cmu_indic_char_type type;
    char phoneme[12];
} indic_char;
