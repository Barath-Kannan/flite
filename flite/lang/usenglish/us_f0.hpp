#pragma once

#include "flite/hrg/utterance.hpp"

struct us_f0_lr_term_struct {
    const char* feature;
    const float start;
    const float mid;
    const float end;
    const char* type;
};
typedef struct us_f0_lr_term_struct us_f0_lr_term;

extern const us_f0_lr_term f0_lr_terms[];

cst_utterance* us_f0_model(cst_utterance* u);
