#include <cstdint>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <memory>
#include <numbers>
#include <stdexcept>

#include <include/complex.hpp>

namespace zcalc {

/*
nxm = 2x3
    a_00 a_01 a_02
    a_10 a_11 a_12
*/

class Matrix {
private:
    std::vector<std::vector<Complex>> m_matrix;

    std::size_t count_nonzero_rows (std::size_t start_row, std::size_t end_row, std::size_t start_col, std::size_t end_col);
    bool get_leftmost_nonzero_indexes(std::size_t start_row, std::size_t* ret_row_index, std::size_t* ret_col_index);
    void switch_rows (const std::size_t i, const std::size_t j);
    bool move_nonzero_row (std::size_t starting_row_index, std::size_t column_index);
    bool is_row_zero (std::size_t row_index);
    bool are_values_zero (std::size_t row_index, std::size_t col_start, std::size_t col_end);
public:
    Matrix (std::size_t num_rows, std::size_t num_cols, const Complex& fill_value);
    Matrix (std::size_t num_rows, std::size_t num_cols);
    Matrix () = delete;
    ~Matrix () = default;

    std::size_t get_num_rows () const;
    std::size_t get_num_cols () const;

    std::vector<Complex> operator[](const std::size_t i) const;
    std::vector<Complex>& operator[](const std::size_t i);
    Complex operator()(const std::size_t i, const std::size_t j) const;
    Complex& operator()(const std::size_t i, const std::size_t j);
    std::vector<Complex> operator()(const std::size_t i) const;
    std::vector<Complex>& operator()(const std::size_t i);
    Matrix operator+(const Matrix& matrix) const;
    Matrix operator-(const Matrix& matrix) const;
    Matrix operator*(const Complex& scalar) const;
    friend Matrix operator*(const Complex& scalar, const Matrix& matrix);
    Matrix operator/(const Complex& scalar) const;
    friend Matrix operator/(const Complex& scalar, const Matrix& matrix);
    Matrix& operator=(const Matrix& matrix);
    friend bool operator==(const Matrix& matrix_1, const Matrix& matrix_2);
    friend bool operator!=(const Matrix& matrix_1, const Matrix& matrix_2);
    
    /* A_nxm * B_mxr = C_nxr */
    Matrix operator*(const Matrix& matrix) const;
    
    bool solve_system_of_linear_equations(std::vector<Complex>& solution);

    void print ();

    friend std::ostream& operator<<(std::ostream& os, const Matrix& matrix);
};

} /* namespace zcalc */