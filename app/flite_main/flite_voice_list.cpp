/* Generated automatically from make_voice_list */

#include "flite/flite.hpp"
#include "flite/lang/us_awb.hpp"
#include "flite/lang/us_kal.hpp"
#include "flite/lang/us_kal16.hpp"
#include "flite/lang/us_rms.hpp"
#include "flite/lang/us_slt.hpp"

#include <string_view>
#include <vector>

cst_voice* register_cmu_us_slt(const char* voxdir);
cst_voice* register_cmu_us_rms(const char* voxdir);
cst_voice* register_cmu_us_kal16(const char* voxdir);
cst_voice* register_cmu_us_kal(const char* voxdir);
cst_voice* register_cmu_us_awb(const char* voxdir);

std::vector<flite::voice> flite_set_voice_list(std::string_view voxdir)
{
    std::vector<flite::voice> voices;
    voices.reserve(5);
    voices.emplace_back(flite::make_us_slt(voxdir));
    voices.emplace_back(flite::make_us_awb(voxdir));
    voices.emplace_back(flite::make_us_kal(voxdir));
    voices.emplace_back(flite::make_us_rms(voxdir));
    voices.emplace_back(flite::make_us_kal16(voxdir));
    return voices;
}
