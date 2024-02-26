#include "zcalc/expression/constant.hpp"

#include <cmath>
#include <iomanip>

namespace zcalc {

Constant::Constant (complex value) : m_value(value) {}

bool Constant::is_numeric () { return true; }

complex Constant::get () { return m_value; }

void Constant::reduce () { return; }

bool Constant::is_zero () { return std::abs(m_value) < epsilon; }

bool Constant::is_one () {
    return ((std::abs(m_value.real() - 1.0)) < epsilon) && (std::abs(m_value.imag()) < epsilon);
}

void Constant::print (std::ostream &os) {
    os << "(" << std::setprecision(4) << m_value.real() << "," << m_value.imag() << ")";
}

} // namespace zcalc