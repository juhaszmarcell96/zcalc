/*
 * Copyright (C) 2025 Marcell Juhasz
 *
 * This software is licensed under a non-commercial license.
 * Non-commercial use (personal, academic, research) is allowed for free.
 * Commercial use requires a paid license.
 * Hosting as a service is prohibited without explicit permission.
 *
 * See LICENSE for details or contact marcell.juhasz96@gmail.com.
 */

#pragma once

#include <zcalc/component/impedance.hpp>

namespace zcalc {
namespace component {

class Inductor : public Impedance {
private:
    double m_inductance { 0.0 };
public:
    Inductor () = delete;
    Inductor (double inductance, Node node_0, Node node_1, id_t id, const std::string& designator) : Impedance(math::Complex{0.0, 0.0}, node_0, node_1, id, designator) {
        m_short = true; // capacitor is short circuit at DC
        m_inductance = inductance;
    }
    ~Inductor () = default;

    void set_frequency (const math::Frequency& frequency) override {
        if (frequency.is_dc()) { m_short = true; }
        else {
            m_short = false;
            m_value = math::Complex { 0.0, frequency.as_rad_per_sec() * m_inductance };
        }
    }
};

} /* namespace component */
} /* namespace zcalc */