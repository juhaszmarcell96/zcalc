#pragma once

#include <include/impedance.hpp>

namespace zcalc {

class Resistor : public Impedance {
public:
    Resistor(const std::string& designator, double resistance);
    ~Resistor() = default;
};

} /* namespace zcalc */