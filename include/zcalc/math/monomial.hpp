#pragma once

#include <string>
#include <iostream>

namespace zcalc {
namespace math {

template<typename T>
class Monomial {
private:
    std::string m_var;
    T m_coeff {};
public:
    Monomial () = delete;
    Monomial (const std::string& var, const T& coeff = {}) : m_var(var), m_coeff(coeff) {}
    ~Monomial () = default;

    const std::string& get_variable () const { return m_var; }
    const T& get_coefficient () const { return m_coeff; }

    void set_coefficient (const T& coeff) { m_coeff = coeff; }

    friend std::ostream& operator<<(std::ostream& os, const Monomial& term) {
        os << term.m_coeff << "*" << term.m_var;
        return os;
    }
};

} /* namespace component */
} /* namespace zcalc */