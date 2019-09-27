#pragma once

#include "flite/audio/audio.hpp"
#include "flite/hrg/item.hpp"
#include "flite/hrg/relation.hpp"
#include "flite/hrg/utterance.hpp"
#include "flite/lexicon/lexicon.hpp"
#include "flite/regex/regex.hpp"
#include "flite/stats/cart.hpp"
#include "flite/synth/synth.hpp"
#include "flite/synth/voice.hpp"
#include "flite/synthcommon/phoneset.hpp"
#include "flite/synthcommon/track.hpp"
#include "flite/synthcommon/utt_utils.hpp"
#include "flite/synthcommon/wave.hpp"
#include "flite/utils/features.hpp"
#include "flite/utils/string.hpp"
#include "flite/utils/tokenstream.hpp"
#include "flite/utils/val.hpp"
#include "flite/wavesynth/units.hpp"

#ifdef WIN32
/* For Visual Studio 2012 global variable definitions */
#define GLOBALVARDEF __declspec(dllexport)
#else
#define GLOBALVARDEF
#endif
extern GLOBALVARDEF cst_val* flite_voice_list;
extern GLOBALVARDEF cst_lang flite_lang_list[20];
extern GLOBALVARDEF int flite_lang_list_length;

/* Public functions */
int flite_init();

/* General top level functions */
cst_voice* flite_voice_select(const char* name);
cst_voice* flite_voice_load(const char* voice_filename);
int flite_voice_dump(cst_voice* voice, const char* voice_filename);
float flite_file_to_speech(const char* filename, cst_voice* voice, const char* outtype);
float flite_text_to_speech(const char* text, cst_voice* voice, const char* outtype);
float flite_phones_to_speech(const char* text, cst_voice* voice, const char* outtype);
float flite_ssml_file_to_speech(const char* filename, cst_voice* voice, const char* outtype);
float flite_ssml_text_to_speech(const char* text, cst_voice* voice, const char* outtype);
int flite_voice_add_lex_addenda(cst_voice* v, const cst_string* lexfile);

/* Lower lever user functions */
cst_wave* flite_text_to_wave(const char* text, cst_voice* voice);
cst_utterance* flite_synth_text(const char* text, cst_voice* voice);
cst_utterance* flite_synth_phones(const char* phones, cst_voice* voice);

float flite_ts_to_speech(cst_tokenstream* ts, cst_voice* voice, const char* outtype);
cst_utterance* flite_do_synth(cst_utterance* u, cst_voice* voice, cst_uttfunc synth);
float flite_process_output(cst_utterance* u, const char* outtype, int append);

/* flite public export wrappers for features access */
int flite_get_param_int(const cst_features* f, const char* name, int def);
float flite_get_param_float(const cst_features* f, const char* name, float def);
const char* flite_get_param_string(const cst_features* f, const char* name, const char* def);
const cst_val* flite_get_param_val(const cst_features* f, const char* name, cst_val* def);
void flite_feat_set_int(cst_features* f, const char* name, int v);
void flite_feat_set_float(cst_features* f, const char* name, float v);
void flite_feat_set_string(cst_features* f, const char* name, const char* v);
void flite_feat_set(cst_features* f, const char* name, const cst_val* v);
int flite_feat_remove(cst_features* f, const char* name);

const char* flite_ffeature_string(const cst_item* item, const char* featpath);
int flite_ffeature_int(const cst_item* item, const char* featpath);
float flite_ffeature_float(const cst_item* item, const char* featpath);
const cst_val* flite_ffeature(const cst_item* item, const char* featpath);
cst_item* flite_path_to_item(const cst_item* item, const char* featpath);

/* These functions are *not* thread-safe, they are designed to be called */
/* before the initial synthesis occurs */
int flite_add_voice(cst_voice* voice);
int flite_add_lang(const char* langname, void (*lang_init)(cst_voice* vox), cst_lexicon* (*lex_init)());
/* These are init functions for generic grapheme based voices */
void utf8_grapheme_lang_init(cst_voice* v);
cst_lexicon* utf8_grapheme_lex_init(void);
