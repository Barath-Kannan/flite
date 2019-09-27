#include "flite/cg/cg.hpp"
#include "flite/flite.hpp"

#include <string.h>

/* This isn't language independent .. */
#include "lex.hpp"
#include "usenglish.hpp"

extern cst_cg_db cmu_us_awb_cg_db;
cst_voice* cmu_us_awb_cg = NULL;

cst_voice* register_cmu_us_awb(const char* voxdir)
{
    cst_voice* vox;
    cst_lexicon* lex;

    if (cmu_us_awb_cg)
        return cmu_us_awb_cg; /* Already registered */

    vox = new_voice();
    vox->name = "awb";

    /* Sets up language specific parameters in the cmu_us_awb. */
    usenglish_init(vox);

    /* Things that weren't filled in already. */
    flite_feat_set_string(vox->features, "name", "cmu_us_awb");

    /* Lexicon */
    lex = cmu_lex_init();
    flite_feat_set(vox->features, "lexicon", lexicon_val(lex));
    flite_feat_set(vox->features, "postlex_func", uttfunc_val(lex->postlex));

    /* No standard segment durations are needed as its done at the */
    /* HMM state level */
    feat_set_string(vox->features, "no_segment_duration_model", "1");
    feat_set_string(vox->features, "no_f0_target_model", "1");

    /* Waveform synthesis */
    flite_feat_set(vox->features, "wave_synth_func", uttfunc_val(&cg_synth));
    flite_feat_set(vox->features, "cg_db", cg_db_val(&cmu_us_awb_cg_db));
    flite_feat_set_int(vox->features, "sample_rate", cmu_us_awb_cg_db.sample_rate);

    cmu_us_awb_cg = vox;

    return cmu_us_awb_cg;
}

void unregister_cmu_us_awb(cst_voice* vox)
{
    if (vox != cmu_us_awb_cg)
        return;
    delete_voice(vox);
    cmu_us_awb_cg = NULL;
}
