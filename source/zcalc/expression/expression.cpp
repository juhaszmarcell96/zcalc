#include "zcalc/expression/expression.hpp"
#include "zcalc/expression/operation.hpp"
#include "zcalc/expression/constant.hpp"
#include "zcalc/expression/term_factory.hpp"

namespace zcalc {

Expression::Expression (std::shared_ptr<Term> exp_root) : m_exp_root(exp_root) {
    reduce();
}
Expression::Expression (complex constant_value) { m_exp_root = TermFactory::create(constant_value); }
Expression::Expression (const std::string& var_name) { m_exp_root = TermFactory::create(var_name); }
Expression::Expression () { m_exp_root = std::make_shared<Constant>(complex { 0.0, 0.0 }); }
void Expression::print (std::ostream &os) {
    if (m_exp_root == nullptr) throw std::runtime_error("ERROR : root cannot be null");
    m_exp_root->print(os);
    os << std::endl;
}
bool Expression::has_value () const {
    if (m_exp_root == nullptr) return false;
    return m_exp_root->is_numeric();
}
bool Expression::is_zero () const {
    if (!has_value()) return false;
    return evaluate() == complex { 0.0, 0.0 };
}
complex Expression::evaluate () const {
    if (m_exp_root == nullptr) throw std::runtime_error("ERROR : root cannot be null");
    return m_exp_root->get();
}
void Expression::reduce () {
    m_exp_root->reduce();
    return;
}

Expression Expression::operator+(const Expression& rhs) const {
    return Expression{TermFactory::create(operation_type::add, m_exp_root, rhs.m_exp_root)};
}
Expression Expression::operator+(complex constant_value) const {
    return Expression{TermFactory::create(operation_type::add, m_exp_root, TermFactory::create(constant_value))};
}
Expression Expression::operator+(std::shared_ptr<Variable> var) const {
    return Expression{TermFactory::create(operation_type::add, m_exp_root, var)};
}
Expression Expression::operator+(const std::string& var_name) const {
    return Expression{TermFactory::create(operation_type::add, m_exp_root, TermFactory::create(var_name))};
}

Expression& Expression::operator+=(const Expression& rhs) {
    m_exp_root = TermFactory::create(operation_type::add, m_exp_root, rhs.m_exp_root);
    return *this;
}
Expression& Expression::operator+=(complex constant_value) {
    m_exp_root = TermFactory::create(operation_type::add, m_exp_root, TermFactory::create(constant_value));
    return *this;
}
Expression& Expression::operator+=(std::shared_ptr<Variable> var) {
    m_exp_root = TermFactory::create(operation_type::add, m_exp_root, var);
    return *this;
}
Expression& Expression::operator+=(const std::string& var_name) {
    m_exp_root = TermFactory::create(operation_type::add, m_exp_root, TermFactory::create(var_name));
    return *this;
}

Expression Expression::operator-(const Expression& rhs) const {
    return Expression{TermFactory::create(operation_type::sub, m_exp_root, rhs.m_exp_root)};
}
Expression Expression::operator-(complex constant_value) const {
    return Expression{TermFactory::create(operation_type::sub, m_exp_root, TermFactory::create(constant_value))};
}
Expression Expression::operator-(std::shared_ptr<Variable> var) const {
    return Expression{TermFactory::create(operation_type::sub, m_exp_root, var)};
}
Expression Expression::operator-(const std::string& var_name) const {
    return Expression{TermFactory::create(operation_type::sub, m_exp_root, TermFactory::create(var_name))};
}

Expression& Expression::operator-=(const Expression& rhs) {
    m_exp_root = TermFactory::create(operation_type::sub, m_exp_root, rhs.m_exp_root);
    return *this;
}
Expression& Expression::operator-=(complex constant_value) {
    m_exp_root = TermFactory::create(operation_type::sub, m_exp_root, TermFactory::create(constant_value));
    return *this;
}
Expression& Expression::operator-=(std::shared_ptr<Variable> var) {
    m_exp_root = TermFactory::create(operation_type::sub, m_exp_root, var);
    return *this;
}
Expression& Expression::operator-=(const std::string& var_name) {
    m_exp_root = TermFactory::create(operation_type::sub, m_exp_root, TermFactory::create(var_name));
    return *this;
}

Expression Expression::operator*(const Expression& rhs) const {
    return Expression{TermFactory::create(operation_type::mul, m_exp_root, rhs.m_exp_root)};
}
Expression Expression::operator*(complex constant_value) const {
    return Expression{TermFactory::create(operation_type::mul, m_exp_root, TermFactory::create(constant_value))};
}
Expression Expression::operator*(std::shared_ptr<Variable> var) const {
    return Expression{TermFactory::create(operation_type::mul, m_exp_root, var)};
}
Expression Expression::operator*(const std::string& var_name) const {
    return Expression{TermFactory::create(operation_type::mul, m_exp_root, TermFactory::create(var_name))};
}

Expression& Expression::operator*=(const Expression& rhs) {
    m_exp_root = TermFactory::create(operation_type::mul, m_exp_root, rhs.m_exp_root);
    return *this;
}
Expression& Expression::operator*=(complex constant_value) {
    m_exp_root = TermFactory::create(operation_type::mul, m_exp_root, TermFactory::create(constant_value));
    return *this;
}
Expression& Expression::operator*=(std::shared_ptr<Variable> var) {
    m_exp_root = TermFactory::create(operation_type::mul, m_exp_root, var);
    return *this;
}
Expression& Expression::operator*=(const std::string& var_name) {
    m_exp_root = TermFactory::create(operation_type::mul, m_exp_root, TermFactory::create(var_name));
    return *this;
}

Expression Expression::operator/(const Expression& rhs) const {
    return Expression{TermFactory::create(operation_type::div, m_exp_root, rhs.m_exp_root)};
}
Expression Expression::operator/(complex constant_value) const {
    return Expression{TermFactory::create(operation_type::div, m_exp_root, TermFactory::create(constant_value))};
}
Expression Expression::operator/(std::shared_ptr<Variable> var) const {
    return Expression{TermFactory::create(operation_type::div, m_exp_root, var)};
}
Expression Expression::operator/(const std::string& var_name) const {
    return Expression{TermFactory::create(operation_type::div, m_exp_root, TermFactory::create(var_name))};
}

Expression& Expression::operator/=(const Expression& rhs) {
    m_exp_root = TermFactory::create(operation_type::div, m_exp_root, rhs.m_exp_root);
    return *this;
}
Expression& Expression::operator/=(complex constant_value) {
    m_exp_root = TermFactory::create(operation_type::div, m_exp_root, TermFactory::create(constant_value));
    return *this;
}
Expression& Expression::operator/=(std::shared_ptr<Variable> var) {
    m_exp_root = TermFactory::create(operation_type::div, m_exp_root, var);
    return *this;
}
Expression& Expression::operator/=(const std::string& var_name) {
    m_exp_root = TermFactory::create(operation_type::div, m_exp_root, TermFactory::create(var_name));
    return *this;
}

bool operator!=(const Expression& exp_0, const Expression& exp_1) {
    return exp_0.m_exp_root != exp_1.m_exp_root;
}
bool operator==(const Expression& exp_0, const Expression& exp_1) {
    return exp_0.m_exp_root == exp_1.m_exp_root;
}

std::ostream& operator<<(std::ostream& os, const Expression& exp) {
    exp.m_exp_root->print(os);
    return os;
}

} // namespace zcalc