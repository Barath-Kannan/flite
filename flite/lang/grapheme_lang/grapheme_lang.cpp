#include "./grapheme_lang.hpp"

#include "flite/flite.hpp"
#include "flite/lexicon/lexicon.hpp"
#include "flite/synth/ffeatures.hpp"
#include "flite/synth/voice.hpp"
#include "flite/utils/val.hpp"

static cst_val* cmu_grapheme_tokentowords(cst_item* token)
{
    /* Return list of words that expand token/name */
    cst_val* r;
    const char* name;

    name = item_name(token);

    if (item_feat_present(token, "phones"))
        return cons_val(string_val(name), NULL);

#if 0
    if (item_feat_present(token,"nsw"))
	nsw = item_feat_string(token,"nsw");

    utt = item_utt(token);
    lex = val_lexicon(feat_val(utt->features,"lexicon"));
#endif

    if (cst_strlen(name) > 0)
        r = cons_val(string_val(name), 0);
    else
        r = NULL;

    return r;
}

int grapheme_utt_break(cst_tokenstream* ts, const char* token, cst_relation* tokens)
{
    /* We'll respect Latin punctuation */
    const char* postpunct = item_feat_string(relation_tail(tokens), "punc");
    /* const char *ltoken = item_name(relation_tail(tokens)); */

    if (cst_strchr(ts->whitespace, '\n') != cst_strrchr(ts->whitespace, '\n'))
        /* contains two new lines */
        return TRUE;
    else if (strchr(postpunct, ':') || strchr(postpunct, '?') || strchr(postpunct, '!'))
        return TRUE;
    else if (strchr(postpunct, '.'))
        return TRUE;
    else
        return FALSE;
}

void cmu_grapheme_lang_init(cst_voice* v)
{
    /* Set grapheme language stuff */
    feat_set_string(v->features, "language", "cmu_grapheme_lang");

    /* utterance break function */
    feat_set(v->features, "utt_break", breakfunc_val(&grapheme_utt_break));

    /* Phoneset -- need to get this from voice */
    feat_set(v->features, "phoneset", phoneset_val(&cmu_grapheme_phoneset));
    feat_set_string(v->features, "silence", cmu_grapheme_phoneset.silence);

    /* Get information from voice and add to lexicon */

    /* Text analyser -- whitespace defaults */
    feat_set_string(v->features, "text_whitespace", cst_ts_default_whitespacesymbols);
    feat_set_string(v->features, "text_postpunctuation", cst_ts_default_postpunctuationsymbols);
    feat_set_string(v->features, "text_prepunctuation", cst_ts_default_prepunctuationsymbols);
    feat_set_string(v->features, "text_singlecharsymbols", cst_ts_default_singlecharsymbols);

    /* Tokenization tokenization function */
    feat_set(v->features, "tokentowords_func", itemfunc_val(&cmu_grapheme_tokentowords));
    /* Pos tagger (gpos)/induced pos */
    /* Phrasing */
    feat_set(v->features, "phrasing_cart", cart_val(&cmu_grapheme_phrasing_cart));
    /* Intonation, Duration and F0 -- part of cg */
    feat_set_string(v->features, "no_intonation_accent_model", "1");

    /* Default ffunctions (required) */
    basic_ff_register(v->ffunctions);

    return;
}
