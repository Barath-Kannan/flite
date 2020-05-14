#pragma once

#include "flite/hrg/utterance.hpp"
#include "flite/lexicon/lexicon.hpp"
#include "flite/stats/cart.hpp"
#include "flite/synth/synth.hpp"
#include "flite/synthcommon/phoneset.hpp"
#include "flite/utils/val.hpp"

/* Voices call this to use usenglish. */
void usenglish_init(cst_voice* v);

/* Default functions and values that you might need. */
cst_utterance* us_f0_model(cst_utterance* u);
extern const cst_phoneset us_phoneset;
extern const cst_cart us_phrasing_cart;
extern const cst_cart us_int_accent_cart;
extern const cst_cart us_int_tone_cart;
extern const cst_cart us_durz_cart;
extern const cst_cart us_pos_cart;
extern const dur_stat* const us_dur_stats[];

