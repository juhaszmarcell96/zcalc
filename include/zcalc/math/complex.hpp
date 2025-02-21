#pragma once

#include <complex>

#include "zcalc/common.hpp"

namespace zcalc {
namespace math {

class Complex {
protected:
    std::complex<double> m_value;
public:
    Complex () = default;
    Complex(double real, double imag) : m_value(real, imag) {}
    Complex(double real) : m_value(real, 0.0) {}
    Complex(int real, int imag) : m_value(real, imag) {}
    Complex(std::complex<double> value) : m_value(value) {}
    ~Complex() = default;

    std::complex<double> get () const { return m_value; }

    double real () const { return m_value.real(); }
    double imag () const { return m_value.imag(); }
    double abs () const { return std::abs(m_value); }
    double arg () const { return std::arg(m_value); }

    Complex operator-() { return std::move(Complex{-m_value}); }
    Complex operator+() { return std::move(Complex{+m_value}); }

    Complex& operator+=(const Complex& other) { m_value += other.m_value; return *this; }
    Complex& operator-=(const Complex& other) { m_value -= other.m_value; return *this; }
    Complex& operator*=(const Complex& other) { m_value *= other.m_value; return *this; }
    Complex& operator/=(const Complex& other) { m_value /= other.m_value; return *this; }

    Complex operator+(const Complex& rhs) const { return std::move(Complex{m_value + rhs.m_value}); }
    Complex operator-(const Complex& rhs) const { return std::move(Complex{m_value - rhs.m_value}); }
    Complex operator*(const Complex& rhs) const { return std::move(Complex{m_value * rhs.m_value}); }
    Complex operator/(const Complex& rhs) const { return std::move(Complex{m_value / rhs.m_value}); }

    friend bool operator==(const Complex& c0, const Complex& c1) {
        //return c0.m_value == c1.m_value;
        if (c0.abs() < (c1.abs() - epsilon)) return false;
        if (c0.abs() > (c1.abs() + epsilon)) return false;
        return true;
    }
    friend bool operator!=(const Complex& c0, const Complex& c1) { return !(c0 == c1); }

    friend std::ostream& operator<<(std::ostream& os, const Complex& c) {
        if (c.m_value.imag() == 0.0) {
            os << "(" << c.real() << "+j" << 0.0 << ")";
        }
        else if (c.m_value.imag() > 0.0) {
            os << "(" << c.real() << "+j" << c.imag() << ")";
        }
        else {
            os << "(" << c.real() << "-j" << -1.0 * c.imag() << ")";
        }
        return os;
    }
};

} /* namespace component */
} /* namespace zcalc */
