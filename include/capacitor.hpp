#pragma once

#include <include/impedance.hpp>

namespace zcalc {

class Capacitor : public Impedance {
public:
    Capacitor(const std::string& designator, double capacitance, double frequency);
    ~Capacitor() = default;
};

} /* namespace zcalc */