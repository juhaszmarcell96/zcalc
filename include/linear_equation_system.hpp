#include <cstdint>
#include <cstddef>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <memory>
#include <numbers>
#include <stdexcept>

#include <include/linear_equation.hpp>

namespace zcalc {

/*
a (nxm = 2x3) | b
    a_00 a_01 a_02 | b_0
    a_10 a_11 a_12 | b_1
*/

class LinearEquationSystem {
private:
    std::size_t m_num_variables = 0;
    std::vector<LinearEquation<Complex>> m_linear_equation_system;

    bool forward_elimination ();
    bool back_substitution ();
    bool is_solvable ();
    void exchange_equations (const std::size_t i, const std::size_t j);
    bool get_leftmost_nonzero_indexes(std::size_t start_equ, std::size_t* ret_equ_index, std::size_t* ret_var_index);
public:
    LinearEquationSystem (std::size_t num_variables);
    LinearEquationSystem () = delete;
    ~LinearEquationSystem () = default;

    bool append_equation (const LinearEquation<Complex> & equation);

    std::size_t get_num_variables () const;
    std::size_t get_num_equations () const;
    
    bool solve(std::vector<Complex>& solution) const;

    friend std::ostream& operator<<(std::ostream& os, const LinearEquationSystem& system);
};

} /* namespace zcalc */