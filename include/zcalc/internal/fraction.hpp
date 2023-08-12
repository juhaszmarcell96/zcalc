#pragma once

#include <cstdint>
#include <iostream>
#include <stdexcept>
#include <cmath>

namespace zcalc {

class Fraction {
private:
    std::int64_t m_numerator { 0 };
    std::int64_t m_denominator { 1 };

    /* greatest common divisor */
    static std::int64_t gcd (std::int64_t a, std::int64_t b) {
        //if (a == 0 || b == 0) return 1;
        //if (a < 0) a *= -1;
        //if (b < 0) b *= -1;
        //while (a != b) {
        //    if (a > b) a -= b;
        //    else b -= a;
        //}
        //return a;
        if (b == 0) return a;
        return gcd(b, a % b);
    }

    /* least common multiple */
    static std::int64_t lcm (std::int64_t a, std::int64_t b) {
        if (a == 0 || b == 0) return 1;
        if (a < 0) a *= -1;
        if (b < 0) b *= -1;
        std::int64_t c = gcd(a, b);
        return a * b / c;
    }

    static void simplify (std::int64_t& num, std::int64_t& den) {
        std::int64_t divisor = gcd (num, den);
        num /= divisor;
        den /= divisor;
    }

    void set (std::int64_t numerator, std::int64_t denominator) {
        if (denominator == 0) {
            throw std::runtime_error("cannot divide by 0");
        }
        if (numerator == 0) {
            m_denominator = 1;
            m_numerator = 0;
            return;
        }
        simplify (numerator, denominator);
        if ((numerator < 0) && (denominator < 0)) {
            m_numerator = numerator * -1;
            m_denominator = denominator * -1;
            return;
        }
        if ((denominator < 0) && (numerator > 0)) {
            m_numerator = numerator * -1;
            m_denominator = denominator * -1;
            return;
        }
        m_numerator = numerator;
        m_denominator = denominator;
    }
public:
    Fraction () = default;
    Fraction (std::int64_t numerator, std::int64_t denominator) {
        set (numerator, denominator);
    }
    Fraction (int value) {
        set (value, 1);
    }
    Fraction (double value) {
        /* operates with 0.1 pico resolution (10^-13) */
        int exp = 13;
        while (value > 10) {
            value /= 10;
            exp -= 1;
        }
        set (value * std::pow(10, 13), std::pow(10, exp));
    }
    ~Fraction () = default;

    double evaluate () const { return (double)m_numerator / (double)m_denominator; }

    Fraction operator-() { return Fraction{-m_numerator, m_denominator}; }
    Fraction operator+() { return Fraction{ m_numerator, m_denominator}; }

    Fraction& operator+=(const Fraction& other) {
        std::int64_t lcm_denom = lcm(m_denominator, other.m_denominator);
        std::int64_t own_mul = lcm_denom / m_denominator;
        std::int64_t other_mul = lcm_denom / other.m_denominator;
        set (m_numerator * own_mul + other.m_numerator * other_mul, lcm_denom);
        return *this;
    }
    Fraction& operator-=(const Fraction& other) {
        std::int64_t lcm_denom = lcm(m_denominator, other.m_denominator);
        std::int64_t own_mul = lcm_denom / m_denominator;
        std::int64_t other_mul = lcm_denom / other.m_denominator;
        set (m_numerator * own_mul - other.m_numerator * other_mul, lcm_denom);
        return *this;
    }
    Fraction& operator*=(const Fraction& other) {
        set (m_numerator * other.m_numerator, m_denominator * other.m_denominator);
        return *this;
    }
    Fraction& operator/=(const Fraction& other) {
        set (m_numerator * other.m_denominator, m_denominator * other.m_numerator);
        return *this;
    }

    Fraction operator+(const Fraction& rhs) const {
        std::int64_t lcm_denom = lcm(m_denominator, rhs.m_denominator);
        std::int64_t own_mul = lcm_denom / m_denominator;
        std::int64_t other_mul = lcm_denom / rhs.m_denominator;
        std::int64_t new_numerator = m_numerator * own_mul + rhs.m_numerator * other_mul;
        std::int64_t new_denominator = lcm_denom;
        return Fraction {new_numerator, new_denominator};
    }
    Fraction operator-(const Fraction& rhs) const {
        std::int64_t lcm_denom = lcm(m_denominator, rhs.m_denominator);
        std::int64_t own_mul = lcm_denom / m_denominator;
        std::int64_t other_mul = lcm_denom / rhs.m_denominator;
        std::int64_t new_numerator = m_numerator * own_mul - rhs.m_numerator * other_mul;
        std::int64_t new_denominator = lcm_denom;
        return Fraction {new_numerator, new_denominator};
    }
    Fraction operator*(const Fraction& rhs) const {
        return Fraction {m_numerator * rhs.m_numerator, m_denominator * rhs.m_denominator};
    }
    Fraction operator/(const Fraction& rhs) const {
        return Fraction {m_numerator * rhs.m_denominator, m_denominator * rhs.m_numerator};
    }

    friend std::ostream& operator<<(std::ostream& os, const Fraction& f) {
        os << f.m_numerator << "/" << f.m_denominator;
        return os;
    }

    friend bool operator==(const Fraction& f0, const Fraction& f1) {
        if ((f0.m_numerator == f1.m_numerator) && (f0.m_denominator == f1.m_denominator)) { return true; }
        if ((f0.m_numerator == (f1.m_numerator * -1)) && (f0.m_denominator == (f1.m_denominator * -1))) { return true; }
        if ((f0.m_numerator == 0) && (f1.m_numerator == 0)) return true;
        return false;
    }
    friend bool operator!=(const Fraction& f0, const Fraction& f1) { return !(f0 == f1); }
};

} /* namespace zcalc */
