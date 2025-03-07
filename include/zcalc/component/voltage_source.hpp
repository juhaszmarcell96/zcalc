#pragma once

#include <zcalc/component/source.hpp>

namespace zcalc {
namespace component {

class VoltageSource : public Source {
public:
    VoltageSource () = delete;
    VoltageSource (math::Complex voltage, Node node_0, Node node_1, std::size_t id, const std::string& designator) : Source(voltage, node_0, node_1, id, designator) {}
    VoltageSource (math::Complex voltage, const math::Frequency& frequency, Node node_0, Node node_1, std::size_t id, const std::string& designator) : Source(voltage, frequency, node_0, node_1, id, designator) {}
    ~VoltageSource () = default;

    // normal operation -> 0*I + 1*U = voltage
    // eliminated       -> 0*I + 1*U = 0
    math::SymbolicLinearEquation<math::Complex> own () const override {
        const std::string current_var = get_designator() + "_i";
        const std::string voltage_var = get_designator() + "_u";
        math::SymbolicLinearEquation<math::Complex> equation { get_designator() };
        equation.add_term(current_var, math::Complex { 0.0, 0.0 });
        equation.add_term(voltage_var, math::Complex { 1.0, 0.0 });
        if (m_short) {
            equation.set_result(math::Complex { 0.0, 0.0 });
        }
        else {
            equation.set_result(m_value.to_complex());
        }
        return equation;
    }

    void eliminate () override { m_short = true; }

    void reactivate () override { m_short = false; }
};

} /* namespace component */
} /* namespace zcalc */