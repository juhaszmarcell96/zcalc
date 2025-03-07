#pragma once

#include <zcalc/component/dependent_source.hpp>

namespace zcalc {
namespace component {

class VoltageControlledCurrentSource : public DependentSource {
private:
    const double m_transconductance;
public:
    VoltageControlledCurrentSource () = delete;
    VoltageControlledCurrentSource (Node node_0, Node node_1, std::size_t id,
                                    const std::string& designator, const IComponent* dependency, double transconductance)
    : DependentSource(node_0, node_1, id, designator, dependency), m_transconductance(transconductance) {}

    // I = g*Ux -> 1*I + 0*U + -g*Ux = 0
    math::SymbolicLinearEquation<math::Complex> own () const override {
        math::SymbolicLinearEquation<math::Complex> equation { get_designator() };
        equation.add_term(current(), math::Complex { 1.0, 0.0 });
        equation.add_term(voltage(), math::Complex { 0.0, 0.0 });
        equation.add_term(m_dependency->voltage(), math::Complex { -m_transconductance, 0.0 });
        equation.set_result(math::Complex { 0.0, 0.0 });
        return equation;
    }
};

} /* namespace component */
} /* namespace zcalc */