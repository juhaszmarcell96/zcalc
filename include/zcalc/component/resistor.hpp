#pragma once

#include <zcalc/component/impedance.hpp>

namespace zcalc {
namespace component {

class Resistor : public Impedance {
public:
    Resistor () = delete;
    Resistor (double resistance, Node node_0, Node node_1, id_t id) : Impedance(math::Complex{0.0, 0.0}, node_0, node_1, id) {
        m_value = std::complex<double> {resistance, 0};
    }
    ~Resistor () = default;

    void set_frequency (const math::Frequency& frequency) override { /* nothing to do */ }
};

} /* namespace component */
} /* namespace zcalc */