#pragma once

#include <cstdint>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <memory>
#include <exception>

#include <include/complex.hpp>

namespace zcalc {

class ExpUnit {
public:
    virtual ~ExpUnit() {};

    virtual bool is_numeric () = 0;
    virtual void reduce () = 0;
    virtual Complex get () = 0;
    virtual std::string to_string() const = 0;
};

class Constant : public ExpUnit {
private:
    Complex m_value;
public:
    ~Constant() = default;
    Constant (Complex value);
    bool is_numeric () override;
    void reduce () override;
    Complex get () override;
    std::string to_string() const override;
};

class Variable : public ExpUnit {
private:
    std::string m_id;
    bool m_value_known = false;
    Complex m_value;
public:
    ~Variable() = default;
    Variable (const std::string& id);
    bool is_numeric () override;
    void reduce () override;
    Complex get () override;
    std::string to_string() const override;
    void set_value (Complex value);
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
    bool is_numeric () override;
    void reduce () override;
    Complex get () override;
    void set_left_operand (std::shared_ptr<ExpUnit> operand);
    void set_right_operand (std::shared_ptr<ExpUnit> operand);
    std::string to_string() const override;
};

class Expression {
private:
    std::shared_ptr<ExpUnit> m_exp_root = nullptr;
public:
    Expression (std::shared_ptr<ExpUnit> exp_root);
    Expression (Complex constant_value);
    Expression ();
    ~Expression () = default;
    void print ();
    bool has_value () const;
    bool is_zero () const;
    Complex evaluate () const;
    void reduce ();

    Expression operator+(const Expression& exp) const;
    Expression operator+(Complex constant_value) const;
    Expression operator+(std::shared_ptr<Variable> var) const;

    Expression& operator+=(const Expression& rhs);
    Expression& operator+=(Complex constant_value);
    Expression& operator+=(std::shared_ptr<Variable> var);

    Expression operator-(const Expression& rhs) const;
    Expression operator-(Complex constant_value) const;
    Expression operator-(std::shared_ptr<Variable> var) const;

    Expression& operator-=(const Expression& rhs);
    Expression& operator-=(Complex constant_value);
    Expression& operator-=(std::shared_ptr<Variable> var);

    Expression operator*(const Expression& rhs) const;
    Expression operator*(Complex constant_value) const;
    Expression operator*(std::shared_ptr<Variable> var) const;

    Expression& operator*=(const Expression& rhs);
    Expression& operator*=(Complex constant_value);
    Expression& operator*=(std::shared_ptr<Variable> var);

    Expression operator/(const Expression& rhs) const;
    Expression operator/(Complex constant_value) const;
    Expression operator/(std::shared_ptr<Variable> var) const;

    Expression& operator/=(const Expression& rhs);
    Expression& operator/=(Complex constant_value);
    Expression& operator/=(std::shared_ptr<Variable> var);

    friend bool operator!=(const Expression& exp_0, const Expression& exp_1);
    friend bool operator==(const Expression& exp_0, const Expression& exp_1);

    friend std::ostream& operator<<(std::ostream& os, const Expression& exp);
};

class Equation {
private:
    std::shared_ptr<Expression> m_lhs = nullptr;
    std::shared_ptr<Expression> m_rhs = nullptr;
    /* TODO if needed */
};

} /* namespace zcalc */