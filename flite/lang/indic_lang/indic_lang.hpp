#pragma once

#include "flite/hrg/utterance.hpp"
#include "flite/lexicon/lexicon.hpp"
#include "flite/regex/regex.hpp"
#include "flite/stats/cart.hpp"
#include "flite/synth/synth.hpp"
#include "flite/synthcommon/phoneset.hpp"
#include "flite/utils/val.hpp"

void cmu_indic_lang_init(cst_voice* v);
extern const cst_phoneset cmu_indic_phoneset;
extern const cst_cart cmu_indic_phrasing_cart;

extern const cst_regex* const cst_rx_not_indic;
