#pragma once

#include <include/impedance.hpp>

namespace zcalc {

class Capacitor : public Impedance {
public:
    Capacitor(double capacitance, double frequency);
};

} /* namespace zcalc */