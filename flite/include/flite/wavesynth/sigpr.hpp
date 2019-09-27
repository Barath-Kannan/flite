#pragma once

#include "flite/wavesynth/sts.hpp"

#include "flite/utils/file.hpp"
#include "flite/utils/val.hpp"

cst_wave* lpc_resynth(cst_lpcres* lpcres);
cst_wave* lpc_resynth_fixedpoint(cst_lpcres* lpcres);
cst_wave* lpc_resynth_spike(cst_lpcres* lpcres);

void add_residual_windowed(int targ_size, unsigned char* targ_residual, int unit_size, const unsigned char* unit_residual);
void add_residual_g721(int targ_size, unsigned char* targ_residual, int packed_unit_size, const unsigned char* unit_residual);
void add_residual_g721vuv(int targ_size, unsigned char* targ_residual, int uunit_size, const unsigned char* unit_residual);
void add_residual_vuv(int targ_size, unsigned char* targ_residual, int packed_unit_size, const unsigned char* unit_residual);
