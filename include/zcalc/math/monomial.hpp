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