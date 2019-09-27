#pragma once

#include "flite/audio/audio.hpp"
#include "flite/stats/cart.hpp"
#include "flite/synth/voice.hpp"
#include "flite/synthcommon/dur_stat.hpp"
#include "flite/synthcommon/phoneset.hpp"
#include "flite/synthcommon/track.hpp"
#include "flite/synthcommon/wave.hpp"

/* The parameters in the spectral model(s) may be encoded in various ways */
/* mostly to preserve space.  The decoder can be dependent on the shape type */
/* This needs to be coordinated with the model creation in make_cg.scm */
/* This is currently very BIG_HAMMER-like and hard coded */

/* Original rf3 (and before) encoding stddev follows mean in pairs:
   F0 (1), MCEP_STATIC (25), MCEP_DELTA (25), ME (5), Voicing (1)  (114 shorts)
   Encoded as linear range in unsigned short from min over range */
#define CST_CG_MODEL_SHAPE_BASE_MINRANGE 1
/* Quantized rf3, encode everything as two 8 bit values in each short.
   Good generic quantized version, but the next one is used for most models
   (57 shorts)
   */
#define CST_CG_MODEL_SHAPE_QUANTIZED_PARAMS 2
/* Quantized rf3, (mostly stddev follows mean in pairs -- except deltas 
   no F0, MCEP_STATIC (50) MCEP_DELTAS stddev (25), ME (5), Voice (2) 
   Encoded as unsigned chars that index into qtable.  we don't include
   the mcep_deltas means, they aren't needed.  They are still held as shorts
   so you need to sub index them see cst_cg_quantized_params_index() 
   (41 shorts) */
#define CST_CG_MODEL_SHAPE_QUANTIZED_PARAMS_41 3

typedef struct cst_cg_db_struct {
    /* Please do not change this structure, but if you do, only add things
       to the end of the struct.  If do you change it , please modify 
       dump/load voice too (in cst_cg_dump_voice and cst_cg_map) */
    const char* name;
    const char* const* types;
    int num_types;

    int sample_rate;

    float f0_mean, f0_stddev;

    /* Cluster trees */
    int num_f0_models;
    const cst_cart*** f0_trees;

    int num_param_models;
    const cst_cart*** param_trees;

    const cst_cart* spamf0_accent_tree; /* spam accent tree */
    const cst_cart* spamf0_phrase_tree; /* spam phrase tree */

    /* Model params e.g. mceps, deltas intersliced with stddevs */
    /* may be compressed/quantized based on value of model_shape */
    int* num_channels;
    int* num_frames;
    const unsigned short*** model_vectors;

    int num_channels_spamf0_accent;
    int num_frames_spamf0_accent;
    const float* const* spamf0_accent_vectors;

    /* Currently shared between different models */
    const float* model_min;   /* for vector coeffs encoding */
    const float* model_range; /* for vector coeffs encoding */

    const float*** qtable; /* q(uantization) tables for each model */

    int model_shape; /* model compression technique */

    float frame_advance;

    /* duration models (cart + phonedurs) */
    int num_dur_models;
    const dur_stat*** dur_stats;
    const cst_cart** dur_cart;

    /* phone to states map */
    const char* const* const* phone_states;

    /* Other parameters */
    int do_mlpg; /* implies deltas are in the model_vectors */
    float* dynwin;
    int dynwinsize;

    float mlsa_alpha;
    float mlsa_beta;

    int multimodel;
    int mixed_excitation;

    /* filters for Mixed Excitation */
    int ME_num;
    int ME_order;
    const double* const* me_h;

    int spamf0;
    float gain;

    /* If its a "grapheme" voice there will be a phoneset and a char_map */
    const cst_phoneset* phoneset;
    const char* const* char_sym_map;  /* Unicode char to symbol map */
    const char* const* sym_phone_map; /* symbol to phone map */

    int freeable; /* doesn't get dumped, but 1 when this a freeable struct */

} cst_cg_db;

CST_VAL_USER_TYPE_DCLS(cg_db, cst_cg_db)
void delete_cg_db(cst_cg_db* db);

cst_utterance* cg_synth(cst_utterance* utt);
cst_wave* mlsa_resynthesis(const cst_track* t, const cst_track* str, cst_cg_db* cg_db, cst_audio_streaming_info* asc, int mlsa_speech_param);
cst_track* mlpg(const cst_track* param_track, cst_cg_db* cg_db);

cst_voice* cst_cg_load_voice(const char* voxdir, const cst_lang lang_table[]);
int cst_cg_dump_voice(const cst_voice* v, const cst_string* filename);
