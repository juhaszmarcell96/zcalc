#include <include/common.hpp>
#include <include/impedance.hpp>

#include <cmath>

namespace zcalc {

Impedance::Impedance(const Impedance& z) {
    m_modulus = z.m_modulus;
    m_argument = z.m_argument;
    m_endpoint_0 = z.m_endpoint_0;
    m_endpoint_1 = z.m_endpoint_1;
}
/* move constructor */
Impedance::Impedance(Impedance&& z) {
    m_modulus = z.m_modulus;
    m_argument = z.m_argument;
    m_endpoint_0 = z.m_endpoint_0;
    m_endpoint_1 = z.m_endpoint_1;
    z.m_modulus = 0;
    z.m_argument = 0;
    z.m_endpoint_0.clear();
    z.m_endpoint_1.clear();
}
/* copy assignment operator */
Impedance& Impedance::operator=(const Impedance& z) {
    if (this == &z) return *this;
    m_modulus = z.m_modulus;
    m_argument = z.m_argument;
    m_endpoint_0 = z.m_endpoint_0;
    m_endpoint_1 = z.m_endpoint_1;
    return *this;
}
/* move assignment operator */
Impedance& Impedance::operator=(Impedance&& z) {
    if (this == &z) return *this;
    m_modulus = z.m_modulus;
    m_argument = z.m_argument;
    m_endpoint_0 = z.m_endpoint_0;
    m_endpoint_1 = z.m_endpoint_1;
    z.m_modulus = 0;
    z.m_argument = 0;
    z.m_endpoint_0.clear();
    z.m_endpoint_1.clear();
    return *this;
}

void Impedance::set_rectangular (double resistance, double reactance) {
    m_modulus = std::sqrt(resistance * resistance + reactance * reactance);
    if (resistance > 0) {
        m_argument = std::atan(reactance / resistance);
    }
    else {
        m_argument = std::atan(reactance / resistance) + pi;
    }
}

void Impedance::set_polar (double modulus, double argument) {
    m_modulus = modulus;
    m_argument = argument;
}

double Impedance::get_modulus () const { return m_modulus; }
double Impedance::get_argument () const { return m_argument; }
double Impedance::get_resistance () const { return m_modulus * std::cos(m_argument); }
double Impedance::get_reactance () const { return m_modulus * std::sin(m_argument); }

const std::string& Impedance::get_endpoint_0 () const { return m_endpoint_0; }
const std::string& Impedance::get_endpoint_1 () const { return m_endpoint_1; }

void Impedance::connect (const std::string& endpoint_0, const std::string& endpoint_1) {
    m_endpoint_0 = endpoint_0;
    m_endpoint_1 = endpoint_1;
}

void Impedance::disconnect () {
    m_endpoint_0.clear();
    m_endpoint_1.clear();
}

bool Impedance::is_connected () {
    return (!m_endpoint_0.empty()) && (!m_endpoint_1.empty());
}

Impedance Impedance::series (const Impedance& z1, const Impedance& z2) {
    double resistance = z1.get_resistance() + z2.get_resistance();
    double reactance = z1.get_reactance() + z2.get_reactance();
    Impedance z;
    z.set_rectangular(resistance, reactance);
    return z;
}

Impedance Impedance::parallel (const Impedance& z1, const Impedance& z2) {
    /* Z1 || Z2 = (Z1*Z2) / (Z1+Z2) */
    /* multiplication */
    double modulus1 = z1.get_modulus() * z2.get_modulus();
    double argument1 = z1.get_argument() + z2.get_argument();
    /* sum */
    double resistance = z1.get_resistance() + z2.get_resistance();
    double reactance = z1.get_reactance() + z2.get_reactance();
    Impedance z;
    z.set_rectangular(resistance, reactance);
    /* division */
    double modulus2 = z.get_modulus();
    double argument2 = z.get_argument();
    /* result */
    z.set_polar(modulus1 / modulus2, argument1 - argument2);
    return z;
}

std::ostream& operator<<(std::ostream& os, const Impedance& z) {
    os << "[(" << z.get_resistance() << ") + j(" << z.get_reactance() << ")] ohm     / " << z.get_modulus() << "<" << z.get_argument() * 180.0 / pi << "° /";
    return os;
}

} /* namespace zcalc */