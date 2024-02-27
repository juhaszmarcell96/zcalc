#include "zcalc/expression/variable_pool.hpp"

namespace zcalc {

void VariablePool::define_variable (const std::string& var_name) {
    if (m_vars.count(var_name) == 0) {
        m_vars[var_name] = Variable {};
    }
}

void VariablePool::undefine_variable (const std::string& var_name) {
    if (m_vars.count(var_name) != 0) {
        m_vars.erase(var_name);
    }
}

complex VariablePool::get_value (const std::string& var_name) {
    if (m_vars.count(var_name) == 0) {
        throw std::runtime_error("ERROR : variable does not exist");
    }
    if (!m_vars[var_name].known) {
        throw std::runtime_error("ERROR : variable value is not known");
    }
    return m_vars[var_name].value;
}

bool VariablePool::is_known (const std::string& var_name) {
    if (m_vars.count(var_name) == 0) {
        throw std::runtime_error("ERROR : variable does not exist");
    }
    return m_vars[var_name].known;
}

void VariablePool::set_variable (const std::string& var_name, complex value) {
    if (m_vars.count(var_name) == 0) {
        throw std::runtime_error("ERROR : variable does not exist");
    }
    m_vars[var_name].value = value;
    m_vars[var_name].known = true;
}

void VariablePool::unset_variable (const std::string& var_name) {
    if (m_vars.count(var_name) == 0) {
        throw std::runtime_error("ERROR : variable does not exist");
    }
    m_vars[var_name].value = complex { 0.0, 0.0 };
    m_vars[var_name].known = false;
}

} // namespace zcalc