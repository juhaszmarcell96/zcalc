#pragma once

#include <map>
#include <string>

#include "zcalc/complex.hpp"

namespace zcalc {

class VariablePool {
private:

    class Variable {
    private:
        bool m_known { false };
        complex m_value { 0.0, 0.0 };
    public:
        Variable() = default;
        ~Variable() = default;
        bool is_known () { return m_known; }
        bool is_zero () {
            if (!m_known) throw std::runtime_error("ERROR : variable value is unknown");
            return std::abs(m_value) < epsilon;
        }
        bool is_one () {
            if (!m_known) throw std::runtime_error("ERROR : variable value is unknown");
            return ((std::abs(m_value.real() - 1.0)) < epsilon) && (std::abs(m_value.imag()) < epsilon);
        }
        complex get () {
            if (!m_known) throw std::runtime_error("ERROR : variable value is unknown");
            return m_value;
        }
        void set_value (complex value) {
            m_value = value;
            m_known = true;
        }
        void unset_value () {
            m_value = complex { 0.0, 0.0 };
            m_known = false;
        }
    };

    static inline std::map<std::string, Variable> m_variables;

    static void check_var_exists (const std::string& name) {
        if (m_variables.count(name) == 0) {
            throw std::runtime_error("ERROR : variable does not exists");
        }
    }
public:
    static void define_variable (const std::string& name) {
        if (m_variables.count(name) != 0) {
            throw std::runtime_error("ERROR : variable already exists");
        }
        m_variables[name] = Variable {};
    }
    static void set_variable (const std::string& name, complex value) {
        check_var_exists(name);
        m_variables[name].set_value(value);
    }
    static void unset_variable (const std::string& name) {
        check_var_exists(name);
        m_variables[name].unset_value();
    }
    static complex get_value (const std::string& name) {
        check_var_exists(name);
        return m_variables[name].get();
    }
    static bool is_var_one (const std::string& name) {
        check_var_exists(name);
        return m_variables[name].is_one();
    }
    static bool is_var_zero (const std::string& name) {
        check_var_exists(name);
        return m_variables[name].is_zero();
    }
    static bool is_var_known (const std::string& name) {
        check_var_exists(name);
        return m_variables[name].is_known();
    }
    static bool var_exists (const std::string& name) {
        return m_variables.count(name) != 0;
    }
};

} // namespace zcalc