#pragma once

#include "flite/lexicon/lexicon.hpp"

cst_lexicon* cmu_lex_init(void);
cst_utterance* cmu_postlex(cst_utterance* u);
