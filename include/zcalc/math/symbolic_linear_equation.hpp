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