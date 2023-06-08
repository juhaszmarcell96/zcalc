#pragma once

#include <zcalc/component.hpp>

#include <numbers>

namespace zcalc {

class Impedance : public Component {
protected:
    Complex m_value;
public:
    Impedance () = default;
    Impedance (const std::string& designator, Complex value) : Component(designator), m_value(value) {}
    Impedance(Complex value) : m_value(value) {}
    ~Impedance() = default;

    void set_rectangular (double resistance, double reactance) { m_value = Complex {resistance, reactance}; }
    void set_polar (double modulus, double argument) { m_value = Complex {std::polar(modulus, argument)}; }

    Complex get_impedance () const { return m_value; }
    double get_modulus () const { return std::abs(m_value.get()); }
    double get_argument () const { return std::arg(m_value.get()); }
    double get_resistance () const { return std::real(m_value.get()); }
    double get_reactance () const { return std::imag(m_value.get()); }

    friend std::ostream& operator<<(std::ostream& os, const Impedance& z) {
        os << "[(" << z.get_resistance() << ") + j(" << z.get_reactance() << ")] ohm     / " << z.get_modulus() << "<" << z.get_argument() * 180.0 / std::numbers::pi << "° /";
        return os;
    }

    static Impedance series (const Impedance& z1, const Impedance& z2) { return z1.m_value + z2.m_value; }
    static Impedance parallel (const Impedance& z1, const Impedance& z2) {
        /* Z1 || Z2 = (Z1*Z2) / (Z1+Z2) */
        return (z1.m_value * z2.m_value) / (z1.m_value + z2.m_value);
    }

    Complex get_i_coeff(const Node* node) const override {
        /* current direction is assumed to be from node_0 to node_1 */
        if (m_node_0.get() == node) return Complex { -1.0, 0.0 };
        else if (m_node_1.get() == node) return Complex { 1.0, 0.0 };
        else return Complex { 0.0, 0.0 };
    }

    Complex get_u_coeff(const Node* node_0, const Node* node_1) const override {
        if ((m_node_0.get() == node_0) && (m_node_1.get() == node_1)) return m_value;
        else if ((m_node_0.get() == node_1) && (m_node_1.get() == node_0)) return m_value * Complex{-1.0, 0.0};
        else return Complex { 0.0, 0.0 };
    }

    Complex get_own_i_coeff() const override {
        return m_value * Complex{-1.0, 0.0};
    }
    
    Complex get_own_u_coeff() const override {
        return Complex { 1.0, 0.0 };
    }

    Complex get_own_result() const override {
        return Complex { 0.0, 0.0 };
    }
};

} /* namespace zcalc */
