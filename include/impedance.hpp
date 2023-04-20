#pragma once

#include <string>
#include <iostream>
#include <complex>
#include <numbers>

namespace zcalc {

class Impedance {
protected:
    std::complex<double> m_value;
public:
    Impedance () = default;
    Impedance(std::complex<double> value);
    ~Impedance() = default;

    void set_rectangular (double resistance, double reactance);
    void set_polar (double modulus, double argument);

    std::complex<double> get_impedance () const;
    double get_modulus () const;
    double get_argument () const;
    double get_resistance () const;
    double get_reactance () const;

    friend std::ostream& operator<<(std::ostream& os, const Impedance& z);

    static Impedance series (const Impedance& z1, const Impedance& z2);

    static Impedance parallel (const Impedance& z1, const Impedance& z2);
};

} /* namespace zcalc */
