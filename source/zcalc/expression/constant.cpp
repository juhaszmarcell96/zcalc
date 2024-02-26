#include "zcalc/expression/constant.hpp"

#include <cmath>
#include <iomanip>

namespace zcalc {

Constant::Constant (complex value) : m_value(value) {}

bool Constant::is_numeric () const { return true; }

complex Constant::get () const { return m_value; }

void Constant::reduce () { return; }

bool Constant::is_zero () const { return std::abs(m_value) < epsilon; }

bool Constant::is_one () const {
    return ((std::abs(m_value.real() - 1.0)) < epsilon) && (std::abs(m_value.imag()) < epsilon);
}

void Constant::print (std::ostream &os) const {
    os << "(" << std::setprecision(4) << m_value.real() << "," << m_value.imag() << ")";
}

bool Constant::is_constant () const { return true; }
bool Constant::is_variable () const { return false; }
bool Constant::is_operation () const {return false; }

} // namespace zcalc