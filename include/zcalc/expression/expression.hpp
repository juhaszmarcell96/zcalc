#pragma once

#include "zcalc/expression/term.hpp"
#include "zcalc/expression/variable.hpp"

#include <memory>

namespace zcalc {

class Expression {
private:
    std::unique_ptr<Term> m_exp_root { nullptr };
public:
    Expression (std::unique_ptr<Term>&& exp_root);
    Expression (complex constant_value);
    Expression (const std::string& var_name); 
    Expression ();
    ~Expression () = default;
    void print (std::ostream &os);
    bool has_value () const;
    bool is_zero () const;
    complex evaluate () const;
    void reduce ();

    Expression operator+(const Expression& rhs) const;
    Expression operator+(complex constant_value) const;
    Expression operator+(std::unique_ptr<Variable> var) const;
    Expression operator+(const std::string& var_name) const;

    Expression& operator+=(const Expression& rhs);
    Expression& operator+=(complex constant_value);
    Expression& operator+=(std::unique_ptr<Variable> var);
    Expression& operator+=(const std::string& var_name);

    Expression operator-(const Expression& rhs) const;
    Expression operator-(complex constant_value) const;
    Expression operator-(std::unique_ptr<Variable> var) const;
    Expression operator-(const std::string& var_name) const;

    Expression& operator-=(const Expression& rhs);
    Expression& operator-=(complex constant_value);
    Expression& operator-=(std::unique_ptr<Variable> var);
    Expression& operator-=(const std::string& var_name);

    Expression operator*(const Expression& rhs) const;
    Expression operator*(complex constant_value) const;
    Expression operator*(std::unique_ptr<Variable> var) const;
    Expression operator*(const std::string& var_name) const;

    Expression& operator*=(const Expression& rhs);
    Expression& operator*=(complex constant_value);
    Expression& operator*=(std::unique_ptr<Variable> var);
    Expression& operator*=(const std::string& var_name);

    Expression operator/(const Expression& rhs) const;
    Expression operator/(complex constant_value) const;
    Expression operator/(std::unique_ptr<Variable> var) const;
    Expression operator/(const std::string& var_name) const;

    Expression& operator/=(const Expression& rhs);
    Expression& operator/=(complex constant_value);
    Expression& operator/=(std::unique_ptr<Variable> var);
    Expression& operator/=(const std::string& var_name);

    friend bool operator!=(const Expression& exp_0, const Expression& exp_1);
    friend bool operator==(const Expression& exp_0, const Expression& exp_1);

    friend std::ostream& operator<<(std::ostream& os, const Expression& exp);
};

} // namespace zcalc