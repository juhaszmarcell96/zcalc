#pragma once

#include <zcalc/component/two_pole.hpp>

namespace zcalc {
namespace component {

// only half of an ideal transformer

//      
//           Iprim      Isec
//      1      ->       <-      3     
//      o────────┐     ┌────────o
//               │     │           
//      │       o│  M  │o       │  
//      │        └─┐ ┌─┘        │  
//   U1 │        ┌─┘ └─┐        │ U2
//      │        └─┐ ┌─┘        │  
//      │        ┌─┘ └─┐        │  
//      V        │     │        V  
//               │     │     
//      o────────┘     └────────o
//      2                       4
//

class CoupledInductorHalf : public TwoPoleComponent {
protected:
    const CoupledInductorHalf* m_other_half { nullptr };
    const double m_self_inductance { 0.0 };
    const double m_mutual_inductance { 0.0 };
    math::Frequency m_frequency {};
public:
    CoupledInductorHalf () = delete;
    CoupledInductorHalf (Node node_0, Node node_1, std::size_t id, const std::string& designator, double self_inductance, double mutual_inductance)
        : TwoPoleComponent(node_0, node_1, id, designator), m_self_inductance(self_inductance), m_mutual_inductance(mutual_inductance) {}

    const math::Frequency& get_frequency () const override {
        return m_frequency;
    }

    void set_other_half (const CoupledInductorHalf* other_half) {
        m_other_half = other_half;
    }

    void set_frequency (const math::Frequency& frequency) override {
        m_frequency = frequency;
    }

    bool is_source () const override { return false; }

    void eliminate () override {
        throw std::runtime_error("cannot eliminate a coupled inductor");
    }

    void reactivate () override {
        throw std::runtime_error("cannot reactivate a coupled inductor");
    }

    // 1: u1 = L1*di1/dt + M*di2/dt (time domain) ----> U1 = L1 * jwI1 + M * jwI2 ----> L1 * jwI1 + M * jwI2 - U1 = 0
    // 2: u2 = M*di1/dt + L2*di2/dt (time domain) ----> U2 = M * jwI1 + L2 * jwI2 ----> L2 * jwI2 + M * jwI1 - U2 = 0
    math::SymbolicLinearEquation<math::Complex> own () const override {
        if (!m_other_half) {
            throw std::runtime_error("no other half?");
        }
        math::SymbolicLinearEquation<math::Complex> equation { get_designator() };
        equation.add_term(current(), math::Complex { 0.0, m_frequency.as_rad_per_sec() *  m_self_inductance });
        equation.add_term(m_other_half->current(), math::Complex { 0.0, m_frequency.as_rad_per_sec() *  m_mutual_inductance });
        equation.add_term(voltage(), math::Complex { -1.0, 0.0 });
        equation.set_result(math::Complex { 0.0, 0.0 });
        return equation;
    }
};

} /* namespace component */
} /* namespace zcalc */