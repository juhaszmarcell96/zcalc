#pragma once

#include "zcalc/complex.hpp"

#include <memory>
#include <string>
#include <map>

namespace zcalc {

class VariablePool {
private:
    struct Variable {
        bool known { false };
        complex value { 0.0, 0.0 };
    };
    static inline std::map<std::string, Variable> m_vars;
public:
    static void define_variable (const std::string& var_name);
    static void undefine_variable (const std::string& var_name);
    static complex get_value (const std::string& var_name);
    static bool is_known (const std::string& var_name);
    static void set_variable (const std::string& var_name, complex value);
    static void unset_variable (const std::string& var_name);
};

} // namespace zcalc