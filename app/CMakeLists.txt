project(flite_app CXX C)
cmake_minimum_required(VERSION 3.2 FATAL_ERROR)
set(CMAKE_CXX_STANDARD 17)

set(S flite_main)
add_executable(flite_main
    ${S}/flite_main.c
    ${S}/flite_lang_list.c
    ${S}/flite_voice_list.c)

target_link_libraries(flite_main
    PUBLIC flite_audio
    PUBLIC flite_hrg
    PUBLIC flite_regex
    PUBLIC flite_stats
    PUBLIC flite_utils
    PUBLIC flite_cg
    PUBLIC flite_lexicon
    PUBLIC flite_speech
    PUBLIC flite_synth
    PUBLIC flite_wavesynth
    PUBLIC flite_cmu_grapheme_lang
    PUBLIC flite_cmu_grapheme_lex
    PUBLIC flite_cmu_indic_lang
    PUBLIC flite_cmu_indic_lex
    PUBLIC flite_cmulex
    PUBLIC flite_cmu_us_kal
    PUBLIC flite_cmu_us_kal16
    PUBLIC flite_cmu_us_slt
    PUBLIC flite_cmu_us_rms
    PUBLIC flite_cmu_us_awb
    PUBLIC flite_usenglish)
