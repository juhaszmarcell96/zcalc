#pragma once

#include <zcalc/impedance.hpp>

#include <numbers>

namespace zcalc {

class Inductor : public Impedance {
public:
    Inductor(const std::string& designator, double inductance, double frequency) : Impedance(designator, Complex{0.0, 0.0}) {
        m_value = std::polar(2.0 * std::numbers::pi * frequency * inductance, std::numbers::pi / 2.0);
    }
    ~Inductor() = default;
};

} /* namespace zcalc */