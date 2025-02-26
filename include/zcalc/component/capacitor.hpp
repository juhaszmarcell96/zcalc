#pragma once

#include <zcalc/component/impedance.hpp>

namespace zcalc {
namespace component {

class Capacitor : public Impedance {
private:
    double m_capacitance { 0.0 };
public:
    Capacitor () = delete;
    Capacitor (double capacitance, Node node_0, Node node_1, id_t id) : Impedance(math::Complex{0.0, 0.0}, node_0, node_1, id) {
        m_open = true; // capacitor is open circuit at DC
        m_capacitance = capacitance;
    }
    ~Capacitor () = default;

    void set_frequency (double frequency) override {
        if (frequency == 0.0) { m_open = true; }
        else {
            m_open = false;
            m_value = std::polar(1.0 / (2.0 * pi * frequency * m_capacitance), -pi / 2.0);
        }
    }
};

} /* namespace component */
} /* namespace zcalc */