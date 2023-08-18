#pragma once


#include <iostream>
#include <vector>
#include <cmath>
#include <map>
#include <string>
#include <memory>
#include <complex>

typedef std::complex<double> complex;
constexpr double epsilon = 1.0e-10;

class Term {
public:
    virtual ~Term() {};

    virtual bool is_numeric () = 0;
    virtual void reduce () = 0;
    virtual complex get () = 0;
    virtual bool is_zero () = 0;
    virtual bool is_one () = 0;
    virtual std::string to_string() const = 0;
};

class Constant : public Term {
private:
    complex m_value { 0.0, 0.0 };
public:
    Constant () = delete;
    ~Constant() = default;
    Constant (complex value) : m_value(value) {}
    bool is_numeric () override { return true; }
    void reduce () override { return; }
    complex get () override { return m_value; }
    bool is_zero () override { return std::abs(m_value) < epsilon; }
    bool is_one () override {
        return ((std::abs(m_value.real() - 1.0)) < epsilon) && (std::abs(m_value.imag()) < epsilon);
    }
    std::string to_string() const override {
        std::string str = "(";
        str += std::to_string(m_value.real());
        str += ",";
        str += std::to_string(m_value.imag());
        str += ")";
        return str;
    }
};

class Variable : public Term {
private:
    std::string m_id;
    bool m_known { false };
    complex m_value { 0.0, 0.0 };
public:
    Variable() = delete;
    ~Variable() = default;
    Variable (const std::string& id) : m_id(id) {}
    bool is_numeric () override { return m_known; }
    void reduce () override { return; }
    bool is_zero () override {
        if (!m_known) throw std::runtime_error("ERROR : variable value is unknown");
        return std::abs(m_value) < epsilon;
    }
    bool is_one () override {
        if (!m_known) throw std::runtime_error("ERROR : variable value is unknown");
        return ((std::abs(m_value.real() - 1.0)) < epsilon) && (std::abs(m_value.imag()) < epsilon);
    }
    complex get () override{
        if (!m_known) throw std::runtime_error("ERROR : variable value is unknown");
        return m_value;
    }
    std::string to_string() const override { return m_id; }
    void set_value (complex value) {
        m_value = value;
        m_known = true;
    }
};

enum class operation_type {
    add,
    sub,
    mul,
    div
};

class Operation : public Term {
private:
    std::shared_ptr<Term> m_left_operand { nullptr };
    std::shared_ptr<Term> m_right_operand { nullptr };

    operation_type m_type;
public:
    Operation () = delete;
    Operation (operation_type type) : m_type (type) {}
    ~Operation () = default;
    bool is_numeric () override {
        if (m_left_operand == nullptr) return false;
        if (m_right_operand == nullptr) return false;
        if (!m_left_operand->is_numeric()) return false;
        if (!m_right_operand->is_numeric()) return false;
        return true;
    }
    void reduce () override {
        if (m_left_operand->is_numeric()) {
            m_left_operand = std::make_shared<Constant>(m_left_operand->get());
        }
        else {
            m_left_operand->reduce();
        }
        if (m_right_operand->is_numeric()) {
            m_right_operand = std::make_shared<Constant>(m_right_operand->get());
        }
        else {
            m_right_operand->reduce();
        }
        return;
    }
    bool is_zero () override {
        return std::abs(get()) < epsilon;
    }
    bool is_one () override {
        return ((std::abs(get().real() - 1.0)) < epsilon) && (std::abs(get().imag()) < epsilon);
    }
    complex get () override {
        if (m_left_operand == nullptr) throw std::runtime_error("ERROR : operand cannot be null");
        if (m_right_operand == nullptr) throw std::runtime_error("ERROR : operand cannot be null");
        switch(m_type) {
            case operation_type::add : {
                return m_left_operand->get() + m_right_operand->get();
            }
            case operation_type::sub : {
                return m_left_operand->get() - m_right_operand->get();
            }
            case operation_type::mul : {
                return m_left_operand->get() * m_right_operand->get();
            }
            case operation_type::div : {
                return m_left_operand->get() / m_right_operand->get(); /* TODO -> check if it is 0, math error */
            }
            default : {
                throw std::runtime_error("ERROR : invalid operator type");
            }
        }
    }
    void set_left_operand (std::shared_ptr<Term> operand) {
        m_left_operand = operand;
    }
    void set_right_operand (std::shared_ptr<Term> operand) {
        m_right_operand = operand;
    }
    std::string to_string() const override {
        if (m_left_operand == nullptr) throw std::runtime_error("ERROR : operand cannot be null");
        if (m_right_operand == nullptr) throw std::runtime_error("ERROR : operand cannot be null");
        std::string str = "(";
        str += m_left_operand->to_string();
        switch(m_type) {
            case operation_type::add : {
                str += "+";
                break;
            }
            case operation_type::sub : {
                str += "-";
                break;
            }
            case operation_type::mul : {
                str += "*";
                break;
            }
            case operation_type::div : {
                str += "/";
                break;
            }
            default : {
                throw std::runtime_error("ERROR : invalid operator type");
            }
        }
        str += m_right_operand->to_string();
        str += ")";
        return str;
    }
};

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