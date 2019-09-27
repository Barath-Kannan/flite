################################################
# Project Settings
################################################
project(flite_app C CXX)
set(CMAKE_CXX_STANDARD 17)

################################################
# Dependencies
################################################
#find_package(Boost COMPONENTS program_options REQUIRED)

################################################
# Targets 
################################################
set(S flite_main)
add_executable(flite_main
    ${S}/flite_main.cpp
    ${S}/flite_lang_list.cpp
    ${S}/flite_voice_list.cpp)

target_link_libraries(flite_main
    PUBLIC flite
    PUBLIC flite_grapheme_lang
    PUBLIC flite_grapheme_lex
    PUBLIC flite_indic_lang
    PUBLIC flite_indic_lex
    PUBLIC flite_lex
    PUBLIC flite_us_kal
    PUBLIC flite_us_kal16
    PUBLIC flite_us_slt
    PUBLIC flite_us_rms
    PUBLIC flite_us_awb
    PUBLIC flite_usenglish)
