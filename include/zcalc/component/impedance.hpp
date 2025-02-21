#pragma once

#include <zcalc/common.hpp>
#include <zcalc/component/component.hpp>
#include <zcalc/internal/complex.hpp>

#include <complex>
#include <memory>
#include <exception>

namespace zcalc {
namespace component {

class Impedance : public Component {
protected:
    Complex m_value;
public:
    Impedance () = delete;
    Impedance (Complex value, Node node_0, Node node_1, id_t id) : Component(id), m_value(value) {
        m_gates.push_back(node_0);
        m_gates.push_back(node_1);
    }
    ~Impedance() = default;

    void set_rectangular (double resistance, double reactance) { m_value = Complex {resistance, reactance}; }
    void set_polar (double modulus, double argument) { m_value = Complex {std::polar(modulus, argument)}; }

    Complex get_impedance () const { return m_value; }
    double get_modulus () const { return std::abs(m_value.get()); }
    double get_argument () const { return std::arg(m_value.get()); }
    double get_resistance () const { return std::real(m_value.get()); }
    double get_reactance () const { return std::imag(m_value.get()); }

    friend std::ostream& operator<<(std::ostream& os, const Impedance& z) {
        os << "[(" << z.get_resistance() << ") + j(" << z.get_reactance() << ")] ohm     / " << z.get_modulus() << "<" << z.get_argument() * 180.0 / pi << "° /";
        return os;
    }

    std::size_t get_num_variables () const override {
        return 2;
    }

    Complex kcl (Node node) const override {
        if (m_gates[0] == node) { return Complex { -1.0, 0.0 }; }
        else if (m_gates[1] == node) { return Complex { 1.0, 0.0 }; }
        else { return Complex { 0.0, 0.0 }; }
    }

    Complex kvl (Node node) const override {
        if (m_gates[0] == node) { return Complex { 1.0, 0.0 }; }
        else if (m_gates[1] == node) { return Complex { -1.0, 0.0 }; }
        else { return Complex { 0.0, 0.0 }; }
    }

    // U = Z * I -> U - ZI = 0
    Complex own_i () const override {
        return m_value * Complex{-1.0, 0.0};
    }
    Complex own_u () const override {
        return Complex { 1.0, 0.0 };
    }
};

} /* namespace component */
} /* namespace zcalc */
