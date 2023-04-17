#include <include/common.hpp>
#include <include/impedance.hpp>

#include <cmath>
#include <numbers>

namespace zcalc {

Impedance::Impedance(std::complex<double> value) : m_value(value) {}

void Impedance::set_rectangular (double resistance, double reactance) {
    m_value = std::complex<double> {resistance, reactance};
}

void Impedance::set_polar (double modulus, double argument) {
    m_value = std::polar(modulus, argument);
}

std::complex<double> Impedance::get_impedance () const { return m_value; }
double Impedance::get_modulus () const { return std::abs(m_value); }
double Impedance::get_argument () const { return std::arg(m_value); }
double Impedance::get_resistance () const { return std::real(m_value); }
double Impedance::get_reactance () const { return std::imag(m_value); }

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

} /* namespace zcalc */