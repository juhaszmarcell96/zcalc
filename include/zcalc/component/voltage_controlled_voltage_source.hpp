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

#include <zcalc/component/dependent_source.hpp>

namespace zcalc {
namespace component {

class VoltageControlledVoltageSource : public DependentSource {
private:
    const double m_voltage_gain;
public:
    VoltageControlledVoltageSource () = delete;
    VoltageControlledVoltageSource (Node node_0, Node node_1, std::size_t id,
                                    const std::string& designator, const IComponent* dependency, double voltage_gain)
    : DependentSource(node_0, node_1, id, designator, dependency), m_voltage_gain(voltage_gain) {}

    // U = n*Ux -> 0*I + 1*U + -n*Ux = 0
    math::SymbolicLinearEquation<math::Complex> own () const override {
        math::SymbolicLinearEquation<math::Complex> equation { get_designator() };
        equation.add_term(current(), math::Complex { 0.0, 0.0 });
        equation.add_term(voltage(), math::Complex { 1.0, 0.0 });
        equation.add_term(m_dependency->voltage(), math::Complex { -m_voltage_gain, 0.0 });
        equation.set_result(math::Complex { 0.0, 0.0 });
        return equation;
    }
};

} /* namespace component */
} /* namespace zcalc */