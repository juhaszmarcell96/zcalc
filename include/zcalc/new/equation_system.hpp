#pragma once

#include <cstdint>
#include <cstddef>
#include <iostream>
#include <iomanip>
#include <complex>
#include <map>
#include <vector>
#include <string>
#include <algorithm>

namespace zcalc {

typedef std::complex<double> complex;

class EquationSystem {
private:
    std::vector<std::string> m_variables;

    typedef std::vector<complex> row_t;
    std::vector<row_t> m_mat;

    static constexpr double epsilon = 1e-10;

    std::size_t get_num_variables () const { return m_variables.size(); }
    std::size_t get_num_equations () const { return m_mat.size(); }

    static bool is_zero (complex val) {
        return std::abs(val) < epsilon;
    }

    static bool is_one (complex val) {
        return (std::abs(val.real() - 1.0) < epsilon) && (std::abs(val.imag()) < epsilon);
    }

    bool variable_exists (const std::string& variable_name) {
        for (const std::string& var : m_variables) {
            if (var.compare(variable_name) == 0) {
                return true;
            }
        }
        return false;
    }

    std::size_t get_variable_index (const std::string& variable_name) {
        for (std::size_t i = 0; i < m_variables.size(); ++i) {
            if (m_variables[i].compare(variable_name) == 0) {
                return i;
            }
        }
        throw std::invalid_argument("variable '" + variable_name + "' not found");
    }

    void swap_equations (const std::size_t i, const std::size_t j) {
        std::swap<row_t>(m_mat[i], m_mat[j]);
    }

    bool get_next_pivot_pos(std::size_t start_equ, std::size_t* ret_equ_index, std::size_t* ret_var_index) {
        for (std::size_t i = start_equ; i < get_num_equations(); ++i) {
            for (std::size_t e = 0; e < get_num_variables(); ++e) {
                if (!is_zero(m_mat[i][e])) {
                    *ret_equ_index = i;
                    *ret_var_index = e;
                    return true;
                }
            }
        }
        /* no more nonzero equations in the subsystem below the given equation index */
        return false;
    }
    bool are_coefficients_zero (std::size_t row) const {
        for (std::size_t e = 0; e < m_variables.size(); ++e) {
            if (!is_zero(m_mat[row][e])) return false;
        }
        return true;
    }
    bool is_result_zero (std::size_t row) const {
        return is_zero(m_mat[row].back());
    }
public:
    EquationSystem () = default;
    ~EquationSystem () = default;

    void add_variable (const std::string& variable_name) {
        if (variable_exists(variable_name)) throw std::invalid_argument("variable '" + variable_name + "' already exists in equation");
        m_variables.push_back(variable_name);
    }

    void set_num_equations (std::size_t num_rows) {
        if (num_rows == 0) return;
        if (get_num_variables() == 0) throw std::invalid_argument("add the variables first");
        m_mat = std::vector<row_t>(num_rows);
        for (std::size_t i = 0; i < num_rows; ++i) {
            m_mat[i] = row_t(m_variables.size() + 1);
            for (std::size_t e = 0; e < m_variables.size() + 1; ++e) {
                m_mat[i][e] = complex{0.0, 0.0};
            }
        }
    }

    void set_coefficient (const std::string& variable_name, std::size_t row, complex value) {
        m_mat[row][get_variable_index(variable_name)] = value;
    }

    complex get_coefficient (const std::string& variable_name, std::size_t row) {
        return m_mat[row][get_variable_index(variable_name)];
    }

    void set_result (std::size_t row, complex value) {
        m_mat[row].back() = value;
    }

    complex get_result (std::size_t row) {
        return m_mat[row].back();
    }

    friend std::ostream& operator<<(std::ostream& os, const EquationSystem& equation) {
        if (equation.get_num_equations() == 0) return os;
        if (equation.get_num_variables() == 0) return os;
        for (std::size_t i = 0; i < equation.get_num_equations(); ++i) {
            for (std::size_t e = 0; e < equation.get_num_variables(); ++e) {
                os << equation.m_mat[i][e] << " * " << equation.m_variables[e] << " + ";
            }
            os << "0 = " << equation.m_mat[i].back() << std::endl;
        }
        return os;
    }

    bool forward_elimination () {
        /* algorithm for reducing the matrix to row echelon form */
        for (std::size_t i = 0; i < get_num_equations(); ++i) {
            /* STEP : determine the leftmost non-zero column */
            std::size_t pivot_i = 0;
            std::size_t pivot_e = 0;
            if (!get_next_pivot_pos(i, &pivot_i, &pivot_e)) {
                /* STEP : no more non-zero rows below the previous pivot position -> move on */
                break;
            }
            swap_equations(i, pivot_i);
            /* STEP : use elementary row operations to put a 1 in the topmost position of this column */
            complex divisor = m_mat[i][pivot_e];
            m_mat[i][pivot_e] = complex { 1.0, 0.0 };
            for (std::size_t e = pivot_e + 1; e < m_mat[i].size(); ++e) m_mat[i][e] /= divisor;
            /* STEP : use elementary row operations to put zeros below the pivot position */
            /*        -> subtract the scalar multiplication of this row from every row below it so that the values of the same column become 0 */
            for (std::size_t j = i + 1; j < get_num_equations(); ++j) {
                complex multiplier = m_mat[j][pivot_e] / m_mat[i][pivot_e];
                m_mat[j][pivot_e] = complex { 0.0, 0.0 };
                for (std::size_t e = pivot_e + 1; e < m_mat[j].size(); ++e) m_mat[j][e] -= m_mat[i][e] * multiplier;
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
        for (int i = (int)get_num_equations() - 1; i >= 0; --i) {
            if (are_coefficients_zero(i)) continue;
            std::size_t e;
            for (e = 0; e < get_num_variables(); ++e) if (!is_zero(m_mat[i][e])) break;
            for (int j = i - 1; j >= 0; --j) {
                complex multiplier = m_mat[j][e] / m_mat[i][e];
                m_mat[j][e] -= multiplier * m_mat[i][e];
                m_mat[j].back() -= multiplier * m_mat[i].back();
            }
        }
        /* TODO : check format */
        return true;
    }
    void check_solvable () {
        /* rank(A) == rank(A|b) == n -> single solution   */
        /* rank(A) == rank(A|b) <  n -> infinite solution */
        /* rank(A) != rank(A|b)      -> no solution       */
        std::size_t rank_A = 0;
        std::size_t rank_Ab = 0;
        for (std::size_t i = 0; i < get_num_equations(); ++i) {
            if (!are_coefficients_zero(i)) {
                ++rank_A;
                if (!is_result_zero(i)) {
                    ++rank_Ab;
                }
            }
        }
        if (rank_A != rank_Ab) {
            throw std::runtime_error("rank(A) != rank(A|b) -> no solution");
        }
        else if (rank_A < get_num_variables()) {
            throw std::runtime_error("rank(A) == rank(A|b) <  number of variables -> infinite solution");
        }
    }
    
    complex solve_for(const std::string& variable_name) const {
        if (get_num_equations() == 0) {
            throw std::runtime_error("no equation in the system");
        }
        if (get_num_variables() == 0) {
            throw std::runtime_error("no variables in the system");
        }
        if (get_num_variables() > get_num_equations()) {
            throw std::runtime_error("not enough equations, the system is not solvable");
        }
        EquationSystem equation_system = *this;
        equation_system.forward_elimination();
        equation_system.back_substitution();
        equation_system.check_solvable();
        for (size_t i = 0; i < equation_system.get_num_equations(); ++i) {
            if (is_one(equation_system.get_coefficient(variable_name, i))) {
                return equation_system.get_result(i);
            }
        }
        return true;
    }
};

} /* namespace zcalc */