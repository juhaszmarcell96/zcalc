#pragma once

#include <zcalc/impedance.hpp>

namespace zcalc {

class Resistor : public Impedance {
public:
    Resistor(const std::string& designator, double resistance) : Impedance(designator, Complex{0.0, 0.0}) {
        m_value = std::complex<double> {resistance, 0};
    }
    ~Resistor() = default;
};

} /* namespace zcalc */