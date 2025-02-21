#pragma once

#include <zcalc/component/impedance.hpp>

namespace zcalc {
namespace component {

class Capacitor : public Impedance {
private:
    double m_capacitance { 0.0 };
public:
    Capacitor () = delete;
    Capacitor (double capacitance, frequency_t frequency, Node node_0, Node node_1, id_t id) : Impedance(math::Complex{0.0, 0.0}, node_0, node_1, id) {
        m_value = std::polar(1.0 / (2.0 * pi * frequency * capacitance), -pi / 2.0);
        m_capacitance = capacitance;
    }
    ~Capacitor () = default;

    // TODO : what if frequency is 0 (DC)?
    void set_frequency (double frequency) override {
        m_value = std::polar(1.0 / (2.0 * pi * frequency * m_capacitance), -pi / 2.0);
    }
};

} /* namespace component */
} /* namespace zcalc */