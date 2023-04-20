#pragma once

#include <cstdint>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <memory>
#include <complex>
#include <numbers>
#include <exception>

namespace zcalc {

class ExpUnit {
public:
    virtual ~ExpUnit() {};

    virtual std::complex<double> get () = 0;
    virtual void print() const = 0;
};

class Constant : public ExpUnit {
private:
    std::complex<double> m_value;
public:
    ~Constant() = default;
    Constant (std::complex<double> value);
    std::complex<double> get () override;
    void print() const override;
};

class Variable : public ExpUnit {
private:
    std::string m_id;
    bool m_value_known = false;
    std::complex<double> m_value;
public:
    ~Variable() = default;
    Variable (const std::string& id);
    std::complex<double> get () override;
    void print() const override;
    void set_value (std::complex<double> value);
};

enum class operation_type {
    add,
    sub,
    mul,
    div
};

class Operation : public ExpUnit {
private:
    std::shared_ptr<ExpUnit> m_left_operand = nullptr;
    std::shared_ptr<ExpUnit> m_right_operand = nullptr;

    operation_type m_type;
public:
    Operation () = delete;
    Operation (operation_type type);
    ~Operation () = default;
    std::complex<double> get () override;
    void set_left_operand (std::shared_ptr<ExpUnit> operand);
    void set_right_operand (std::shared_ptr<ExpUnit> operand);
    void print() const override;
};

class Expression {
private:
    std::shared_ptr<ExpUnit> m_exp_root = nullptr;
public:
    Expression () = delete;
    Expression (std::shared_ptr<ExpUnit> exp_root);
    Expression (std::complex<double> constant_value);
    void print ();
    std::complex<double> evaluate ();

    Expression operator+(const Expression& exp) const;
    Expression operator+(std::complex<double> constant_value) const;
    Expression operator+(std::shared_ptr<Variable> var) const;

    Expression& operator+=(const Expression& rhs);
    Expression& operator+=(std::complex<double> constant_value);
    Expression& operator+=(std::shared_ptr<Variable> var);

    Expression operator-(const Expression& rhs);
    Expression operator-(std::complex<double> constant_value);
    Expression operator-(std::shared_ptr<Variable> var);

    Expression& operator-=(const Expression& rhs);
    Expression& operator-=(std::complex<double> constant_value);
    Expression& operator-=(std::shared_ptr<Variable> var);

    Expression operator*(const Expression& rhs);
    Expression operator*(std::complex<double> constant_value);
    Expression operator*(std::shared_ptr<Variable> var);

    Expression& operator*=(const Expression& rhs);
    Expression& operator*=(std::complex<double> constant_value);
    Expression& operator*=(std::shared_ptr<Variable> var);

    Expression operator/(const Expression& rhs);
    Expression operator/(std::complex<double> constant_value);
    Expression operator/(std::shared_ptr<Variable> var);

    Expression& operator/=(const Expression& rhs);
    Expression& operator/=(std::complex<double> constant_value);
    Expression& operator/=(std::shared_ptr<Variable> var);
};

class Equation {
private:
    std::shared_ptr<Expression> m_lhs = nullptr;
    std::shared_ptr<Expression> m_rhs = nullptr;
    /* TODO if needed */
};

} /* namespace zcalc */