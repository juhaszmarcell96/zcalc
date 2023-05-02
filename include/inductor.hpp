#pragma once

#include <include/impedance.hpp>

namespace zcalc {

class Inductor : public Impedance {
public:
    Inductor(const std::string& designator, double inductance, double frequency);
    ~Inductor() = default;
};

} /* namespace zcalc */