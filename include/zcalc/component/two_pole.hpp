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

#include <zcalc/component/component.hpp>

namespace zcalc {
namespace component {

//
//     o 0
//     │
//     │   │
//    +-+  │
//    │ │  │ U, I
//    +-+  │
//     │   V
//     │
//     o 1
//

class TwoPoleComponent : public ComponentBase {
protected:
    bool m_short { false };
    bool m_open { false };
public:
    TwoPoleComponent () = delete;
    TwoPoleComponent (Node node_0, Node node_1, id_t id, const std::string& designator) : ComponentBase(id, designator) {
        m_gates.push_back(node_0);
        m_gates.push_back(node_1);
    }
    ~TwoPoleComponent() = default;

    std::size_t get_num_variables () const override { return 2; }

    math::SymbolicLinearEquation<math::Complex> kcl (Node node) const override {
        const std::string current_var = current();
        math::SymbolicLinearEquation<math::Complex> equation {};
        if (m_open) {
            // open circuit -> no current
            equation.add_term(current_var, math::Complex { 0.0, 0.0 });
        }
        else {
            if (m_gates[0] == node) {
                // current flowing out of the node
                equation.add_term(current_var, math::Complex { -1.0, 0.0 });
            }
            else if (m_gates[1] == node) {
                // current flowing into the node
                equation.add_term(current_var, math::Complex { 1.0, 0.0 });
            }
            else {
                // not my node
                equation.add_term(current_var, math::Complex { 0.0, 0.0 });
            }
        }
        return equation;
    }

    math::SymbolicLinearEquation<math::Complex> kvl (Node node) const override {
        const std::string voltage_var = voltage();
        math::SymbolicLinearEquation<math::Complex> equation {};
        if (m_short) {
            // short circuit -> no voltage
            equation.add_term(voltage_var, math::Complex { 0.0, 0.0 });
        }
        else {
            if (m_gates[0] == node) {
                // loop direction aligns with the voltage drop direction
                equation.add_term(voltage_var, math::Complex { 1.0, 0.0 });
            }
            else if (m_gates[1] == node) {
                // loop direction is opposite to the voltage drop direction
                equation.add_term(voltage_var, math::Complex { -1.0, 0.0 });
            }
            else {
                // not my node
                equation.add_term(voltage_var, math::Complex { 0.0, 0.0 });
            }
        }
        return equation;
    }

    void add_to_graph (graph::Graph<component::IComponent*>& graph) override {
        graph.add_edge(m_gates[0], m_gates[1], this);
    }
};

} /* namespace component */
} /* namespace zcalc */
