#pragma once

#include "flite/error.hpp"
#include "flite/val_defs.hpp"

#include <any>
#include <string>
#include <variant>

namespace flite {

using val_type = std::variant<int, float, std::string>;
using userdata_type = std::any;

} // namespace flite
