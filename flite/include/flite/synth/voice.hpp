#pragma once

#include "flite/hrg/relation.hpp"
#include "flite/hrg/utterance.hpp"
#include "flite/lexicon/lexicon.hpp"
#include "flite/utils/features.hpp"
#include "flite/utils/file.hpp"
#include "flite/utils/val.hpp"

#include <string_view>

struct cst_voice_struct {
    const char* name;

    cst_features* features;
    cst_features* ffunctions;

    /* This hook is called (from utt_init()) after the input text (if
       any) has been set and voice features have been copied in, but
       before synthesis. */
    cst_utterance* (*utt_init)(cst_utterance* u, struct cst_voice_struct* v);
};

typedef struct cst_voice_struct cst_voice;

/* Hold pointers to language and lexicon init function */
struct cst_lang_struct {
    const char* lang;
    void (*lang_init)(cst_voice* vox);
    cst_lexicon* (*lex_init)();
};
typedef struct cst_lang_struct cst_lang;

/* Constructor functions */
cst_voice* new_voice();
void delete_voice(cst_voice* u);

/* for voices with external voxdata */
int flite_mmap_clunit_voxdata(const char* voxdir, cst_voice* voice);
int flite_munmap_clunit_voxdata(cst_voice* voice);

cst_voice* cst_cg_load_voice(const char* voxdir, const cst_lang lang_table[]);
int cst_cg_dump_voice(const cst_voice* v, const cst_string* filename);

CST_VAL_USER_TYPE_DCLS(voice, cst_voice)

namespace flite {

class voice {
public:
    voice() noexcept;
    voice(std::string_view voxdir, cst_lang lang_table[]);

    voice(voice&&) noexcept;
    voice& operator=(voice&&) noexcept;
    voice(const voice&) = delete;
    voice& operator=(const voice&) = delete;

    ~voice();

    auto operator-> () -> cst_voice*;
    auto operator-> () const -> const cst_voice*;

private:
    cst_voice* _voice;
};

} // namespace flite
