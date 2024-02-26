#include "zcalc/expression/variable.hpp"

#include <map>
#include <string>

namespace zcalc {

bool Variable::is_numeric () const { return m_known; }

void Variable::reduce () { return; }

bool Variable::is_zero () const {
    if (!m_known) throw std::runtime_error("ERROR : variable value is unknown");
    return std::abs(m_value) < epsilon;
}

bool Variable::is_one () const {
    if (!m_known) throw std::runtime_error("ERROR : variable value is unknown");
    return ((std::abs(m_value.real() - 1.0)) < epsilon) && (std::abs(m_value.imag()) < epsilon);
}

complex Variable::get () const {
    if (!m_known) throw std::runtime_error("ERROR : variable value is unknown");
    return m_value;
}

void Variable::set_value (complex value) {
    m_value = value;
    m_known = true;
}

void Variable::unset_value () {
    m_value = complex { 0.0, 0.0 };
    m_known = false;
}

void Variable::print (std::ostream &os) const {
    os << m_id;
}

bool Variable::is_constant () const { return false; }
bool Variable::is_variable () const { return true; }
bool Variable::is_operation () const {return false; }

} // namespace zcalc