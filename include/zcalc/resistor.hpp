#pragma once

#include <zcalc/impedance.hpp>

namespace zcalc {

class Resistor : public Impedance {
public:
    Resistor () = delete;
    Resistor (const std::string& designator, double resistance, Node* node_0, Node* node_1, std::size_t id) : Impedance(designator, Complex{0.0, 0.0}, node_0, node_1, id) {
        m_value = std::complex<double> {resistance, 0};
    }
    ~Resistor () = default;

    void set_frequency (double frequency) override { /* nothing to do */ }
};

} /* namespace zcalc */