#pragma once

#include <stdexcept>
#include <string>

namespace flite {

class flite_error
    : public std::runtime_error {
public:
    flite_error(std::string);
};

} // namespace flite
