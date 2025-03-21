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
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <memory>
#include <complex>
#include <numbers>
#include <stdexcept>

namespace zcalc {
namespace math {

struct Dimensions {
    std::size_t row { 0 };
    std::size_t col { 0 };
};

/*
nxm = 2x3
    a_00 a_01 a_02
    a_10 a_11 a_12
*/

template<typename T>
class Matrix {
private:
    std::vector<std::vector<T>> m_matrix;
public:
    Matrix (std::size_t num_rows, std::size_t num_cols) {
        if (num_rows == 0) { throw std::invalid_argument("number of rows cannot be 0"); }
        if (num_cols == 0) { throw std::invalid_argument("number of columns cannot be 0"); }
        m_matrix = std::vector<std::vector<T>>(num_rows, std::vector<T>(num_cols, T{}));
    }
    Matrix () = delete;
    ~Matrix () = default;

    std::size_t get_num_rows () const { return m_matrix.size(); }
    std::size_t get_num_cols () const { return m_matrix[0].size(); }
    Dimensions get_dimensions () const {
        return Dimensions { .row = get_num_rows(), .col = get_num_cols() };
    }

    const std::vector<T>& operator[](const std::size_t i) const { return m_matrix[i]; }
    std::vector<T>& operator[](const std::size_t i) { return m_matrix[i]; }
    T operator()(const std::size_t i, const std::size_t j) const { return m_matrix[i][j]; }
    T& operator()(const std::size_t i, const std::size_t j) { return m_matrix[i][j]; }
    const std::vector<T>& operator()(const std::size_t i) const { return m_matrix[i]; }
    std::vector<T>& operator()(const std::size_t i) { return m_matrix[i]; }
    Matrix<T> operator+(const Matrix<T>& matrix) const {
        if (matrix.get_num_rows() != get_num_rows()) { throw std::invalid_argument("matrixes must be of the same dimension"); }
        if (matrix.get_num_cols() != get_num_cols()) { throw std::invalid_argument("matrixes must be of the same dimension"); }
        Matrix<T> ret_matrix {get_num_rows(), get_num_cols()};
        for (std::size_t i = 0; i < get_num_rows(); ++i) {
            for (std::size_t j = 0; j < get_num_cols(); ++j) {
                ret_matrix.m_matrix[i][j] = m_matrix[i][j] + matrix.m_matrix[i][j];
            }
        }
        return std::move(ret_matrix);
    }
    Matrix<T> operator-(const Matrix<T>& matrix) const {
        if (matrix.get_num_rows() != get_num_rows()) { throw std::invalid_argument("matrixes must be of the same dimension"); }
        if (matrix.get_num_cols() != get_num_cols()) { throw std::invalid_argument("matrixes must be of the same dimension"); }
        Matrix<T> ret_matrix {get_num_rows(), get_num_cols()};
        for (std::size_t i = 0; i < get_num_rows(); ++i) {
            for (std::size_t j = 0; j < get_num_cols(); ++j) {
                ret_matrix.m_matrix[i][j] = m_matrix[i][j] - matrix.m_matrix[i][j];
            }
        }
        return std::move(ret_matrix);
    }
    Matrix<T> operator*(const T& scalar) const {
        Matrix<T> ret_matrix {get_num_rows(), get_num_cols()};
        for (std::size_t i = 0; i < get_num_rows(); ++i) {
            for (std::size_t j = 0; j < get_num_cols(); ++j) {
                ret_matrix.m_matrix[i][j] = scalar * m_matrix[i][j];
            }
        }
        return std::move(ret_matrix);
    }
    friend Matrix<T> operator*(const T& scalar, const Matrix<T>& matrix) {
        Matrix<T> ret_matrix {matrix.get_num_rows(), matrix.get_num_cols()};
        for (std::size_t i = 0; i < matrix.get_num_rows(); ++i) {
            for (std::size_t j = 0; j < matrix.get_num_cols(); ++j) {
                ret_matrix.m_matrix[i][j] = scalar * matrix.m_matrix[i][j];
            }
        }
        return std::move(ret_matrix);
    }
    Matrix<T> operator/(const T& scalar) const {
        Matrix<T> ret_matrix {get_num_rows(), get_num_cols()};
        for (std::size_t i = 0; i < get_num_rows(); ++i) {
            for (std::size_t j = 0; j < get_num_cols(); ++j) {
                ret_matrix.m_matrix[i][j] = m_matrix[i][j] / scalar;
            }
        }
        return std::move(ret_matrix);
    }
    friend Matrix<T> operator/(const T& scalar, const Matrix<T>& matrix) {
        Matrix<T> ret_matrix {matrix.get_num_rows(), matrix.get_num_cols()};
        for (std::size_t i = 0; i < matrix.get_num_rows(); ++i) {
            for (std::size_t j = 0; j < matrix.get_num_cols(); ++j) {
                ret_matrix.m_matrix[i][j] = scalar / matrix.m_matrix[i][j];
            }
        }
        return std::move(ret_matrix);
    }

    Matrix<T>& operator=(const Matrix<T>& matrix) {
        m_matrix = matrix.m_matrix;
        return *this;
    }

    friend bool operator==(const Matrix<T>& matrix_1, const Matrix<T>& matrix_2) {
        if (matrix_1.get_num_rows() != matrix_2.get_num_rows()) return false;
        if (matrix_1.get_num_cols() != matrix_2.get_num_cols()) return false;
        for (std::size_t i = 0; i < matrix_1.get_num_rows(); ++i) {
            for (std::size_t j = 0; j < matrix_1.get_num_cols(); ++j) {
                if (matrix_1.m_matrix[i][j] != matrix_2.m_matrix[i][j]) return false;
            }
        }
        return true;
    }

    friend bool operator!=(const Matrix<T>& matrix_1, const Matrix<T>& matrix_2) {
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
    Matrix<T> operator*(const Matrix<T>& matrix) const {
        if (get_num_cols() != matrix.get_num_rows()) { throw std::invalid_argument("matrixes must be of the same dimension"); }
        Matrix<T> ret_matrix {get_num_rows(), matrix.get_num_cols()};
        for (std::size_t i = 0; i < ret_matrix.get_num_rows(); ++i) {
            for (std::size_t j = 0; j < ret_matrix.get_num_cols(); ++j) {
                ret_matrix.m_matrix[i][j] = T{};
                for (std::size_t k = 0; k < get_num_cols(); ++k) {
                    ret_matrix.m_matrix[i][j] += m_matrix[i][k] * matrix.m_matrix[k][j];
                }
            }
        }
        return std::move(ret_matrix);
    }

    friend std::ostream& operator<<(std::ostream& os, const Matrix& matrix) {
        os << "dimensions : " << matrix.get_num_rows() << "x" << matrix.get_num_cols() << std::endl;
        for (const std::vector<T>& row : matrix.m_matrix) {
            os << "[ ";
            for (const T& val : row) {
                os << val << " ";
            }
            os << "]" << std::endl;
        }
        return os;
    }
};

} /* namespace component */
} /* namespace zcalc */