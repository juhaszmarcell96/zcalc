#include "zcalc/expression/constant.hpp"

#include <cmath>
#include <iomanip>

namespace zcalc {

Constant::Constant (complex value) : m_value(value) {}

term_types Constant::get_type () const { return term_types::constant; }

bool Constant::is_numeric () const { return true; }

complex Constant::get_value () const { return m_value; }

void Constant::simplify () { return; }

bool Constant::is_zero () const { return std::abs(m_value) < epsilon; }

bool Constant::is_one () const {
    return ((std::abs(m_value.real() - 1.0)) < epsilon) && (std::abs(m_value.imag()) < epsilon);
}

void Constant::print (std::ostream &os) const {
    if (std::abs(m_value.imag()) < epsilon) {
        os << std::setprecision(4) << m_value.real();
    }
    else {
        os << "(" << std::setprecision(4) << m_value.real();
        if (m_value.imag() < 0.0) {
            os << "-" << (m_value.imag() * (-1.0));
        }
        else {
            os << "+" << m_value.imag();
        }
        os  << "j)";
    }
}

bool Constant::is_constant () const { return true; }
bool Constant::is_variable () const { return false; }
bool Constant::is_operation () const {return false; }

} // namespace zcalc