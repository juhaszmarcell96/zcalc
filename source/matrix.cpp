#include <include/matrix.hpp>

namespace zcalc {

std::size_t Matrix::count_nonzero_rows (std::size_t start_row, std::size_t end_row, std::size_t start_col, std::size_t end_col) {
    std::size_t count = 0;
    for (std::size_t row_index = start_row; row_index <= end_row; ++row_index) {
        bool is_row_all_zero = true;
        for (std::size_t col_index = start_col; col_index <= end_col; ++col_index) {
            if (m_matrix[row_index][col_index] != Complex{0.0, 0.0}) {
                is_row_all_zero = false;
            }
        }
        if (!is_row_all_zero) ++count;
    }
    return count;
}

bool Matrix::get_leftmost_nonzero_indexes(std::size_t start_row, std::size_t* ret_row_index, std::size_t* ret_col_index) {
    for (std::size_t col_index = 0; col_index < get_num_cols(); ++col_index) {
        for (std::size_t row_index = start_row; row_index < get_num_rows(); ++row_index) {
            if (m_matrix[row_index][col_index] != Complex{0.0, 0.0}) {
                *ret_row_index = row_index;
                *ret_col_index = col_index;
                return true;
            }
        }
    }
    /* no more nonzero rows in the submatrix below the given row index */
    return false;
}

void Matrix::switch_rows (const std::size_t i, const std::size_t j) {
    if (i == j) return;
    std::vector<Complex> tmp = m_matrix[i];
    m_matrix[i] = m_matrix[j];
    m_matrix[j] = tmp;
}

bool Matrix::move_nonzero_row (std::size_t starting_row_index, std::size_t column_index) {
    for (std::size_t i = starting_row_index; i < get_num_rows(); ++i) {
        if (m_matrix[i][column_index] != Complex{0.0, 0.0}) {
            switch_rows(starting_row_index, i);
            return true;
        }
    }
    return false;
}

bool Matrix::is_row_zero (std::size_t row_index) {
    for (std::size_t col_index = 0; col_index < get_num_cols(); ++col_index) {
        if (m_matrix[row_index][col_index] != Complex{0.0, 0.0}) {
            return false;
        }
    }
    return true;
}

bool Matrix::are_values_zero (std::size_t row_index, std::size_t col_start, std::size_t col_end) {
    for (std::size_t col_index = col_start; col_index < col_end; ++col_index) {
        if (m_matrix[row_index][col_index] != Complex{0.0, 0.0}) {
            return false;
        }
    }
    return true;
}

Matrix::Matrix (std::size_t num_rows, std::size_t num_cols, const Complex& fill_value) {
    if (num_rows == 0) throw std::invalid_argument("number of rows cannot be 0");
    if (num_cols == 0) throw std::invalid_argument("number of columns cannot be 0");
    m_matrix = std::vector<std::vector<Complex>>(num_rows, std::vector<Complex>(num_cols, fill_value));
}
Matrix::Matrix (std::size_t num_rows, std::size_t num_cols) {
    if (num_rows == 0) throw std::invalid_argument("number of rows cannot be 0");
    if (num_cols == 0) throw std::invalid_argument("number of columns cannot be 0");
    m_matrix = std::vector<std::vector<Complex>>(num_rows, std::vector<Complex>(num_cols));
}

std::size_t Matrix::get_num_rows () const { return m_matrix.size(); }
std::size_t Matrix::get_num_cols () const { return m_matrix[0].size(); }

std::vector<Complex> Matrix::operator[](const std::size_t i) const { return m_matrix[i]; }
std::vector<Complex>& Matrix::operator[](const std::size_t i) { return m_matrix[i]; }
Complex Matrix::operator()(const std::size_t i, const std::size_t j) const { return m_matrix[i][j]; }
Complex& Matrix::operator()(const std::size_t i, const std::size_t j) { return m_matrix[i][j]; }
std::vector<Complex> Matrix::operator()(const std::size_t i) const { return m_matrix[i]; }
std::vector<Complex>& Matrix::operator()(const std::size_t i) { return m_matrix[i]; }
Matrix Matrix::operator+(const Matrix& matrix) const {
    if (matrix.get_num_rows() != get_num_rows()) throw std::invalid_argument("matrixes must be of the same dimension");
    if (matrix.get_num_cols() != get_num_cols()) throw std::invalid_argument("matrixes must be of the same dimension");
    Matrix ret_matrix {get_num_rows(), get_num_cols()};
    for (std::size_t i = 0; i < get_num_rows(); ++i) {
        for (std::size_t j = 0; j < get_num_cols(); ++j) {
            ret_matrix.m_matrix[i][j] = m_matrix[i][j] + matrix.m_matrix[i][j];
        }
    }
    return std::move(ret_matrix);
}
Matrix Matrix::operator-(const Matrix& matrix) const {
    if (matrix.get_num_rows() != get_num_rows()) throw std::invalid_argument("matrixes must be of the same dimension");
    if (matrix.get_num_cols() != get_num_cols()) throw std::invalid_argument("matrixes must be of the same dimension");
    Matrix ret_matrix {get_num_rows(), get_num_cols()};
    for (std::size_t i = 0; i < get_num_rows(); ++i) {
        for (std::size_t j = 0; j < get_num_cols(); ++j) {
            ret_matrix.m_matrix[i][j] = m_matrix[i][j] - matrix.m_matrix[i][j];
        }
    }
    return std::move(ret_matrix);
}
Matrix Matrix::operator*(const Complex& scalar) const {
    Matrix ret_matrix {get_num_rows(), get_num_cols()};
    for (std::size_t i = 0; i < get_num_rows(); ++i) {
        for (std::size_t j = 0; j < get_num_cols(); ++j) {
            ret_matrix.m_matrix[i][j] = scalar * m_matrix[i][j];
        }
    }
    return std::move(ret_matrix);
}
Matrix operator*(const Complex& scalar, const Matrix& matrix) {
    Matrix ret_matrix {matrix.get_num_rows(), matrix.get_num_cols()};
    for (std::size_t i = 0; i < matrix.get_num_rows(); ++i) {
        for (std::size_t j = 0; j < matrix.get_num_cols(); ++j) {
            ret_matrix.m_matrix[i][j] = scalar * matrix.m_matrix[i][j];
        }
    }
    return std::move(ret_matrix);
}
Matrix Matrix::operator/(const Complex& scalar) const {
    Matrix ret_matrix {get_num_rows(), get_num_cols()};
    for (std::size_t i = 0; i < get_num_rows(); ++i) {
        for (std::size_t j = 0; j < get_num_cols(); ++j) {
            ret_matrix.m_matrix[i][j] = scalar / m_matrix[i][j];
        }
    }
    return std::move(ret_matrix);
}
Matrix operator/(const Complex& scalar, const Matrix& matrix) {
    Matrix ret_matrix {matrix.get_num_rows(), matrix.get_num_cols()};
    for (std::size_t i = 0; i < matrix.get_num_rows(); ++i) {
        for (std::size_t j = 0; j < matrix.get_num_cols(); ++j) {
            ret_matrix.m_matrix[i][j] = scalar / matrix.m_matrix[i][j];
        }
    }
    return std::move(ret_matrix);
}

Matrix& Matrix::operator=(const Matrix& matrix) {
    m_matrix = matrix.m_matrix;
    return *this;
}

bool operator==(const Matrix& matrix_1, const Matrix& matrix_2) {
    if (matrix_1.get_num_rows() != matrix_2.get_num_rows()) return false;
    if (matrix_1.get_num_cols() != matrix_2.get_num_cols()) return false;
    for (std::size_t i = 0; i < matrix_1.get_num_rows(); ++i) {
        for (std::size_t j = 0; j < matrix_1.get_num_cols(); ++j) {
            if (matrix_1.m_matrix[i][j] != matrix_2.m_matrix[i][j]) return false;
        }
    }
    return true;
}

bool operator!=(const Matrix& matrix_1, const Matrix& matrix_2) {
    if (matrix_1.get_num_rows() != matrix_2.get_num_rows()) return true;
    if (matrix_1.get_num_cols() != matrix_2.get_num_cols()) return true;
    for (std::size_t i = 0; i < matrix_1.get_num_rows(); ++i) {
        for (std::size_t j = 0; j < matrix_1.get_num_cols(); ++j) {
            if (matrix_1.m_matrix[i][j] != matrix_2.m_matrix[i][j]) return true;
        }
    }
    return false;
}

/* A_nxm * B_mxr = C_nxr */
Matrix Matrix::operator*(const Matrix& matrix) const {
    if (get_num_cols() != matrix.get_num_rows())  throw std::invalid_argument("matrixes must be of the same dimension");
    Matrix ret_matrix {get_num_rows(), matrix.get_num_cols()};
    for (std::size_t i = 0; i < ret_matrix.get_num_rows(); ++i) {
        for (std::size_t j = 0; j < ret_matrix.get_num_cols(); ++j) {
            ret_matrix.m_matrix[i][j] = Complex { 0.0, 0.0 };
            for (std::size_t k = 0; k < get_num_cols(); ++k) {
                ret_matrix.m_matrix[i][j] += m_matrix[i][k] * matrix.m_matrix[k][j];
            }
        }
    }
    return std::move(ret_matrix);
}

bool Matrix::solve_system_of_linear_equations(std::vector<Complex>& solution) {
    //std::cout << "###################### elimination ######################" << std::endl;
    //print();
    /* there must be more equations than variables -> equal or more more rows than columns */
    if (get_num_cols() > get_num_rows() + 1) return false;
    /* algorithm for reducing the matrix to row echelon form */
    for (std::size_t row_index = 0; row_index < get_num_rows(); ++row_index) {
        /* STEP : determine the leftmost non-zero column */
        //std::cout << "STEP : determine the leftmost non-zero column" << std::endl;
        std::size_t leftmost_nonzero_col_index = 0;
        std::size_t leftmost_nonzero_row_index = 0;
        if (!get_leftmost_nonzero_indexes(row_index, &leftmost_nonzero_row_index, &leftmost_nonzero_col_index)) {
            /* STEP : no more non-zero rows below the previous pivot position -> move on */
            //std::cout << "STEP : no more non-zero rows below the previous pivot position -> move on" << std::endl;
            break;
        }
        //std::cout << "leftmost_nonzero_col_index : " << leftmost_nonzero_col_index << std::endl;
        //std::cout << "leftmost_nonzero_row_index : " << leftmost_nonzero_row_index << std::endl;
        switch_rows(row_index, leftmost_nonzero_row_index);
        //print();
        /* STEP : use elementary row operations to put a 1 in the topmost position of this column */
        //std::cout << "STEP : use elementary row operations to put a 1 in the topmost position of this column" << std::endl;
        Complex divisor = m_matrix[row_index][leftmost_nonzero_col_index];
        m_matrix[row_index][leftmost_nonzero_col_index] = Complex { 1.0, 0.0 };
        for (std::size_t col_index = leftmost_nonzero_col_index + 1; col_index < get_num_cols(); ++col_index) {
            if (m_matrix[row_index][col_index] != Complex{0.0, 0.0}) m_matrix[row_index][col_index] = m_matrix[row_index][col_index] / divisor;
        }
        //print();
        /* STEP : use elementary row operations to put zeros below the pivot position */
        /*        -> subtract the scalar multiplication of this row from every row below it so that the values of the same column become 0 */
        //std::cout << "STEP : use elementary row operations to put zeros below the pivot position" << std::endl;
        for (std::size_t i = row_index + 1; i < get_num_rows(); ++i) {
            Complex multiplier = m_matrix[i][leftmost_nonzero_col_index] / m_matrix[row_index][leftmost_nonzero_col_index];
            for (std::size_t j = 0; j < get_num_cols(); ++j) {
                m_matrix[i][j] = m_matrix[i][j] - multiplier * m_matrix[row_index][j];
            }
        }
        //print();
    }
    //print();
    /* at this point we have a row echelon form -> check maybe? */

    /* last some rows must be all 0 -> some kind of check would be nice TODO */
    /* something is wrong if only the last column is non zero but the variables all have 0 as coefficient */
    /* the matrix, excluding the zero rows, should be a square matrix? */
    /* start from the last row */
    std::size_t last_col_index = get_num_cols() - 1;
    int row_index = (int)get_num_rows() - 1;
    /* skip every full zero row */
    for (row_index; row_index >= 0; --row_index) {
        if (are_values_zero(row_index, 0, get_num_cols() - 1)) continue;
        std::size_t leading_one_index;
        for (size_t col_index = 0; col_index < get_num_cols() - 1; ++col_index) {
            if (m_matrix[row_index][col_index] != Complex{0.0, 0.0}) leading_one_index = col_index;
        }
        for (int backsub_row_index = row_index - 1; backsub_row_index >= 0; --backsub_row_index) {
            Complex multiplier = m_matrix[backsub_row_index][leading_one_index] / m_matrix[row_index][leading_one_index];
            m_matrix[backsub_row_index][leading_one_index] = m_matrix[backsub_row_index][leading_one_index] - (multiplier * m_matrix[row_index][leading_one_index]);
            m_matrix[backsub_row_index][last_col_index] = m_matrix[backsub_row_index][last_col_index] - (multiplier * m_matrix[row_index][last_col_index]);
        }
        --leading_one_index;
        //print();
    }
    
    /* rank(A) == rank(A|b) == n -> single solution   */
    /* rank(A) == rank(A|b) <  n -> infinite solution */
    /* rank(A) != rank(A|b)      -> no solution       */
    std::size_t rank_A  = count_nonzero_rows(0, get_num_rows() - 1, 0, get_num_cols() - 2);
    std::size_t rank_Ab = count_nonzero_rows(0, get_num_rows() - 1, 0, get_num_cols() - 1);
    //std::cout << rank_A << " " << rank_Ab << std::endl;
    if (rank_A != rank_Ab) {
        //std::cout << "ERROR : cannot solve equation system" << std::endl;
        return false;
    }
    else if (rank_A < get_num_cols() - 1) {
        //std::cout << "ERROR : equation system has infinite solutions" << std::endl;
        return false;
    }
    //std::cout << "#########################################################" << std::endl;
    /* solution */
    solution = std::vector<Complex>(get_num_cols() - 1);
    for (size_t i = 0; i < get_num_rows(); ++i) {
        for (size_t j = 0; j < get_num_cols() - 1; ++j) {
            if (m_matrix[i][j] != Complex{0.0, 0.0}) {
                solution[j] = m_matrix[i][get_num_cols() - 1];
                break;
            }
        }
    }
    return true;
}

void Matrix::print () {
    std::cout << "dimensions : " << get_num_rows() << "x" << get_num_cols() << std::endl;
    for (const std::vector<Complex>& row : m_matrix) {
        std::cout << "[ ";
        for (const Complex& val : row) {
            std::cout << val << " ";
        }
        std::cout << "]" << std::endl;
    }
}

std::ostream& operator<<(std::ostream& os, const Matrix& matrix) {
    os << "dimensions : " << matrix.get_num_rows() << "x" << matrix.get_num_cols() << std::endl;
    for (const std::vector<Complex>& row : matrix.m_matrix) {
        os << "[ ";
        for (const Complex& val : row) {
            os << val << " ";
        }
        os << "]" << std::endl;
    }
    return os;
}

} /* namespace zcalc */