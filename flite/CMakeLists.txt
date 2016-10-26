set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules")
project(flite CXX C)
cmake_minimum_required(VERSION 3.2 FATAL_ERROR)
set(CMAKE_CXX_STANDARD 14)

add_definitions(-DCST_NO_SOCKETS)

if(${WINDOWS})
    set(flite_audio_driver_src src/audio/au_wince.c)
    set(flite_audio_driver_def CST_AUDIO_WINCE)
elseif(${UNIX})
    find_package(ALSA QUIET)
    find_package(PULSEAUDIO QUIET)
    find_package(LINUXAUDIO QUIET)
    if (ALSA_FOUND)
        set(flite_audio_driver_src src/audio/au_alsa.c)
        set(flite_audio_driver_inc ${ALSA_INCLUDE_DIR})
        set(flite_audio_driver_lib  ${ALSA_LIBRARY})
        set(flite_audio_driver_def CST_AUDIO_WINCE)
    elseif (PULSEAUDIO_FOUND)
        set(flite_audio_driver_src src/audio/au_pulseaudio.c)
        set(flite_audio_driver_inc ${PULSEAUDIO_INCLUDE_DIR})
        set(flite_audio_driver_lib  ${PULSEAUDIO_LIBRARY})
        set(flite_audio_driver_def CST_AUDIO_PULSEAUDIO)
    elseif (LINUXAUDIO_FOUND)
    set(flite_audio_driver_src src/audio/au_oss.c)
    set(flite_audio_driver_inc ${LINUXAUDIO_INCLUDE_DIR})
    set(flite_audio_driver_def CST_AUDIO_LINUX)
    else()
        set(flite_audio_driver_src src/audio/au_none.c)
        set(flite_audio_driver_def CST_AUDIO_NONE)
    endif()
else()
    set(flite_audio_driver_src src/audio/au_none.c)
    set(flite_audio_driver_def CST_AUDIO_NONE)
endif()

add_library(flite_audio
    src/audio/auclient.c
    src/audio/auserver.c
    src/audio/audio.c
    src/audio/au_streaming.c
    ${flite_audio_driver_src})

target_include_directories(flite_audio
    PUBLIC inc
    PUBLIC src/audio
    PUBLIC ${flite_audio_driver_inc})

target_link_libraries(flite_audio ${flite_audio_driver_lib})

target_compile_definitions(flite_audio PRIVATE ${flite_audio_driver_def})

add_library(flite_hrg
    src/hrg/cst_utterance.c
    src/hrg/cst_relation.c
    src/hrg/cst_item.c
    src/hrg/cst_ffeature.c
    src/hrg/cst_rel_io.c)

target_include_directories(flite_hrg PUBLIC inc)

add_library(flite_regex
    src/regex/cst_regex.c
    src/regex/regexp.c
    src/regex/regsub.c)

target_include_directories(flite_regex PUBLIC inc PUBLIC src/regex)

add_library(flite_stats
    src/stats/cst_cart.c
    src/stats/cst_viterbi.c
    src/stats/cst_ss.c)

target_include_directories(flite_stats PUBLIC inc)

if(${WINDOWS})
    set(flite_utils_mmap src/utils/cst_mmap_win32.c)
elseif(${UNIX})
    set(flite_utils_mmap src/utils/cst_mmap_posix.c)
else()
    set(flite_utils_mmap src/utils/cst_mmap_none.c)
endif()

add_library(flite_utils
    src/utils/cst_alloc.c
    src/utils/cst_error.c
    src/utils/cst_string.c
    src/utils/cst_wchar.c
    src/utils/cst_tokenstream.c
    src/utils/cst_val.c
    src/utils/cst_features.c
    src/utils/cst_endian.c
    src/utils/cst_socket.c
    src/utils/cst_val_const.c
    src/utils/cst_val_user.c
    src/utils/cst_args.c
    src/utils/cst_url.c
    src/utils/cst_file_stdio.c
    ${flite_utils_mmap})

target_include_directories(flite_utils PUBLIC inc)

add_library(flite_cg
    src/cg/cst_cg.c
    src/cg/cst_mlsa.c
    src/cg/cst_mlpg.c
    src/cg/cst_vc.c
    src/cg/cst_cg_load_voice.c
    src/cg/cst_cg_dump_voice.c
    src/cg/cst_cg_map.c
    src/cg/cst_spamf0.c)

target_include_directories(flite_cg
    PUBLIC inc
    PUBLIC src/flite_cg)

target_link_libraries(flite_cg
    PUBLIC flite_stats)

if(${UNIX})
target_link_libraries(flite_cg
    PUBLIC m)
endif()

add_library(flite_lexicon
    src/lexicon/cst_lexicon.c
    src/lexicon/cst_lts.c
    src/lexicon/cst_lts_rewrites.c)

target_include_directories(flite_lexicon PUBLIC inc)

add_library(flite_speech
    src/speech/cst_wave.c
    src/speech/cst_wave_io.c
    src/speech/cst_track.c
    src/speech/cst_track_io.c
    src/speech/cst_wave_utils.c
    src/speech/cst_lpcres.c
    src/speech/rateconv.c
    src/speech/g721.c
    src/speech/g72x.c
    src/speech/g723_24.c
    src/speech/g723_40.c)

target_include_directories(flite_speech PUBLIC inc PUBLIC src/speech)

add_library(flite_synth
    src/synth/cst_synth.c
    src/synth/cst_utt_utils.c
    src/synth/cst_voice.c
    src/synth/cst_phoneset.c
    src/synth/cst_ffeatures.c
    src/synth/cst_ssml.c
    src/synth/flite.c)

target_include_directories(flite_synth PUBLIC inc)

target_link_libraries(flite_synth
    PUBLIC flite_speech
    PUBLIC flite_cg
    PUBLIC flite_lexicon)

add_library(flite_wavesynth
    src/wavesynth/cst_units.c
    src/wavesynth/cst_clunits.c
    src/wavesynth/cst_diphone.c
    src/wavesynth/cst_sigpr.c
    src/wavesynth/cst_sts.c
    src/wavesynth/cst_reflpc.c)

target_include_directories(flite_wavesynth PUBLIC inc)

add_library(flite_cmu_grapheme_lang
    lang/cmu_grapheme_lang/cmu_grapheme_lang.c
    lang/cmu_grapheme_lang/cmu_grapheme_phrasing_cart.c
    lang/cmu_grapheme_lang/cmu_grapheme_phoneset.c)

target_include_directories(flite_cmu_grapheme_lang
    PUBLIC inc
    PUBLIC lang/cmu_grapheme_lang)

target_link_libraries(flite_cmu_grapheme_lang
    PUBLIC flite_synth)

add_library(flite_cmu_grapheme_lex
    lang/cmu_grapheme_lex/cmu_grapheme_lex.c
    lang/cmu_grapheme_lex/grapheme_unitran_tables.c)

target_include_directories(flite_cmu_grapheme_lex
    PUBLIC inc
    PUBLIC lang/cmu_grapheme_lex)

add_library(flite_cmu_indic_lang
    lang/cmu_indic_lang/cmu_indic_lang.c
    lang/cmu_indic_lang/cmu_indic_phoneset.c
    lang/cmu_indic_lang/cmu_indic_phrasing_cart.c)

target_include_directories(flite_cmu_indic_lang
    PUBLIC inc
    PUBLIC lang/cmu_indic_lang)

target_link_libraries(flite_cmu_indic_lang
    PUBLIC flite_synth)

add_library(flite_cmu_indic_lex
    lang/cmu_indic_lex/cmu_indic_lex.c)

target_include_directories(flite_cmu_indic_lex
    PUBLIC inc
    PUBLIC lang/cmu_indic_lex)

add_library(flite_cmulex
    lang/cmulex/cmu_lex.c
    lang/cmulex/cmu_lex_data.c
    lang/cmulex/cmu_lex_entries.c
    lang/cmulex/cmu_lts_model.c
    lang/cmulex/cmu_lts_rules.c
    lang/cmulex/cmu_postlex.c)

#lang/cmulex/cmu_lex_num_bytes.c
#lang/cmulex/cmu_lex_data_raw.c
#lang/cmulex/cmu_lex_entries_huff_table.c
#lang/cmulex/cmu_lex_phones_huff_table.c

target_include_directories(flite_cmulex
    PUBLIC inc
    PUBLIC lang/cmulex)

add_library(flite_cmu_time_awb
    lang/cmu_time_awb/cmu_time_awb.c
    lang/cmu_time_awb/cmu_time_awb_cart.c
    lang/cmu_time_awb/cmu_time_awb_clunits.c
    lang/cmu_time_awb/cmu_time_awb_lex_entry.c
    lang/cmu_time_awb/cmu_time_awb_lpc.c
    lang/cmu_time_awb/cmu_time_awb_mcep.c)

target_include_directories(flite_cmu_time_awb
    PUBLIC inc
    PUBLIC lang/cmu_time_awb
    PUBLIC lang/usenglish
    PUBLIC lang/cmulex)

add_library(flite_cmu_us_kal
    lang/cmu_us_kal/cmu_us_kal.c
    lang/cmu_us_kal/cmu_us_kal_diphone.c
    lang/cmu_us_kal/cmu_us_kal_lpc.c
    lang/cmu_us_kal/cmu_us_kal_res.c
    lang/cmu_us_kal/cmu_us_kal_residx.c
    lang/cmu_us_kal/cmu_us_kal_ressize.c)

target_include_directories(flite_cmu_us_kal
    PUBLIC inc
    PUBLIC lang/cmu_us_kal
    PUBLIC lang/usenglish
    PUBLIC lang/cmulex)

add_library(flite_cmu_us_kal16
    lang/cmu_us_kal16/cmu_us_kal16.c
    lang/cmu_us_kal16/cmu_us_kal16_diphone.c
    lang/cmu_us_kal16/cmu_us_kal16_lpc.c
    lang/cmu_us_kal16/cmu_us_kal16_res.c
    lang/cmu_us_kal16/cmu_us_kal16_residx.c)

target_include_directories(flite_cmu_us_kal16
    PUBLIC inc
    PUBLIC lang/cmu_us_kal16
    PUBLIC lang/usenglish
    PUBLIC lang/cmulex)

add_library(flite_cmu_us_rms
    lang/cmu_us_rms/cmu_us_rms.c
    lang/cmu_us_rms/cmu_us_rms_cg.c
    lang/cmu_us_rms/cmu_us_rms_cg_durmodel.c
    lang/cmu_us_rms/cmu_us_rms_cg_f0_trees.c
    lang/cmu_us_rms/cmu_us_rms_cg_phonestate.c
    lang/cmu_us_rms/cmu_us_rms_cg_single_mcep_trees.c
    lang/cmu_us_rms/cmu_us_rms_cg_single_params.c
    lang/cmu_us_rms/cmu_us_rms_spamf0_accent.c
    lang/cmu_us_rms/cmu_us_rms_spamf0_accent_params.c
    lang/cmu_us_rms/cmu_us_rms_spamf0_phrase.c)

target_include_directories(flite_cmu_us_rms
    PUBLIC inc
    PUBLIC lang/cmu_us_rms
    PUBLIC lang/usenglish
    PUBLIC lang/cmulex)

add_library(flite_cmu_us_slt
    lang/cmu_us_slt/cmu_us_slt.c
    lang/cmu_us_slt/cmu_us_slt_cg.c
    lang/cmu_us_slt/cmu_us_slt_cg_durmodel.c
    lang/cmu_us_slt/cmu_us_slt_cg_f0_trees.c
    lang/cmu_us_slt/cmu_us_slt_cg_phonestate.c
    lang/cmu_us_slt/cmu_us_slt_cg_single_mcep_trees.c
    lang/cmu_us_slt/cmu_us_slt_cg_single_params.c
    lang/cmu_us_slt/cmu_us_slt_spamf0_accent.c
    lang/cmu_us_slt/cmu_us_slt_spamf0_accent_params.c
    lang/cmu_us_slt/cmu_us_slt_spamf0_phrase.c)

target_include_directories(flite_cmu_us_slt
    PUBLIC inc
    PUBLIC lang/cmu_us_slt
    PUBLIC lang/usenglish
    PUBLIC lang/cmulex)

add_library(flite_usenglish
    lang/usenglish/us_aswd.c
    lang/usenglish/us_dur_stats.c
    lang/usenglish/us_durz_cart.c
    lang/usenglish/usenglish.c
    lang/usenglish/us_expand.c
    lang/usenglish/us_f0lr.c
    lang/usenglish/us_f0_model.c
    lang/usenglish/us_ffeatures.c
    lang/usenglish/us_gpos.c
    lang/usenglish/us_int_accent_cart.c
    lang/usenglish/us_int_tone_cart.c
    lang/usenglish/us_nums_cart.c
    lang/usenglish/us_phoneset.c
    lang/usenglish/us_phrasing_cart.c
    lang/usenglish/us_pos_cart.c
    lang/usenglish/us_text.c)

target_include_directories(flite_usenglish
    PUBLIC inc
    PUBLIC lang/usenglish)

target_link_libraries(flite_usenglish
    PUBLIC flite_utils)

add_executable(flite_main
    src/main/flite_main.c
    src/main/flite_lang_list.c
    src/main/flite_voice_list.c)

target_include_directories(flite_main
    PUBLIC inc)

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
    PUBLIC flite_usenglish)
