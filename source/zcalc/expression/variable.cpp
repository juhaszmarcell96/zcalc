#include "zcalc/expression/variable.hpp"
#include "zcalc/expression/variable_pool.hpp"

#include <map>
#include <string>
#include <iomanip>

namespace zcalc {

term_types Variable::get_type () const { return term_types::variable; }

Variable::Variable (const std::string& name, complex coeff) : m_name(name), m_coeff(coeff) {
    VariablePool::define_variable(name);
}

bool Variable::is_numeric () const { return VariablePool::is_known(m_name); }

void Variable::simplify () { return; }

bool Variable::is_zero () const { return std::abs(VariablePool::get_value(m_name)) < epsilon; }

bool Variable::is_one () const {
    complex value = VariablePool::get_value(m_name);
    return ((std::abs(value.real() - 1.0)) < epsilon) && (std::abs(value.imag()) < epsilon);
}

complex Variable::get_value () const { return VariablePool::get_value(m_name); }

void Variable::set_value (complex value) {
    VariablePool::set_variable(m_name, value);
}

void Variable::unset_value () {
    VariablePool::unset_variable(m_name);
}

void Variable::print (std::ostream &os) const {
    if (std::abs(m_coeff.imag()) < epsilon) {
        if (!((std::abs(m_coeff.real() - 1.0)) < epsilon)) {
            os << std::setprecision(4) << m_coeff.real();
        }
    }
    else {
        os << "(" << std::setprecision(4) << m_coeff.real();
        if (m_coeff.imag() < 0.0) {
            os << "-" << (m_coeff.imag() * (-1.0));
        }
        else {
            os << "+" << m_coeff.imag();
        }
        os  << "j)";
    }
    //os << "(" << std::setprecision(4) << m_coeff.real() << "," << m_coeff.imag() << ")";
    os << m_name;
}

const std::string& Variable::get_name () const { return m_name; }
complex Variable::get_coefficient () const { return m_coeff; }
void Variable::set_coefficient (complex coeff) { m_coeff = coeff; }

bool Variable::is_constant () const { return false; }
bool Variable::is_variable () const { return true; }
bool Variable::is_operation () const {return false; }

} // namespace zcalc