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

#include <cstdint>
#include <cstddef>
#include <iostream>
#include <vector>
#include <string>

#include <zcalc/math/monomial.hpp>

namespace zcalc {
namespace math {

template <typename T>
class SymbolicLinearEquation {
private:
    std::vector<Monomial<T>> m_terms;
    T m_result;
    std::string m_label;
public:
    SymbolicLinearEquation () = default;
    SymbolicLinearEquation (const std::string& label) : m_label(label) { }
    ~SymbolicLinearEquation () = default;

    void set_label (const std::string& label) {
        m_label = label;
    }
    const std::string& get_label () const {
        return m_label;
    }

    void add_term (const std::string& variable, const T& coefficient) {
        for (auto& term : m_terms) {
            if (term.get_variable() == variable) {
                term.set_coefficient(term.get_coefficient() + coefficient);
                return;
            }
        }
        m_terms.push_back(Monomial<T>{variable, coefficient});
    }
    void set_result (const T& value) {
        m_result = value;
    }

    void add_result (const T& value) {
        m_result += value;
    }

    const std::vector<Monomial<T>>& get_terms () const { return m_terms; }

    // if the variable is not found, coefficient is 0
    T get_coefficient (const std::string& variable) const {
        for (const auto& term : m_terms) {
            if (term.get_variable() == variable) {
                return term.get_coefficient();
            }
        }
        return T{};
    }

    T get_result () const {
        return m_result;
    }

    void merge (const SymbolicLinearEquation<T>& equ) {
        for (const auto& term : equ.m_terms) {
            add_term(term.get_variable(), term.get_coefficient());
        }
        add_result(equ.get_result());
    }

    friend std::ostream& operator<<(std::ostream& os, const SymbolicLinearEquation<T>& equation) {
        os << equation.m_label << " : ";
        bool first = true;
        for (const auto& term : equation.m_terms) {
            if (first) { first = false; }
            else { os << "+"; }
            os << "[" << term << "]";
        }
        os << " = " << equation.m_result;
        return os;
    }
};

} /* namespace component */
} /* namespace zcalc */