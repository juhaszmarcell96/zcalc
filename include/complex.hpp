#pragma once

#include <complex>

namespace zcalc {

static constexpr double epsilon = 1e-12;

class Complex {
protected:
    std::complex<double> m_value;
public:
    Complex () = default;
    Complex(double real, double imag);
    Complex(int real, int imag = 0);
    Complex(std::complex<double> value);
    ~Complex() = default;

    std::complex<double> get () const;

    double real () const;
    double imag () const;

    Complex operator-();
    Complex operator+();

    Complex& operator+=(const Complex& other);
    Complex& operator-=(const Complex& other);
    Complex& operator*=(const Complex& other);
    Complex& operator/=(const Complex& other);

    Complex operator+(const Complex& rhs) const;
    Complex operator-(const Complex& rhs) const;
    Complex operator*(const Complex& rhs) const;
    Complex operator/(const Complex& rhs) const;

    friend bool operator!=(const Complex& c0, const Complex& c1);
    friend bool operator==(const Complex& c0, const Complex& c1);

    friend std::ostream& operator<<(std::ostream& os, const Complex& c);
};

} /* namespace zcalc */
