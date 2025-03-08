#pragma once

#include <zcalc/component/two_pole.hpp>

namespace zcalc {
namespace component {

// only half of an ideal transformer

//      
//           Iprim    Isec
//      1      ->     <-      3     
//      o────────┐   ┌────────o
//               │   │           
//      │       o│n:1│o       │  
//      │        /   /        │  
//   U1 │        \   \        │ U2
//      │        /   /        │  
//      │        \   \        │  
//      V        │   │        V  
//               │   │     
//      o────────┘   └────────o
//      2                     4
//

class IdealTransformerHalf : public TwoPoleComponent {
protected:
    const IdealTransformerHalf* m_other_half { nullptr };
    const double m_transfer_value { 1.0 };
    const bool m_first { false };
public:
    IdealTransformerHalf () = delete;
    IdealTransformerHalf (Node node_0, Node node_1, std::size_t id, const std::string& designator, double transfer_value, bool first)
        : TwoPoleComponent(node_0, node_1, id, designator), m_transfer_value(transfer_value), m_first(first) {}

    const math::Frequency& get_frequency () const override {
        throw std::runtime_error("why do you want the frequency of an ideal transformer?");
    }

    void set_other_half (const IdealTransformerHalf* other_half) {
        m_other_half = other_half;
    }

    void set_frequency (const math::Frequency& frequency) override {}

    bool is_source () const override { return false; }

    void eliminate () override {
        throw std::runtime_error("cannot eliminate an ideal transformer");
    }

    void reactivate () override {
        throw std::runtime_error("cannot reactivate an ideal transformer");
    }

    // 1: U1 = n*U2  <-> U1 - n*U2 = 0
    // 2: I2 = -n*I1 <-> I1 + I2/n = 0
    math::SymbolicLinearEquation<math::Complex> own () const override {
        if (!m_other_half) {
            throw std::runtime_error("no other half?");
        }
        math::SymbolicLinearEquation<math::Complex> equation { get_designator() };
        if (m_first) {
            equation.add_term(voltage(), math::Complex { 1.0, 0.0 });
            equation.add_term(m_other_half->voltage(), math::Complex { -m_transfer_value, 0.0 });
        }
        else {
            equation.add_term(m_other_half->current(), math::Complex { 1.0, 0.0 });
            equation.add_term(current(), math::Complex { 1.0 / m_transfer_value, 0.0 });
        }
        equation.set_result(math::Complex { 0.0, 0.0 });
        return equation;
    }
};

} /* namespace component */
} /* namespace zcalc */