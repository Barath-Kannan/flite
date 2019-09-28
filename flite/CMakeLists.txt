set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules")
project(flite CXX C)
cmake_minimum_required(VERSION 3.11 FATAL_ERROR)
set(CMAKE_CXX_STANDARD 17)

set(H include/flite/utils)
set(S src/utils)

if(${WIN32})
    set(flite_utils_mmap ${S}/mmap_win32.cpp)
elseif(${UNIX})
    set(flite_utils_mmap ${S}/mmap_posix.cpp)
else()
    set(flite_utils_mmap ${S}/mmap_none.cpp)
endif()

add_library(flite_utils
    ${H}/alloc.hpp ${S}/alloc.cpp
    ${H}/args.hpp ${S}/args.cpp
    ${H}/endian.hpp ${S}/endian.cpp
    ${H}/error.hpp ${S}/error.cpp
    ${H}/features.hpp ${S}/features.cpp
    ${H}/file.hpp ${S}/file.cpp ${S}/url.cpp
    ${H}/math.hpp
    ${H}/socket.hpp ${S}/socket.cpp
    ${H}/string.hpp ${S}/string.cpp
    ${H}/tokenstream.hpp ${S}/tokenstream.cpp
    ${H}/val.hpp ${S}/val.cpp
    ${H}/val_const.hpp ${S}/val_const.cpp
    ${H}/val_defs.hpp
    ${S}/val_user.cpp
    ${H}/wchar.hpp ${S}/wchar.cpp
    ${flite_utils_mmap})

target_include_directories(flite_utils PUBLIC include)

if(${WIN32})
    target_link_libraries(flite_utils
        PUBLIC WSock32)
endif()

set(H include/flite/hrg)
set(S src/hrg)

add_library(flite_hrg
    ${H}/hrg.hpp
    ${H}/item.hpp ${S}/item.cpp
    ${H}/utterance.hpp ${S}/utterance.cpp
    ${H}/relation.hpp ${S}/relation.cpp
    ${S}/ffeature.cpp
    ${S}/rel_io.cpp)

target_link_libraries(flite_hrg
    PUBLIC flite_utils)

set(H include/flite/lexicon)
set(S src/lexicon)

add_library(flite_lexicon
    ${H}/lexicon.hpp ${S}/lexicon.cpp
    ${H}/lts.hpp ${S}/lts.cpp
    ${H}/lts_rewrites.hpp ${S}/lts_rewrites.cpp)

target_link_libraries(flite_lexicon
    PUBLIC flite_utils)

set(H include/flite/regex)
set(S src/regex)

add_library(flite_regex
    ${H}/regex.hpp ${S}/regex.cpp
    ${S}/regexp.cpp
    ${S}/regsub.cpp
    ${S}/regex_defs.hpp)

target_link_libraries(flite_regex
    PUBLIC flite_utils)

set(H include/flite/stats)
set(S src/stats)

add_library(flite_stats
    ${H}/cart.hpp ${S}/cart.cpp
    ${H}/viterbi.hpp ${S}/viterbi.cpp
    ${H}/ss.hpp ${S}/ss.cpp)

target_link_libraries(flite_stats
    PUBLIC flite_utils
    PUBLIC flite_hrg
    PUBLIC flite_regex)

set(H include/flite/synthcommon)
set(S src/synthcommon)

add_library(flite_synthcommon
    ${H}/dur_stat.hpp ${S}/dur_stat.cpp
    ${H}/phoneset.hpp ${S}/phoneset.cpp
    ${H}/track.hpp ${S}/track.cpp
    ${H}/utt_utils.hpp ${S}/utt_utils.cpp
    ${H}/wave.hpp ${S}/wave.cpp)

target_link_libraries(flite_synthcommon
    flite_utils
    flite_hrg)

set(H include/flite/audio)
set(S src/audio)

if(${WIN32})
    set(flite_audio_driver_src ${S}/wince.cpp)
    set(flite_audio_driver_def CST_AUDIO_WINCE)
	SET(FLITE_AUDIO_DRIVER_LIB wINMM)
elseif(${UNIX})
    find_package(ALSA QUIET)
    find_package(PULSEAUDIO QUIET)
    find_package(LINUXAUDIO QUIET)
    if (ALSA_FOUND)
        set(flite_audio_driver_src ${S}/alsa.cpp)
        set(flite_audio_driver_inc ${ALSA_INCLUDE_DIR})
        set(flite_audio_driver_lib  ${ALSA_LIBRARY})
        set(flite_audio_driver_def CST_AUDIO_WINCE)
    elseif (PULSEAUDIO_FOUND)
        set(flite_audio_driver_src ${S}/pulseaudio.cpp)
        set(flite_audio_driver_inc ${PULSEAUDIO_INCLUDE_DIR})
        set(flite_audio_driver_lib  ${PULSEAUDIO_LIBRARY})
        set(flite_audio_driver_def CST_AUDIO_PULSEAUDIO)
    elseif (LINUXAUDIO_FOUND)
        set(flite_audio_driver_src ${S}/oss.cpp)
        set(flite_audio_driver_inc ${LINUXAUDIO_INCLUDE_DIR})
        set(flite_audio_driver_def CST_AUDIO_LINUX)
    else()
        set(flite_audio_driver_src ${S}/none.cpp)
        set(flite_audio_driver_def CST_AUDIO_NONE)
    endif()
else()
    set(flite_audio_driver_src ${S}/none.cpp)
    set(flite_audio_driver_def CST_AUDIO_NONE)
endif()

add_library(flite_audio
    ${H}/audio.hpp ${S}/audio.cpp
    ${S}/client.cpp
    ${S}/server.cpp
    ${S}/native_audio.hpp
    ${S}/streaming.cpp
    ${flite_audio_driver_src})

target_include_directories(flite_audio
    PUBLIC ${flite_audio_driver_inc})

target_link_libraries(flite_audio
    PUBLIC flite_utils
    PUBLIC flite_hrg
    PUBLIC flite_synthcommon
    PUBLIC ${flite_audio_driver_lib})

target_compile_definitions(flite_audio
    PRIVATE ${flite_audio_driver_def})

set(H include/flite/wavesynth)
set(S src/wavesynth)

add_library(flite_wavesynth
    ${H}/units.hpp ${S}/units.cpp
    ${H}/clunits.hpp ${S}/clunits.cpp
    ${H}/diphone.hpp ${S}/diphone.cpp
    ${H}/sigpr.hpp ${S}/sigpr.cpp
    ${H}/sts.hpp ${S}/sts.cpp
    ${S}/reflpc.cpp)

target_link_libraries(flite_wavesynth 
    PUBLIC flite_utils
    PUBLIC flite_hrg
    PUBLIC flite_synthcommon
    PUBLIC flite_stats
    PUBLIC flite_audio)

set(H include/flite/synth)
set(S src/synth)

add_library(flite_synth
    ${H}/ffeatures.hpp ${S}/ffeatures.cpp
    ${H}/synth.hpp ${S}/synth.cpp
    ${H}/voice.hpp ${S}/voice.cpp)

target_link_libraries(flite_synth
    PUBLIC flite_utils
    PUBLIC flite_lexicon
    PUBLIC flite_hrg
    PUBLIC flite_regex
    PUBLIC flite_stats
    PUBLIC flite_synthcommon
    PUBLIC flite_wavesynth)

set(H include/flite/cg)
set(S src/cg)

add_library(flite_cg
    ${H}/cg.hpp ${S}/cg.cpp
    ${S}/cg_load_voice.cpp
    ${S}/cg_dump_voice.cpp
    ${S}/cg_map.hpp ${S}/cg_map.cpp
    ${S}/mlsa.hpp ${S}/mlsa.cpp
    ${S}/mlpg.hpp ${S}/mlpg.cpp
    ${S}/spamf0.hpp ${S}/spamf0.cpp
    ${S}/vc.hpp ${S}/vc.cpp)

target_link_libraries(flite_cg
    PUBLIC flite_stats
    PUBLIC flite_audio
    PUBLIC flite_wavesynth
    PUBLIC flite_synth)

#if(${UNIX})
#target_link_libraries(flite_cg
#    PUBLIC m)
#endif()

set(S src/speech)
add_library(flite_speech
    ${S}/g721.cpp
    ${S}/g72x.cpp ${S}/g72x.hpp
    ${S}/g723_24.cpp
    ${S}/g723_40.cpp
    ${S}/lpcres.cpp
    ${S}/rateconv.cpp
    ${S}/track_io.cpp
    ${S}/wave_io.cpp
    ${S}/wave_utils.cpp)

target_link_libraries(flite_speech
    PUBLIC flite_utils
    PUBLIC flite_synthcommon)

set(H include/flite)
set(S src)

add_library(flite
    ${H}/flite.hpp ${S}/flite.cpp
    ${S}/ssml.cpp)

target_link_libraries(flite
    PUBLIC flite_cg
    PUBLIC flite_speech)

set(S lang/grapheme_lang)
add_library(flite_grapheme_lang
    ${S}/grapheme_lang.hpp ${S}/grapheme_lang.cpp
    ${S}/grapheme_phrasing_cart.hpp ${S}/grapheme_phrasing_cart.cpp
    ${S}/grapheme_phoneset.cpp)

target_link_libraries(flite_grapheme_lang
    PUBLIC flite)

set(S lang/grapheme_lex)
add_library(flite_grapheme_lex
    ${S}/grapheme_lex.hpp ${S}/grapheme_lex.cpp
    ${S}/grapheme_unitran_tables.cpp)

target_link_libraries(flite_grapheme_lex
    PUBLIC flite)

set(S lang/indic_lang)
add_library(flite_indic_lang
    ${S}/indic_eng_num_table.hpp
    ${S}/indic_guj_num_table.hpp
    ${S}/indic_hin_num_table.hpp
    ${S}/indic_kan_num_table.hpp
    ${S}/indic_lang.hpp ${S}/indic_lang.cpp
    ${S}/indic_mar_num_table.hpp
    ${S}/indic_num_table.hpp
    ${S}/indic_pan_num_table.hpp
    ${S}/indic_phoneset.cpp
    ${S}/indic_phrasing_cart.hpp ${S}/indic_phrasing_cart.cpp
    ${S}/indic_san_num_table.hpp
    ${S}/indic_tam_num_table.hpp
    ${S}/indic_tel_num_table.hpp)

target_link_libraries(flite_indic_lang
    PUBLIC flite)

set(S lang/indic_lex)
add_library(flite_indic_lex
    ${S}/indic_lex.hpp ${S}/indic_lex.cpp)

target_link_libraries(flite_indic_lex
    PUBLIC flite
    PUBLIC flite_lex)

set(S lang/lex)
add_library(flite_lex
    ${S}/lex.hpp ${S}/lex.cpp
    ${S}/lex_data.cpp
    ${S}/lex_entries.cpp
    ${S}/lts_model.hpp ${S}/lts_model.cpp
    ${S}/lts_rules.cpp
    ${S}/postlex.cpp)

target_link_libraries(flite_lex
    PUBLIC flite)

target_include_directories(flite_lex
    PUBLIC ${S})

set(S lang/usenglish)
add_library(flite_usenglish
    ${S}/us_aswd.cpp
    ${S}/us_dur_stats.cpp
    ${S}/us_durz_cart.hpp ${S}/us_durz_cart.cpp
    ${S}/usenglish.hpp ${S}/usenglish.cpp
    ${S}/us_expand.cpp
    ${S}/us_f0.hpp
    ${S}/us_f0lr.cpp
    ${S}/us_f0_model.cpp
    ${S}/us_ffeatures.hpp ${S}/us_ffeatures.cpp
    ${S}/us_gpos.cpp
    ${S}/us_int_accent_cart.hpp ${S}/us_int_accent_cart.cpp
    ${S}/us_int_tone_cart.hpp ${S}/us_int_tone_cart.cpp
    ${S}/us_nums_cart.hpp ${S}/us_nums_cart.cpp
    ${S}/us_phoneset.cpp
    ${S}/us_phrasing_cart.hpp ${S}/us_phrasing_cart.cpp
    ${S}/us_pos_cart.hpp ${S}/us_pos_cart.cpp
    ${S}/us_text.hpp ${S}/us_text.cpp)

target_include_directories(flite_usenglish
    PUBLIC ${S})

target_link_libraries(flite_usenglish
    PUBLIC flite)

set(S lang/time_awb)
add_library(flite_time_awb
    ${S}/time_awb.cpp
    ${S}/time_awb_cart.cpp
    ${S}/time_awb_clunits.cpp
    ${S}/time_awb_lex_entry.cpp
    ${S}/time_awb_lpc.cpp
    ${S}/time_awb_mcep.cpp)

target_link_libraries(flite_time_awb
    PUBLIC flite
    PUBLIC flite_lex
    PUBLIC flite_usenglish)

set(S lang/us_awb)
add_library(flite_us_awb
    ${S}/us_awb_cg.cpp
    ${S}/us_awb_cg_durmodel.hpp ${S}/us_awb_cg_durmodel.cpp
    ${S}/us_awb_cg_f0_trees.hpp ${S}/us_awb_cg_f0_trees.cpp
    ${S}/us_awb_cg_phonestate.cpp
    ${S}/us_awb_cg_single_mcep_trees.hpp ${S}/us_awb_cg_single_mcep_trees.cpp
    ${S}/us_awb_cg_single_params.cpp
    ${S}/us_awb.cpp
    ${S}/us_awb_spamf0_accent.hpp ${S}/us_awb_spamf0_accent.cpp
    ${S}/us_awb_spamf0_accent_params.cpp
    ${S}/us_awb_spamf0_phrase.hpp ${S}/us_awb_spamf0_phrase.cpp)

target_include_directories(flite_us_awb
    PUBLIC ${S})

target_link_libraries(flite_us_awb
    PUBLIC flite
    PUBLIC flite_lex
    PUBLIC flite_usenglish)

set(S lang/us_kal)
add_library(flite_us_kal
    ${S}/us_kal.cpp
    ${S}/us_kal_diphone.cpp
    ${S}/us_kal_lpc.cpp
    ${S}/us_kal_res.cpp
    ${S}/us_kal_residx.cpp
    ${S}/us_kal_ressize.cpp)

target_link_Libraries(flite_us_kal
    PUBLIC flite
    PUBLIC flite_lex
    PUBLIC flite_usenglish)

set(S lang/us_kal16)
add_library(flite_us_kal16
    ${S}/us_kal16.cpp
    ${S}/us_kal16_diphone.cpp
    ${S}/us_kal16_lpc.cpp
    ${S}/us_kal16_res.cpp
    ${S}/us_kal16_residx.cpp)

target_link_libraries(flite_us_kal16
    PUBLIC flite
    PUBLIC flite_lex
    PUBLIC flite_usenglish)

set(S lang/us_rms)
add_library(flite_us_rms
    ${S}/us_rms.cpp
    ${S}/us_rms_cg.cpp
    ${S}/us_rms_cg_durmodel.hpp ${S}/us_rms_cg_durmodel.cpp
    ${S}/us_rms_cg_f0_trees.hpp ${S}/us_rms_cg_f0_trees.cpp
    ${S}/us_rms_cg_phonestate.cpp
    ${S}/us_rms_cg_single_mcep_trees.hpp ${S}/us_rms_cg_single_mcep_trees.cpp
    ${S}/us_rms_cg_single_params.cpp
    ${S}/us_rms_spamf0_accent.hpp ${S}/us_rms_spamf0_accent.cpp
    ${S}/us_rms_spamf0_accent_params.cpp
    ${S}/us_rms_spamf0_phrase.hpp ${S}/us_rms_spamf0_phrase.cpp)

target_link_libraries(flite_us_rms
    PUBLIC flite
    PUBLIC flite_lex
    PUBLIC flite_usenglish)

set(S lang/us_slt)
add_library(flite_us_slt
    ${S}/us_slt.cpp
    ${S}/us_slt_cg.cpp
    ${S}/us_slt_cg_durmodel.hpp ${S}/us_slt_cg_durmodel.cpp
    ${S}/us_slt_cg_f0_trees.hpp ${S}/us_slt_cg_f0_trees.cpp
    ${S}/us_slt_cg_phonestate.cpp
    ${S}/us_slt_cg_single_mcep_trees.hpp ${S}/us_slt_cg_single_mcep_trees.cpp
    ${S}/us_slt_cg_single_params.cpp
    ${S}/us_slt_spamf0_accent.hpp ${S}/us_slt_spamf0_accent.cpp
    ${S}/us_slt_spamf0_accent_params.cpp
    ${S}/us_slt_spamf0_phrase.hpp ${S}/us_slt_spamf0_phrase.cpp)

target_link_libraries(flite_us_slt
    PUBLIC flite
    PUBLIC flite_lex
    PUBLIC flite_usenglish)
