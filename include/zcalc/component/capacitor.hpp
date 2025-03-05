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

    void set_frequency (const math::Frequency& frequency) override {
        if (frequency.is_dc()) { m_open = true; }
        else {
            m_open = false;
            m_value = std::polar(1.0 / (frequency.as_rad_per_sec() * m_capacitance), -std::numbers::pi / 2.0);
        }
    }
};

} /* namespace component */
} /* namespace zcalc */