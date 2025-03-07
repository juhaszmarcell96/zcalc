#pragma once

#include <zcalc/component/two_pole.hpp>
#include <zcalc/math/phasor.hpp>

namespace zcalc {
namespace component {

class Voltmeter : public TwoPoleComponent {
public:
    Voltmeter () = delete;
    Voltmeter (Node node_0, Node node_1, std::size_t id, const std::string& designator) : TwoPoleComponent(node_0, node_1, id, designator) {
        m_open = true; // open circuit
    }

    const math::Frequency& get_frequency () const override {
        throw std::runtime_error("why do you want the frequency of a voltmeter?");
    }

    void set_frequency (const math::Frequency& frequency) override {}

    // ideal voltmeter -> no current -> 1*I + 0*U = 0
    math::SymbolicLinearEquation<math::Complex> own () const override {
        const std::string current_var = get_designator() + "_i";
        const std::string voltage_var = get_designator() + "_u";
        math::SymbolicLinearEquation<math::Complex> equation { get_designator() };
        equation.add_term(current_var, math::Complex { 1.0, 0.0 });
        equation.add_term(voltage_var, math::Complex { 0.0, 0.0 });
        equation.set_result(math::Complex { 0.0, 0.0 });
        return equation;
    }

    bool is_source () const override { return false; }

    void eliminate () override {
        throw std::runtime_error("cannot eliminate an voltmeter");
    }

    void reactivate () override {
        throw std::runtime_error("cannot reactivate an voltmeter");
    }
};

} /* namespace component */
} /* namespace zcalc */