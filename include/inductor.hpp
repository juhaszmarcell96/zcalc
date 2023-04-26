#pragma once

#include <include/impedance.hpp>

namespace zcalc {

class Inductor : public Impedance {
public:
    Inductor(double inductance, double frequency);
    ~Inductor() = default;
};

} /* namespace zcalc */