#pragma once

#include "zcalc/expression/constant.hpp"
#include "zcalc/expression/variable_pool.hpp"

#include <complex>
#include <string>
#include <variant>

namespace zcalc {

class Term {
private:
    std::variant<Constant, std::string> m_content;
public:
    Term () : m_content(Constant{}) {}
    Term (complex value) : m_content(Constant{value}) {}
    Term (const std::string& var) : m_content(var) {
        if (!VariablePool::var_exists(var)) {
            VariablePool::define_variable(var);
        }
    }

    bool is_numeric () {
        if (std::holds_alternative<Constant>(m_content)) {
            return true;
        }
        else if (std::holds_alternative<std::string>(m_content)) {
            return VariablePool::is_var_known(std::get<std::string>(m_content));
        }
        throw std::runtime_error("ERROR : this is a bug, not a feature");
    }
    
    complex get ();
    void reduce ();
    bool is_zero ();
    bool is_one ();
    std::string to_string() const;
};

} // namespace zcalc