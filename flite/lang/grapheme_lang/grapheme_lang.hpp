#pragma once

#include "flite/hrg/utterance.hpp"
#include "flite/lexicon/lexicon.hpp"
#include "flite/stats/cart.hpp"
#include "flite/synth/synth.hpp"
#include "flite/synthcommon/phoneset.hpp"
#include "flite/utils/val.hpp"

void cmu_grapheme_lang_init(cst_voice* v);
extern const cst_phoneset cmu_grapheme_phoneset;
extern const cst_cart cmu_grapheme_phrasing_cart;
