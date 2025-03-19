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

#include <zcalc/component/two_pole.hpp>
#include <zcalc/math/phasor.hpp>

namespace zcalc {
namespace component {

class Ammeter : public TwoPoleComponent {
public:
    Ammeter () = delete;
    Ammeter (Node node_0, Node node_1, std::size_t id, const std::string& designator) : TwoPoleComponent(node_0, node_1, id, designator) {
        m_short = true; // short circuit
    }

    const math::Frequency& get_frequency () const override {
        throw std::runtime_error("why do you want the frequency of a ammeter?");
    }

    void set_frequency (const math::Frequency& frequency) override {}

    // ideal ampere meter -> no voltage drom -> 0*I + 1*U = 0
    math::SymbolicLinearEquation<math::Complex> own () const override {
        math::SymbolicLinearEquation<math::Complex> equation { get_designator() };
        equation.add_term(current(), math::Complex { 0.0, 0.0 });
        equation.add_term(voltage(), math::Complex { 1.0, 0.0 });
        equation.set_result(math::Complex { 0.0, 0.0 });
        return equation;
    }

    bool is_source () const override { return false; }

    void eliminate () override {
        throw std::runtime_error("cannot eliminate an ammeter");
    }

    void reactivate () override {
        throw std::runtime_error("cannot reactivate an ammeter");
    }
};

} /* namespace component */
} /* namespace zcalc */