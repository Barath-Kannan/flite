#include "flite/flite.hpp"
#include "flite/wavesynth/diphone.hpp"
#include "lex.hpp"
#include "usenglish.hpp"

#include <string.h>

extern cst_diphone_db cmu_us_kal16_db;

cst_voice* cmu_us_kal16_diphone = NULL;

cst_voice* register_cmu_us_kal16(const char* voxdir)
{
    cst_voice* v;
    cst_lexicon* lex;

    if (cmu_us_kal16_diphone)
        return cmu_us_kal16_diphone; /* Already registered */

    v = new_voice();
    v->name = "kal16";

    /* Sets up language specific parameters in the cmu_us_kal16. */
    usenglish_init(v);

    feat_set_string(v->features, "name", "cmu_us_kal16");

    feat_set_float(v->features, "int_f0_target_mean", 95.0);
    feat_set_float(v->features, "int_f0_target_stddev", 11.0);

    feat_set_float(v->features, "duration_stretch", 1.1);

    /* Lexicon */
    lex = cmu_lex_init();
    feat_set(v->features, "lexicon", lexicon_val(lex));
    feat_set(v->features, "postlex_func", uttfunc_val(lex->postlex));

    /* Waveform synthesis */
    feat_set(v->features, "wave_synth_func", uttfunc_val(&diphone_synth));
    feat_set(v->features, "diphone_db", diphone_db_val(&cmu_us_kal16_db));
    feat_set_int(v->features, "sample_rate", cmu_us_kal16_db.sts->sample_rate);
    /*    feat_set_string(v->features,"join_type","simple_join"); */
    feat_set_string(v->features, "join_type", "modified_lpc");
    feat_set_string(v->features, "resynth_type", "fixed");

    cmu_us_kal16_diphone = v;

    return cmu_us_kal16_diphone;
}

void unregister_cmu_us_kal16(cst_voice* vox)
{
    if (vox != cmu_us_kal16_diphone)
        return;
    delete_voice(vox);
    cmu_us_kal16_diphone = NULL;
}
