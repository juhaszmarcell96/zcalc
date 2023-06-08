#pragma once

#include <zcalc/component.hpp>
#include <zcalc/complex.hpp>

#include <string>
#include <iostream>

namespace zcalc {

class Source : public Component {
protected:
    Complex m_voltage;
public:
    Source () = default;
    Source(const std::string& designator, Complex voltage) : Component(designator), m_voltage(voltage) {}
    ~Source() = default;

    Complex get_i_coeff(const Node* node) const override {
        /* current direction is assumed to be from node_0 to node_1 */
        if (m_node_0.get() == node) return Complex { -1.0, 0.0 };
        else if (m_node_1.get() == node) return Complex { 1.0, 0.0 };
        else return Complex { 0.0, 0.0 };
    }
    Complex get_u_coeff(const Node* node_0, const Node* node_1) const override {
        if ((m_node_0.get() == node_0) && (m_node_1.get() == node_1)) return m_voltage;
        else if ((m_node_0.get() == node_1) && (m_node_1.get() == node_0)) return m_voltage * Complex { -1.0, 0.0 };
        else return Complex { 0.0, 0.0 };
    }
    Complex get_own_i_coeff() const override { return Complex {0.0, 0.0}; }
    Complex get_own_u_coeff() const override { return Complex { 1.0, 0.0 }; }
    Complex get_own_result() const override { return m_voltage; }
};

} /* namespace zcalc */