#include "zcalc/expression/variable.hpp"
#include "zcalc/expression/variable_pool.hpp"

#include <map>
#include <string>

namespace zcalc {

term_types Variable::get_type () const { return term_types::variable; }

Variable::Variable (const std::string& name) : m_name(name) {
    VariablePool::define_variable(name);
}

bool Variable::is_numeric () const { return VariablePool::is_known(m_name); }

void Variable::reduce () { return; }

bool Variable::is_zero () const { return std::abs(VariablePool::get_value(m_name)) < epsilon; }

bool Variable::is_one () const {
    complex value = VariablePool::get_value(m_name);
    return ((std::abs(value.real() - 1.0)) < epsilon) && (std::abs(value.imag()) < epsilon);
}

complex Variable::get () const { return VariablePool::get_value(m_name); }

void Variable::set_value (complex value) {
    VariablePool::set_variable(m_name, value);
}

void Variable::unset_value () {
    VariablePool::unset_variable(m_name);
}

void Variable::print (std::ostream &os) const {
    os << m_name;
}

bool Variable::is_constant () const { return false; }
bool Variable::is_variable () const { return true; }
bool Variable::is_operation () const {return false; }

std::unique_ptr<Term> Variable::create_copy () const {
    return std::make_unique<Variable>(m_name);
}

} // namespace zcalc