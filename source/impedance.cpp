#include <include/common.hpp>
#include <include/impedance.hpp>

#include <cmath>
#include <numbers>

namespace zcalc {

Impedance::Impedance(Complex value) : m_value(value) {}

void Impedance::set_rectangular (double resistance, double reactance) {
    m_value = Complex {resistance, reactance};
}

void Impedance::set_polar (double modulus, double argument) {
    m_value = Complex {std::polar(modulus, argument)};
}

Complex Impedance::get_impedance () const { return m_value; }
double Impedance::get_modulus () const { return std::abs(m_value.get()); }
double Impedance::get_argument () const { return std::arg(m_value.get()); }
double Impedance::get_resistance () const { return std::real(m_value.get()); }
double Impedance::get_reactance () const { return std::imag(m_value.get()); }

Impedance Impedance::series (const Impedance& z1, const Impedance& z2) {
    return z1.m_value + z2.m_value;
}

Impedance Impedance::parallel (const Impedance& z1, const Impedance& z2) {
    /* Z1 || Z2 = (Z1*Z2) / (Z1+Z2) */
    return (z1.m_value * z2.m_value) / (z1.m_value + z2.m_value);
}

std::ostream& operator<<(std::ostream& os, const Impedance& z) {
    os << "[(" << z.get_resistance() << ") + j(" << z.get_reactance() << ")] ohm     / " << z.get_modulus() << "<" << z.get_argument() * 180.0 / std::numbers::pi << "° /";
    return os;
}

Complex Impedance::get_i_coeff(const node_ptr_t node) const {
    /* current direction is assumed to be from node_0 to node_1 */
    if (m_node_0 == node) return Complex { -1.0, 0.0 };
    else if (m_node_1 == node) return Complex { 1.0, 0.0 };
    else return Complex { 0.0, 0.0 };
}

Complex Impedance::get_u_coeff(const node_ptr_t node_0, const node_ptr_t node_1) const {
    if ((m_node_0 == node_0) && (m_node_1 == node_1)) return m_value;
    else if ((m_node_0 == node_1) && (m_node_1 == node_0)) return m_value * -1;
    else return Complex { 0.0, 0.0 };
}

} /* namespace zcalc */