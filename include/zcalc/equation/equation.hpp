#pragma once

#include "zcalc/equation/term.hpp"

#include <iostream>
#include <vector>
#include <cmath>
#include <map>
#include <string>
#include <memory>

class TermFactory {
public:
    static std::shared_ptr<Term> create (complex value) {
        return std::make_shared<Constant>(value);
    }

    static std::shared_ptr<Term> create (operation_type type, std::shared_ptr<Term> lhs, std::shared_ptr<Term> rhs) {
        switch(type) {
            case operation_type::add : {
                if (lhs->is_numeric() && rhs->is_numeric()) {
                    return std::make_shared<Constant>(lhs->get() + rhs->get());
                }
                else if (lhs->is_numeric()) {
                    if (lhs->is_zero()) {
                        return rhs;
                    }
                }
                else if (rhs->is_numeric()) {
                    if (rhs->is_zero()) {
                        return lhs;
                    }
                }
                std::shared_ptr<Operation> new_op = std::make_shared<Operation>(operation_type::add);
                new_op->set_left_operand(lhs);
                new_op->set_right_operand(rhs);
                new_op->reduce();
                return new_op;
            }
            case operation_type::sub : {
                if (lhs->is_numeric() && rhs->is_numeric()) {
                    return std::make_shared<Constant>(lhs->get() - rhs->get());
                }
                else if (lhs->is_numeric()) {
                    if (lhs->is_zero()) {
                        return rhs;
                    }
                }
                else if (rhs->is_numeric()) {
                    if (rhs->is_zero()) {
                        return lhs;
                    }
                }
                std::shared_ptr<Operation> new_op = std::make_shared<Operation>(operation_type::sub);
                new_op->set_left_operand(lhs);
                new_op->set_right_operand(rhs);
                new_op->reduce();
                return new_op;
            }
            case operation_type::mul : {
                if (lhs->is_numeric() && rhs->is_numeric()) {
                    return std::make_shared<Constant>(lhs->get() * rhs->get());
                }
                else if (lhs->is_numeric()) {
                    if (lhs->is_zero()) {
                        return std::make_shared<Constant>(complex{0.0, 0.0});
                    }
                    else if (lhs->is_one()) {
                        return rhs;
                    }
                }
                else if (rhs->is_numeric()) {
                    if (rhs->is_zero()) {
                        return std::make_shared<Constant>(complex{0.0, 0.0});
                    }
                    else if (rhs->is_one()) {
                        return lhs;
                    }
                }
                std::shared_ptr<Operation> new_op = std::make_shared<Operation>(operation_type::mul);
                new_op->set_left_operand(lhs);
                new_op->set_right_operand(rhs);
                new_op->reduce();
                return new_op;
            }
            case operation_type::div : {
                if (lhs->is_numeric() && rhs->is_numeric()) {
                    return std::make_shared<Constant>(lhs->get() / rhs->get());
                }
                else if (lhs->is_numeric()) {
                    if (lhs->is_zero()) {
                        return std::make_shared<Constant>(complex{0.0, 0.0});
                    }
                }
                else if (rhs->is_numeric()) {
                    if (rhs->is_zero()) {
                        throw std::runtime_error("ERROR : cannot divide by 0");
                    }
                    else if (rhs->is_one()) {
                        return lhs;
                    }
                }
                std::shared_ptr<Operation> new_op = std::make_shared<Operation>(operation_type::div);
                new_op->set_left_operand(lhs);
                new_op->set_right_operand(rhs);
                new_op->reduce();
                return new_op;
            }
            default : {
                throw std::runtime_error("ERROR : invalid operator type");
            }
        }
    }
};

class Expression {
private:
    std::shared_ptr<Term> m_exp_root { nullptr };
public:
    Expression (std::shared_ptr<Term> exp_root) : m_exp_root(exp_root) {
        reduce();
    }
    Expression (complex constant_value) { m_exp_root = std::make_shared<Constant>(constant_value); }
    Expression () { m_exp_root = std::make_shared<Constant>(complex { 0.0, 0.0 }); }
    ~Expression () = default;
    void print () {
        if (m_exp_root == nullptr) throw std::runtime_error("ERROR : root cannot be null");
        std::cout << m_exp_root->to_string() << std::endl;
    }
    bool has_value () const {
        if (m_exp_root == nullptr) return false;
        return m_exp_root->is_numeric();
    }
    bool is_zero () const {
        if (!has_value()) return false;
        return evaluate() == complex { 0.0, 0.0 };
    }
    complex evaluate () const {
        if (m_exp_root == nullptr) throw std::runtime_error("ERROR : root cannot be null");
        return m_exp_root->get();
    }
    void reduce () {
        m_exp_root->reduce();
        return;
    }

    Expression operator+(const Expression& rhs) const {
        return Expression{TermFactory::create(operation_type::add, m_exp_root, rhs.m_exp_root)};
    }
    Expression operator+(complex constant_value) const {
        return Expression{TermFactory::create(operation_type::add, m_exp_root, TermFactory::create(constant_value))};
    }
    Expression operator+(std::shared_ptr<Variable> var) const {
        return Expression{TermFactory::create(operation_type::add, m_exp_root, var)};
    }

    Expression& operator+=(const Expression& rhs) {
        m_exp_root = TermFactory::create(operation_type::add, m_exp_root, rhs.m_exp_root);
        return *this;
    }
    Expression& operator+=(complex constant_value) {
        m_exp_root = TermFactory::create(operation_type::add, m_exp_root, TermFactory::create(constant_value));
        return *this;
    }
    Expression& operator+=(std::shared_ptr<Variable> var) {
        m_exp_root = TermFactory::create(operation_type::add, m_exp_root, var);
        return *this;
    }

    Expression operator-(const Expression& rhs) const {
        return Expression{TermFactory::create(operation_type::sub, m_exp_root, rhs.m_exp_root)};
    }
    Expression operator-(complex constant_value) const {
        return Expression{TermFactory::create(operation_type::sub, m_exp_root, TermFactory::create(constant_value))};
    }
    Expression operator-(std::shared_ptr<Variable> var) const {
        return Expression{TermFactory::create(operation_type::sub, m_exp_root, var)};
    }

    Expression& operator-=(const Expression& rhs) {
        m_exp_root = TermFactory::create(operation_type::sub, m_exp_root, rhs.m_exp_root);
        return *this;
    }
    Expression& operator-=(complex constant_value) {
        m_exp_root = TermFactory::create(operation_type::sub, m_exp_root, TermFactory::create(constant_value));
        return *this;
    }
    Expression& operator-=(std::shared_ptr<Variable> var) {
        m_exp_root = TermFactory::create(operation_type::sub, m_exp_root, var);
        return *this;
    }

    Expression operator*(const Expression& rhs) const {
        return Expression{TermFactory::create(operation_type::mul, m_exp_root, rhs.m_exp_root)};
    }
    Expression operator*(complex constant_value) const {
        return Expression{TermFactory::create(operation_type::mul, m_exp_root, TermFactory::create(constant_value))};
    }
    Expression operator*(std::shared_ptr<Variable> var) const {
        return Expression{TermFactory::create(operation_type::mul, m_exp_root, var)};
    }

    Expression& operator*=(const Expression& rhs) {
        m_exp_root = TermFactory::create(operation_type::mul, m_exp_root, rhs.m_exp_root);
        return *this;
    }
    Expression& operator*=(complex constant_value) {
        m_exp_root = TermFactory::create(operation_type::mul, m_exp_root, TermFactory::create(constant_value));
        return *this;
    }
    Expression& operator*=(std::shared_ptr<Variable> var) {
        m_exp_root = TermFactory::create(operation_type::mul, m_exp_root, var);
        return *this;
    }

    Expression operator/(const Expression& rhs) const {
        return Expression{TermFactory::create(operation_type::div, m_exp_root, rhs.m_exp_root)};
    }
    Expression operator/(complex constant_value) const {
        return Expression{TermFactory::create(operation_type::div, m_exp_root, TermFactory::create(constant_value))};
    }
    Expression operator/(std::shared_ptr<Variable> var) const {
        return Expression{TermFactory::create(operation_type::div, m_exp_root, var)};
    }

    Expression& operator/=(const Expression& rhs) {
        m_exp_root = TermFactory::create(operation_type::div, m_exp_root, rhs.m_exp_root);
        return *this;
    }
    Expression& operator/=(complex constant_value) {
        m_exp_root = TermFactory::create(operation_type::div, m_exp_root, TermFactory::create(constant_value));
        return *this;
    }
    Expression& operator/=(std::shared_ptr<Variable> var) {
        m_exp_root = TermFactory::create(operation_type::div, m_exp_root, var);
        return *this;
    }

    friend bool operator!=(const Expression& exp_0, const Expression& exp_1) {
        return exp_0.m_exp_root != exp_1.m_exp_root;
    }
    friend bool operator==(const Expression& exp_0, const Expression& exp_1) {
        return exp_0.m_exp_root == exp_1.m_exp_root;
    }

    friend std::ostream& operator<<(std::ostream& os, const Expression& exp) {
        os << exp.m_exp_root->to_string();
        return os;
    }
};

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