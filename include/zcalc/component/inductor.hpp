#pragma once

#include <zcalc/component/impedance.hpp>

namespace zcalc {
namespace component {

class Inductor : public Impedance {
private:
    double m_inductance { 0.0 };
public:
    Inductor () = delete;
    Inductor (double inductance, Node node_0, Node node_1, id_t id) : Impedance(math::Complex{0.0, 0.0}, node_0, node_1, id) {
        m_short = true; // capacitor is short circuit at DC
        m_inductance = inductance;
    }
    ~Inductor () = default;

    void set_frequency (const math::Frequency& frequency) override {
        if (frequency.is_dc()) { m_short = true; }
        else {
            m_short = false;
            m_value = std::polar(frequency.as_rad_per_sec() * m_inductance, std::numbers::pi / 2.0);
        }
    }
};

} /* namespace component */
} /* namespace zcalc */