#pragma once

#include "flite/features.hpp"

cst_val* cst_args(
    char** argv,
    int argc,
    const char* description,
    cst_features* args);
