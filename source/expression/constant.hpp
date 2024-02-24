#pragma once

#include "zcalc/complex.hpp"

#include <cmath>
#include <ostream>
#include <iomanip>

namespace zcalc {

class Constant {
private:
    complex m_value { 0.0, 0.0 };
public:
    Constant ();
    ~Constant() = default;
    Constant (complex value) : m_value(value) {}
    complex get () { return m_value; }
    bool is_zero () { return std::abs(m_value) < epsilon; }
    bool is_one () {
        return ((std::abs(m_value.real() - 1.0)) < epsilon) && (std::abs(m_value.imag()) < epsilon);
    }
    friend std::ostream& operator<<(std::ostream &os, const Constant& c) {
        os << "(" << std::setprecision(4) << c.m_value.real() << "," << c.m_value.imag() << ")";
        return os;
    }
};

} // namespace zcalc