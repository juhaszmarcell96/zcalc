#pragma once

#include <zcalc/impedance.hpp>

#include <numbers>

namespace zcalc {

class Capacitor : public Impedance {
public:
    Capacitor(const std::string& designator, double capacitance, double frequency) : Impedance(designator, Complex{0.0, 0.0}) {
        m_value = std::polar(1.0 / (2.0 * std::numbers::pi * frequency * capacitance), -std::numbers::pi / 2.0);
    }
    ~Capacitor() = default;
};

} /* namespace zcalc */