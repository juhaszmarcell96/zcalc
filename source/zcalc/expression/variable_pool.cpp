#include "zcalc/expression/variable_pool.hpp"

namespace zcalc {

void VariablePool::define_variable (const std::string& var_name) {
    if (m_vars.count(var_name) == 0) {
        m_vars[var_name] = std::make_shared<Variable>(var_name);
    }
}

std::shared_ptr<Variable> VariablePool::get_variable (const std::string& var_name) {
    if (m_vars.count(var_name) == 0) {
        throw std::runtime_error("ERROR : variable does not exist");
    }
    return m_vars[var_name];
}

void VariablePool::set_variable (const std::string& var_name, complex value) {
    if (m_vars.count(var_name) == 0) {
        throw std::runtime_error("ERROR : variable does not exist");
    }
    m_vars[var_name]->set_value(value);
}

void VariablePool::unset_variable (const std::string& var_name) {
    if (m_vars.count(var_name) == 0) {
        throw std::runtime_error("ERROR : variable does not exist");
    }
    m_vars[var_name]->unset_value();
}

} // namespace zcalc