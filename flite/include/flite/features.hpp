#pragma once

#include "flite/val.hpp"

#include <vector>

namespace flite {

struct feature_value {
    std::string _name;
    val_type _val;
};

using features = std::vector<feature_value>;

} // namespace flite
