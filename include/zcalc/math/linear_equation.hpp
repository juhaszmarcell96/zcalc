#pragma once

#include <cstdint>
#include <cstddef>
#include <iostream>
#include <vector>

#include <zcalc/math/complex.hpp>

namespace zcalc {
namespace math {

template <typename T>
class LinearEquation {
private:
    std::vector<T> m_a;
    T m_b;
public:
    LinearEquation (std::size_t num_variables) : m_a(num_variables, T{}), m_b(T{}) { }
    LinearEquation () = delete;
    ~LinearEquation () = default;

    void set_coefficient (std::size_t variable_index, const T& value) {
        m_a[variable_index] = value;
    }
    void set_result (const T& value) {
        m_b = value;
    }
    T get_coefficient (std::size_t variable_index) const {
        return m_a[variable_index];
    }
    T get_result () const {
        return m_b;
    }

    bool is_zero () const {
        for (std::size_t i = 0; i < m_a.size(); ++i) {
            if (m_a[i] != T{}) return false;
        }
        return true;
    }
    bool is_full_zero () const {
        if (m_b != T{}) return false;
        for (std::size_t i = 0; i < m_a.size(); ++i) {
            if (m_a[i] != T{}) return false;
        }
        return true;
    }

    std::size_t get_first_nonzero_coeff_index () const {
        for (std::size_t i = 0; i < m_a.size(); ++i) {
            if (m_a[i] != T{}) return i;
        }
        return -1;
    }

    T operator[](const std::size_t variable_index) const { return m_a[variable_index]; }
    T& operator[](const std::size_t variable_index) { return m_a[variable_index]; }

    std::size_t get_num_variables () const {
        return m_a.size();
    }

    LinearEquation<T>& operator+=(const LinearEquation<T>& other) {
        if (m_a.size() != other.m_a.size()) throw std::invalid_argument("equations must have the same number of variables");
        for (std::size_t i = 0; i < m_a.size(); ++i) {
            m_a[i] += other.m_a[i];
        }
        m_b += other.m_b;
        return *this;
    }
    LinearEquation<T>& operator-=(const LinearEquation<T>& other) {
        if (m_a.size() != other.m_a.size()) throw std::invalid_argument("equations must have the same number of variables");
        for (std::size_t i = 0; i < m_a.size(); ++i) {
            m_a[i] -= other.m_a[i];
        }
        m_b -= other.m_b;
        return *this;
    }
    LinearEquation<T>& operator*=(const T& value) {
        for (std::size_t i = 0; i < m_a.size(); ++i) {
            m_a[i] *= value;
        }
        m_b *= value;
        return *this;
    }
    LinearEquation<T>& operator/=(const T& value) {
        if (value == T{}) throw std::invalid_argument("cannot divide with zero");
        for (std::size_t i = 0; i < m_a.size(); ++i) {
            m_a[i] /= value;
        }
        m_b /= value;
        return *this;
    }

    LinearEquation<T> operator+(const LinearEquation<T>& rhs) const {
        if (m_a.size() != rhs.m_a.size()) throw std::invalid_argument("equations must have the same number of variables");
        LinearEquation<T> equation {m_a.size()};
        for (std::size_t i = 0; i < m_a.size(); ++i) {
            equation.m_a[i] = m_a[i] + rhs.m_a[i];
        }
        equation.m_b = m_b + rhs.m_b;
        return std::move(equation);
    }
    LinearEquation<T> operator-(const LinearEquation<T>& rhs) const {
        if (m_a.size() != rhs.m_a.size()) throw std::invalid_argument("equations must have the same number of variables");
        LinearEquation<T> equation {m_a.size()};
        for (std::size_t i = 0; i < m_a.size(); ++i) {
            equation.m_a[i] = m_a[i] - rhs.m_a[i];
        }
        equation.m_b = m_b - rhs.m_b;
        return std::move(equation);
    }
    LinearEquation<T> operator*(const T& rhs) const {
        LinearEquation<T> equation {m_a.size()};
        for (std::size_t i = 0; i < m_a.size(); ++i) {
            equation.m_a[i] = m_a[i] * rhs;
        }
        equation.m_b = m_b * rhs;
        return std::move(equation);
    }
    LinearEquation<T> operator/(const T& rhs) const {
        if (rhs == T{}) throw std::invalid_argument("cannot divide with zero");
        LinearEquation<T> equation {m_a.size()};
        for (std::size_t i = 0; i < m_a.size(); ++i) {
            equation.m_a[i] = m_a[i] / rhs;
        }
        equation.m_b = m_b / rhs;
        return std::move(equation);
    }

    friend std::ostream& operator<<(std::ostream& os, const LinearEquation<T>& equation) {
        for (std::size_t i = 0; i < equation.m_a.size(); ++i) {
            os << equation.m_a[i] << "  ";
        }
        os << "|" << equation.m_b;
        return os;
    }
};

} /* namespace component */
} /* namespace zcalc */