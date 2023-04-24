#include <string>
#include <iostream>
#include <numbers>

#include <include/complex.hpp>

namespace zcalc {

Complex::Complex(double real, double imag) : m_value(real, imag) {}

Complex::Complex(int real, int imag) : m_value(real, imag) {}

Complex::Complex(std::complex<double> value) : m_value(value) {}

double Complex::real () const { return m_value.real(); }
double Complex::imag () const { return m_value.imag(); }

Complex& Complex::operator+=(const Complex& other) { m_value += other.m_value; return *this; }
Complex& Complex::operator-=(const Complex& other) { m_value -= other.m_value; return *this; }
Complex& Complex::operator*=(const Complex& other) { m_value *= other.m_value; return *this; }
Complex& Complex::operator/=(const Complex& other) { m_value /= other.m_value; return *this; }

Complex Complex::operator+(const Complex& rhs) const { return std::move(Complex{m_value + rhs.m_value}); }
Complex Complex::operator-(const Complex& rhs) const { return std::move(Complex{m_value - rhs.m_value}); }
Complex Complex::operator*(const Complex& rhs) const { return std::move(Complex{m_value * rhs.m_value}); }
Complex Complex::operator/(const Complex& rhs) const { return std::move(Complex{m_value / rhs.m_value}); }

bool operator==(const Complex& c0, const Complex& c1) {
    if (c0.m_value.real() < (c1.m_value.real() - epsilon)) return false;
    if (c0.m_value.real() > (c1.m_value.real() + epsilon)) return false;
    if (c0.m_value.imag() < (c1.m_value.imag() - epsilon)) return false;
    if (c0.m_value.imag() > (c1.m_value.imag() + epsilon)) return false;
    return true;
}
bool operator!=(const Complex& c0, const Complex& c1) { return !(c0 == c1); }

std::ostream& operator<<(std::ostream& os, const Complex& c) {
    if (c.m_value.imag() >= 0.0) {
        os << "(" << c.real() << "+j" << c.imag() << ")";
    }
    else {
        os << "(" << c.real() << "-j" << -1.0 * c.imag() << ")";
    }
    return os;
}

} /* namespace zcalc */
