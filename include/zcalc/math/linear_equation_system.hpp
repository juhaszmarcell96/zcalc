#pragma once

#include <cstdint>
#include <cstddef>
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <algorithm>
#include <memory>
#include <numbers>
#include <stdexcept>

#include <zcalc/math/linear_equation.hpp>
#include <zcalc/math/complex.hpp>

namespace zcalc {
namespace math {

/*
a (nxm = 2x3) | b
    a_00 a_01 a_02 | b_0
    a_10 a_11 a_12 | b_1
*/

class LinearEquationSystem {
private:
    std::size_t m_num_variables = 0;
    std::vector<LinearEquation<Complex>> m_linear_equation_system;
    std::vector<std::string> m_labels;

    bool forward_elimination () {
        /* algorithm for reducing the matrix to row echelon form */
        for (std::size_t equation_index = 0; equation_index < get_num_equations(); ++equation_index) {
            /* STEP : determine the leftmost non-zero column */
            std::size_t leftmost_nonzero_equ_index = 0;
            std::size_t leftmost_nonzero_var_index = 0;
            if (!get_leftmost_nonzero_indexes(equation_index, &leftmost_nonzero_equ_index, &leftmost_nonzero_var_index)) {
                /* STEP : no more non-zero rows below the previous pivot position -> move on */
                break;
            }
            exchange_equations(equation_index, leftmost_nonzero_equ_index);
            /* STEP : use elementary row operations to put a 1 in the topmost position of this column */
            Complex divisor = m_linear_equation_system[equation_index].get_coefficient(leftmost_nonzero_var_index);
            m_linear_equation_system[equation_index] /= divisor;
            /* STEP : use elementary row operations to put zeros below the pivot position */
            /*        -> subtract the scalar multiplication of this row from every row below it so that the values of the same column become 0 */
            for (std::size_t i = equation_index + 1; i < get_num_equations(); ++i) {
                Complex multiplier = m_linear_equation_system[i].get_coefficient(leftmost_nonzero_var_index) 
                                        / m_linear_equation_system[equation_index].get_coefficient(leftmost_nonzero_var_index);
                m_linear_equation_system[i] -= m_linear_equation_system[equation_index] * multiplier;
            }
        }
        /* TODO : check the format if it is really the one we wanted */
        return true;
    }
    bool back_substitution () {
        /* last some rows must be all 0 -> some kind of check would be nice TODO */
        /* something is wrong if only the last column is non zero but the variables all have 0 as coefficient */
        /* the matrix, excluding the zero rows, should be a square matrix? */
        /* start from the last row */
        /* skip every full zero row */
        for (int equ_index = (int)get_num_equations() - 1; equ_index >= 0; --equ_index) {
            LinearEquation<Complex>& current_equ = m_linear_equation_system[equ_index];
            if (current_equ.is_zero()) continue;
            std::size_t leading_one_index = current_equ.get_first_nonzero_coeff_index();
            for (int back_sub_equ_index = equ_index - 1; back_sub_equ_index >= 0; --back_sub_equ_index) {
                LinearEquation<Complex>& back_sub_equ = m_linear_equation_system[back_sub_equ_index];
                Complex multiplier = back_sub_equ[leading_one_index] / current_equ[leading_one_index];
                back_sub_equ[leading_one_index] = back_sub_equ[leading_one_index] - (multiplier * current_equ[leading_one_index]);
                back_sub_equ.set_result(back_sub_equ.get_result() - current_equ.get_result() * multiplier);
            }
            --leading_one_index;
        }
        /* TODO : check format */
        return true;
    }
    bool is_solvable () {
        /* rank(A) == rank(A|b) == n -> single solution   */
        /* rank(A) == rank(A|b) <  n -> infinite solution */
        /* rank(A) != rank(A|b)      -> no solution       */
        std::size_t rank_A = 0;
        std::size_t rank_Ab = 0;
        for (const LinearEquation<Complex>& equ : m_linear_equation_system) {
            if (!equ.is_zero()) {
                ++rank_A;
            }
            if (!equ.is_full_zero()) {
                ++rank_Ab;
            }
        }
        if (rank_A != rank_Ab) {
            std::cerr << "rank(A) = " << std::to_string(rank_A) << std::endl;
            std::cerr << "rank(A|b) = " << std::to_string(rank_Ab) << std::endl;
            std::cerr << "rank(A) != rank(A|b) -> no solution" << std::endl;
            return false;
        }
        else if (rank_A < get_num_variables()) {
            std::cerr << "rank(A) = " << std::to_string(rank_A) << std::endl;
            std::cerr << "rank(A|b) = " << std::to_string(rank_Ab) << std::endl;
            std::cerr << "number of variables = " << std::to_string(get_num_variables()) << std::endl;
            std::cerr << "rank(A) == rank(A|b) < number of variables -> infinite solution" << std::endl;
            return false;
        }
        else { return true; }
    }
    void exchange_equations (const std::size_t i, const std::size_t j) {
        if (i == j) return;
        LinearEquation<Complex> tmp = m_linear_equation_system[i];
        m_linear_equation_system[i] = m_linear_equation_system[j];
        m_linear_equation_system[j] = tmp;
    }
    bool get_leftmost_nonzero_indexes(std::size_t start_equ, std::size_t* ret_equ_index, std::size_t* ret_var_index) {
        for (std::size_t var_index = 0; var_index < get_num_variables(); ++var_index) {
            for (std::size_t equ_index = start_equ; equ_index < get_num_equations(); ++equ_index) {
                if (m_linear_equation_system[equ_index].get_coefficient(var_index) != Complex{0.0, 0.0}) {
                    *ret_equ_index = equ_index;
                    *ret_var_index = var_index;
                    return true;
                }
            }
        }
        /* no more nonzero equations in the subsystem below the given equation index */
        return false;
    }
public:
    LinearEquationSystem (std::size_t num_variables) : m_num_variables(num_variables) {
        m_labels.resize(num_variables + 1);
    }
    LinearEquationSystem () = delete;
    ~LinearEquationSystem () = default;

    void clear_equations () {
        m_linear_equation_system.clear();
    }

    bool append_equation (const LinearEquation<Complex>& equation) {
        if (equation.get_num_variables() != m_num_variables) { return false; }
        m_linear_equation_system.push_back(equation);
        return true;
    }

    bool set_label (const std::string& label, std::size_t index) {
        if (index >= m_labels.size()) { return false; }
        m_labels[index] = label;
        return true;
    }

    std::size_t get_num_variables () const { return m_num_variables; }
    std::size_t get_num_equations () const { return m_linear_equation_system.size(); }
    
    bool solve(std::vector<Complex>& solution) const {
        /* there must be at least as many equations as independent variables */
        if (get_num_variables() > get_num_equations()) {
            std::cerr << "more variables than equations -> unable to solve" << std::endl;
            return false;
        }
        LinearEquationSystem equation_system = *this;
        equation_system.forward_elimination();
        equation_system.back_substitution();
        if (!equation_system.is_solvable()) {
            std::cerr << "equation system is not solvable" << std::endl;
            return false;
        }
        solution = std::vector<Complex>(get_num_variables());
        for (size_t i = 0; i < equation_system.get_num_equations(); ++i) {
            for (size_t j = 0; j < equation_system.get_num_variables(); ++j) {
                if (equation_system.m_linear_equation_system[i][j] != Complex{0.0, 0.0}) {
                    solution[j] = equation_system.m_linear_equation_system[i].get_result();
                    break;
                }
            }
        }
        return true;
    }

    friend std::ostream& operator<<(std::ostream& os, const LinearEquationSystem& system) {
        os << "equ\\var";
        for (const auto& label : system.m_labels) {
            os << "," << label;
        }
        os << std::endl;
        for (std::size_t equ_index = 0; equ_index < system.get_num_equations(); ++equ_index) {
            os << system.m_linear_equation_system[equ_index] << std::endl;
        }
        return os;
    }
};

} /* namespace component */
} /* namespace zcalc */