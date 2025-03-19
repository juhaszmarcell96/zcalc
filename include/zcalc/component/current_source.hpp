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

#include <zcalc/component/source.hpp>

namespace zcalc {
namespace component {

class CurrentSource : public Source {
public:
    CurrentSource () = delete;
    CurrentSource (math::Complex current, Node node_0, Node node_1, std::size_t id, const std::string& designator) : Source(current, node_0, node_1, id, designator) {}
    CurrentSource (math::Complex current, const math::Frequency& frequency, Node node_0, Node node_1, std::size_t id, const std::string& designator) : Source(current, frequency, node_0, node_1, id, designator) {}
    ~CurrentSource () = default;

    // normal operation -> 1*I + 0*U = current
    // eliminated       -> 1*I + 0*U = 0
    math::SymbolicLinearEquation<math::Complex> own () const override {
        math::SymbolicLinearEquation<math::Complex> equation { get_designator() };
        equation.add_term(current(), math::Complex { 1.0, 0.0 });
        equation.add_term(voltage(), math::Complex { 0.0, 0.0 });
        if (m_open) {
            equation.set_result(math::Complex { 0.0, 0.0 });
        }
        else {
            equation.set_result(m_value.to_complex());
        }
        return equation;
    }

    void eliminate () override { m_open = true; }

    void reactivate () override { m_open = false; }
};

} /* namespace component */
} /* namespace zcalc */