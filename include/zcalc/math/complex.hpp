/*
 * Copyright (C) 2025 Marcell Juhasz
 *
 * This software is licensed under a non-commercial license.
 * Non-commercial use (personal, academic, research) is allowed for free.
 * Commercial use requires a paid license.
 * Hosting as a service is prohibited without explicit permission.
 *
 * See LICENSE for details or contact marcell.juhasz96@gmail.com.
 */

#pragma once

#include <complex>
#include <numbers>

#include "zcalc/common.hpp"

namespace zcalc {
namespace math {

class Complex {
public:
    enum class print_format {
        basic,
        trig_rad,
        trig_deg,
        euler_rad,
        euler_deg
    };
protected:
    std::complex<double> m_value { 0.0, 0.0 };
    mutable print_format m_format { print_format::basic }; // mutable, does not really matter
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
        return (std::abs(c0.real() - c1.real()) < epsilon) && (std::abs(c0.imag() - c1.imag()) < epsilon);
    }
    friend bool operator!=(const Complex& c0, const Complex& c1) { return !(c0 == c1); }

    void set_print_format (print_format format) const {
        m_format = format;
    }

    friend std::ostream& operator<<(std::ostream& os, const Complex& c) {
        switch (c.m_format) {
            case Complex::print_format::basic : {
                if (c.m_value.imag() == 0.0) {
                    os << "(" << c.real() << "+j" << 0.0 << ")";
                }
                else if (c.m_value.imag() > 0.0) {
                    os << "(" << c.real() << "+j" << c.imag() << ")";
                }
                else {
                    os << "(" << c.real() << "-j" << -1.0 * c.imag() << ")";
                }
                break;
            }
            case Complex::print_format::trig_rad : {
                const auto arg = c.arg();
                os << c.abs() << "*(cos(" << arg << ")+j*sin(" << arg << "))";
                break;
            }
            case Complex::print_format::trig_deg : {
                const auto arg = (c.arg() * 360.0) / (2 * std::numbers::pi);
                os << c.abs() << "*(cos(" << arg << ")+j*sin(" << arg << "°))";
                break;
            }
            case Complex::print_format::euler_rad : {
                os << c.abs() << "<" << c.arg();
                break;
            }
            case Complex::print_format::euler_deg : {
                os << c.abs() << "<" << (c.arg() * 360.0) / (2 * std::numbers::pi) << "°";
                break;
            }
        }
        return os;
    }
};

} /* namespace component */
} /* namespace zcalc */
