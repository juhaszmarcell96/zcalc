#pragma once

#include <include/impedance.hpp>

namespace zcalc {

class Resistor : public Impedance {
public:
    Resistor(double resistance);
    ~Resistor() = default;
};

} /* namespace zcalc */