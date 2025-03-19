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

class Capacitor : public Impedance {
private:
    double m_capacitance { 0.0 };
public:
    Capacitor () = delete;
    Capacitor (double capacitance, Node node_0, Node node_1, id_t id, const std::string& designator) : Impedance(math::Complex{0.0, 0.0}, node_0, node_1, id, designator) {
        m_open = true; // capacitor is open circuit at DC
        m_capacitance = capacitance;
    }
    ~Capacitor () = default;

    void set_frequency (const math::Frequency& frequency) override {
        if (frequency.is_dc()) { m_open = true; }
        else {
            m_open = false;
            m_value = math::Complex { 0.0, -1.0 / (frequency.as_rad_per_sec() * m_capacitance) };
        }
    }
};

} /* namespace component */
} /* namespace zcalc */