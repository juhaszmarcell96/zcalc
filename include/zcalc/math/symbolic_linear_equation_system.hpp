#pragma once

#include <cstdint>
#include <iostream>
#include <map>
#include <optional>

#include <zcalc/math/symbolic_linear_equation.hpp>
#include <zcalc/math/linear_equation_system.hpp>

namespace zcalc {
namespace math {

template <typename T>
class SymbolicLinearEquationSystem {
private:
    std::vector<SymbolicLinearEquation<T>> m_equations;
public:
    SymbolicLinearEquationSystem () = default;
    ~SymbolicLinearEquationSystem () = default;

    void add (const SymbolicLinearEquation<T>& equ) {
        m_equations.push_back(equ);
    }

    void add (SymbolicLinearEquation<T>&& equ) {
        m_equations.push_back(std::move(equ));
    }

    std::optional<std::map<std::string, T>> solve () const {
        std::map<std::string, T> variables;
        // get the number of variables by assempling the result
        for (const auto& equ : m_equations) {
            for (const auto& term : equ.get_terms()) {
                variables[term.get_variable()] = T{};
            }
        }
        const auto num_variables = variables.size();
        // create the linear equation system
        LinearEquationSystem lin_equ_system { num_variables };
        // populate the linear equation system
        for (const auto& equ : m_equations) {
            LinearEquation<T> lin_equ { num_variables, equ.get_label() };
            std::size_t variable_index { 0 };
            for (const auto& [var, val] : variables) {
                lin_equ[variable_index] = equ.get_coefficient(var);
                lin_equ_system.set_label(var, variable_index);
                ++variable_index;
            }
            lin_equ.set_result(equ.get_result());
            lin_equ_system.append_equation(std::move(lin_equ));
        }
        // solve the equation system
        const auto solutions = lin_equ_system.solve();
        if (!solutions.has_value()) { return std::nullopt; }
        if (solutions.value().size() != variables.size()) { return std::nullopt; }
        std::size_t variable_index { 0 };
        for (auto& [var, val] : variables) {
            val = solutions.value()[variable_index];
            ++variable_index;
        }
        return variables;
    }

    friend std::ostream& operator<<(std::ostream& os, const SymbolicLinearEquationSystem<T>& equation_system) {
        for (const auto& equation : equation_system.m_equations) {
            os << equation << std::endl;
        }
        return os;
    }
};

} /* namespace component */
} /* namespace zcalc */