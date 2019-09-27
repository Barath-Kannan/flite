#include "usenglish.hpp"

#include "flite/flite.hpp"
#include "us_f0.hpp"
#include "us_ffeatures.hpp"
#include "us_text.hpp"

static const char* const us_english_punctuation = "\"'`.,:;!?(){}[]";
static const char* const us_english_prepunctuation = "\"'`({[";
static const char* const us_english_singlecharsymbols = "";
static const char* const us_english_whitespace = " \t\n\r";

void usenglish_init(cst_voice* v)
{
    /* utterance break function */
    feat_set(v->features, "utt_break", breakfunc_val(&default_utt_break));

    /* Phoneset */
    feat_set(v->features, "phoneset", phoneset_val(&us_phoneset));
    feat_set_string(v->features, "silence", us_phoneset.silence);

    /* Text analyser */
    feat_set_string(v->features, "text_whitespace", us_english_whitespace);
    feat_set_string(v->features, "text_postpunctuation", us_english_punctuation);
    feat_set_string(v->features, "text_prepunctuation", us_english_prepunctuation);
    feat_set_string(v->features, "text_singlecharsymbols", us_english_singlecharsymbols);

    feat_set(v->features, "tokentowords_func", itemfunc_val(&us_tokentowords));

    /* very simple POS tagger */
    feat_set(v->features, "pos_tagger_cart", cart_val(&us_pos_cart));

    /* Phrasing */
    feat_set(v->features, "phrasing_cart", cart_val(&us_phrasing_cart));

    /* Intonation */
    feat_set(v->features, "int_cart_accents", cart_val(&us_int_accent_cart));
    feat_set(v->features, "int_cart_tones", cart_val(&us_int_tone_cart));

    /* Duration */
    feat_set(v->features, "dur_cart", cart_val(&us_durz_cart));
    feat_set(v->features, "dur_stats", dur_stats_val((dur_stats*)us_dur_stats));

    /* f0 model */
    feat_set(v->features, "f0_model_func", uttfunc_val(&us_f0_model));

    us_ff_register(v->ffunctions);
}
