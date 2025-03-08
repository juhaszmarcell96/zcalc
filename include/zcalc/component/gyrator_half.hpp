#pragma once

#include <zcalc/component/two_pole.hpp>

namespace zcalc {
namespace component {

// only half of a gyrator

//      
//             I1        I2
//      1      ->        <-      3     
//      o────────┐      ┌────────o
//               │  r   │           
//      │        │----->│        │  
//      │        │\    /│        │  
//   U1 │        │ │  │ │        │ U2
//      │        │ │  │ │        │  
//      │        │/    \│        │  
//      V        │      │        V  
//               │      │     
//      o────────┘      └────────o
//      2                        4
//

class GyratorHalf : public TwoPoleComponent {
protected:
    const GyratorHalf* m_other_half { nullptr };
    const double m_gyration_resistance { 1.0 };
    const bool m_first { false };
public:
    GyratorHalf () = delete;
    GyratorHalf (Node node_0, Node node_1, std::size_t id, const std::string& designator, double gyration_resistance, bool first)
        : TwoPoleComponent(node_0, node_1, id, designator), m_gyration_resistance(gyration_resistance), m_first(first) {}

    const math::Frequency& get_frequency () const override {
        throw std::runtime_error("why do you want the frequency of a gyrator?");
    }

    void set_other_half (const GyratorHalf* other_half) {
        m_other_half = other_half;
    }

    void set_frequency (const math::Frequency& frequency) override {}

    bool is_source () const override { return false; }

    void eliminate () override {
        throw std::runtime_error("cannot eliminate a gyrator");
    }

    void reactivate () override {
        throw std::runtime_error("cannot reactivate a gyrator");
    }

    // 1: U1 = -r*I2 <-> U1 + r*I2 = 0
    // 2: U2 =  r*I1 <-> U2 - r*I1 = 0
    math::SymbolicLinearEquation<math::Complex> own () const override {
        if (!m_other_half) {
            throw std::runtime_error("no other half?");
        }
        math::SymbolicLinearEquation<math::Complex> equation { get_designator() };
        if (m_first) {
            equation.add_term(voltage(), math::Complex { 1.0, 0.0 });
            equation.add_term(m_other_half->current(), math::Complex { m_gyration_resistance, 0.0 });
        }
        else {
            equation.add_term(voltage(), math::Complex { 1.0, 0.0 });
            equation.add_term(m_other_half->current(), math::Complex { -m_gyration_resistance, 0.0 });
        }
        equation.set_result(math::Complex { 0.0, 0.0 });
        return equation;
    }
};

} /* namespace component */
} /* namespace zcalc */