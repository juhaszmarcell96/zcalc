#pragma once

#include <include/component.hpp>

namespace zcalc {

class Impedance : public Component {
protected:
    Complex m_value;
public:
    Impedance () = default;
    Impedance(Complex value);
    ~Impedance() = default;

    void set_rectangular (double resistance, double reactance);
    void set_polar (double modulus, double argument);

    Complex get_impedance () const;
    double get_modulus () const;
    double get_argument () const;
    double get_resistance () const;
    double get_reactance () const;

    friend std::ostream& operator<<(std::ostream& os, const Impedance& z);

    static Impedance series (const Impedance& z1, const Impedance& z2);
    static Impedance parallel (const Impedance& z1, const Impedance& z2);

    Complex get_i_coeff(const node_ptr_t node) const override;
    Complex get_u_coeff(const node_ptr_t node_0, const node_ptr_t node_1) const override;
};

} /* namespace zcalc */
