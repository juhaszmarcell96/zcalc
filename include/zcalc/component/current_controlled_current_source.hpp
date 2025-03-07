#pragma once

#include <zcalc/component/dependent_source.hpp>

namespace zcalc {
namespace component {

class CurrentControlledCurrentSource : public DependentSource {
private:
    const double m_current_gain;
public:
    CurrentControlledCurrentSource () = delete;
    CurrentControlledCurrentSource (Node node_0, Node node_1, std::size_t id,
                                    const std::string& designator, const std::string& dependency, double current_gain)
    : DependentSource(node_0, node_1, id, designator, dependency), m_current_gain(current_gain) {}

    // I = a*Ix -> 1*I + 0*U + -a*Ix = 0
    math::SymbolicLinearEquation<math::Complex> own () const override {
        const std::string current_var = get_designator() + "_i";
        const std::string voltage_var = get_designator() + "_u";
        const std::string other_current_var = m_dependency + "_i";
        math::SymbolicLinearEquation<math::Complex> equation { get_designator() };
        equation.add_term(current_var, math::Complex { 1.0, 0.0 });
        equation.add_term(voltage_var, math::Complex { 0.0, 0.0 });
        equation.add_term(other_current_var, math::Complex { -m_current_gain, 0.0 });
        equation.set_result(math::Complex { 0.0, 0.0 });
        return equation;
    }
};

} /* namespace component */
} /* namespace zcalc */