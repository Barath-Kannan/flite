#include "flite/flite.hpp"
#include "flite/wavesynth/diphone.hpp"
#include "lex.hpp"
#include "usenglish.hpp"

static cst_utterance* cmu_us_kal_postlex(cst_utterance* u);
extern cst_diphone_db cmu_us_kal_db;

cst_voice* cmu_us_kal_diphone = NULL;

cst_voice* register_cmu_us_kal(const char* voxdir)
{
    cst_voice* v;
    cst_lexicon* lex;

    if (cmu_us_kal_diphone)
        return cmu_us_kal_diphone; /* Already registered */

    v = new_voice();
    v->name = "kal";

    /* Set up basic values for synthesizing with this voice */
    usenglish_init(v);
    flite_feat_set_string(v->features, "name", "cmu_us_kal_diphone");

    /* Lexicon */
    lex = cmu_lex_init();
    flite_feat_set(v->features, "lexicon", lexicon_val(lex));

    /* Intonation */
    flite_feat_set_float(v->features, "int_f0_target_mean", 95.0);
    flite_feat_set_float(v->features, "int_f0_target_stddev", 11.0);

    flite_feat_set_float(v->features, "duration_stretch", 1.1);

    /* Post lexical rules */
    flite_feat_set(v->features, "postlex_func", uttfunc_val(&cmu_us_kal_postlex));

    /* Waveform synthesis: diphone_synth */
    flite_feat_set(v->features, "wave_synth_func", uttfunc_val(&diphone_synth));
    flite_feat_set(v->features, "diphone_db", diphone_db_val(&cmu_us_kal_db));
    flite_feat_set_int(v->features, "sample_rate", cmu_us_kal_db.sts->sample_rate);
    flite_feat_set_string(v->features, "resynth_type", "fixed");
    flite_feat_set_string(v->features, "join_type", "modified_lpc");

    cmu_us_kal_diphone = v;

    return cmu_us_kal_diphone;
}

void unregister_cmu_us_kal(cst_voice* v)
{
    if (v != cmu_us_kal_diphone)
        return;
    delete_voice(v);
    cmu_us_kal_diphone = NULL;
}

static void fix_ah(cst_utterance* u)
{
    /* This should really be done in the index itself */
    const cst_item* s;

    for (s = relation_head(utt_relation(u, "Segment")); s; s = item_next(s))
        if (cst_streq(item_feat_string(s, "name"), "ah"))
            item_set_string(s, "name", "aa");
}

static cst_utterance* cmu_us_kal_postlex(cst_utterance* u)
{
    cmu_postlex(u);
    fix_ah(u);

    return u;
}
