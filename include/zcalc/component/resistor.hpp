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

class Resistor : public Impedance {
public:
    Resistor () = delete;
    Resistor (double resistance, Node node_0, Node node_1, id_t id, const std::string& designator) : Impedance(math::Complex{0.0, 0.0}, node_0, node_1, id, designator) {
        m_value = std::complex<double> {resistance, 0};
    }
    ~Resistor () = default;

    void set_frequency (const math::Frequency& frequency) override { /* nothing to do */ }
};

} /* namespace component */
} /* namespace zcalc */