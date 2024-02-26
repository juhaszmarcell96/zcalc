#pragma once

#include "zcalc/equation/term.hpp"

#include <iostream>
#include <vector>
#include <cmath>
#include <map>
#include <string>
#include <memory>





class Equation {
private:
    std::shared_ptr<Expression> m_lhs = nullptr;
    std::shared_ptr<Expression> m_rhs = nullptr;
    /* TODO if needed */
};

class LinearEquation {
private:
    struct Variable {
        double coeff { 0.0 };
        double value { 0.0 };
        bool known { false };
    };
    std::map<std::string, Variable> m_variables;
    double m_eq { 0.0 };
public:
    void add_variable (const std::string& var_name) {
        m_variables[var_name] = Variable {};
    }

    void set_coeff (const std::string& var_name, double coeff) {
        m_variables[var_name].coeff = coeff;
    }

    void set_eq (double eq) {
        m_eq = eq;
    }

    bool solve_for (const std::string& var_name) {
        return true;
    }

    double get_value (const std::string& var_name) {
        /* TODO : if known */
        return m_variables[var_name].value;
    }
};