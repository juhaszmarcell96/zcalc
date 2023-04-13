#pragma once

#include <string>
#include <iostream>

namespace zcalc {

class Impedance {
protected:
    double m_modulus;
    double m_argument;

    std::string m_endpoint_0;
    std::string m_endpoint_1;
public:
    Impedance () = default;
    /* copy constructor */
    Impedance(const Impedance& z);
    /* move constructor */
    Impedance(Impedance&& z);
    /* copy assignment operator */
    Impedance &operator=(const Impedance& z);
    /* move assignment operator */
    Impedance &operator=(Impedance&& z);
    ~Impedance() = default;

    
    void set_rectangular (double resistance, double reactance);
    void set_polar (double modulus, double argument);

    double get_modulus () const;
    double get_argument () const;
    double get_resistance () const;
    double get_reactance () const;
    
    const std::string& get_endpoint_0 () const;
    const std::string& get_endpoint_1 () const;

    void connect (const std::string& endpoint_0, const std::string& endpoint_1);
    void disconnect ();
    bool is_connected ();

    friend std::ostream& operator<<(std::ostream& os, const Impedance& z);

    static Impedance series (const Impedance& z1, const Impedance& z2);

    static Impedance parallel (const Impedance& z1, const Impedance& z2);
};

} /* namespace zcalc */