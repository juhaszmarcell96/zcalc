#pragma once

#include "zcalc/expression/variable.hpp"

#include <memory>
#include <string>
#include <map>

namespace zcalc {

class VariablePool {
private:
    static inline std::map<std::string, std::shared_ptr<Variable>> m_vars;
public:
    static void define_variable (const std::string& var_name);
    static void undefine_variable (const std::string& var_name);
    static std::shared_ptr<Variable> get_variable (const std::string& var_name);
    static void set_variable (const std::string& var_name, complex value);
    static void unset_variable (const std::string& var_name);
};

} // namespace zcalc