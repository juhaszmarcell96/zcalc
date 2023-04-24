#include <include/expression.hpp>


namespace zcalc {

Constant::Constant (std::complex<double> value) : m_value(value) {}
bool Constant::is_numeric () {
    return true;
}
std::complex<double> Constant::get () {
    return m_value;
}
std::string Constant::to_string() const {
    std::string str = "(";
    str += std::to_string(m_value.real());
    str += ",";
    str += std::to_string(m_value.imag());
    str += ")";
    return str;
}



Variable::Variable (const std::string& id) : m_id(id) {}
bool Variable::is_numeric () {
    return m_value_known;
}
std::complex<double> Variable::get () {
    if (!m_value_known) throw std::domain_error("ERROR : variable value is unknown");
    return m_value;
}
std::string Variable::to_string() const { return m_id; }
void Variable::set_value (std::complex<double> value) {
    m_value = value;
    m_value_known = true;
}



Operation::Operation (operation_type type) : m_type (type) {}
bool Operation::is_numeric () {
    if (m_left_operand == nullptr) return false;
    if (m_right_operand == nullptr) return false;
    if (!m_left_operand->is_numeric()) return false;
    if (!m_right_operand->is_numeric()) return false;
    return true;
}
std::complex<double> Operation::get () {
    if (m_left_operand == nullptr) throw std::domain_error("ERROR : operand cannot be null");
    if (m_right_operand == nullptr) throw std::domain_error("ERROR : operand cannot be null");
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
            throw std::domain_error("ERROR : invalid operator type");
        }
    }
}
void Operation::set_left_operand (std::shared_ptr<ExpUnit> operand) {
    m_left_operand = operand;
}
void Operation::set_right_operand (std::shared_ptr<ExpUnit> operand) {
    m_right_operand = operand;
}
std::string Operation::to_string() const {
    if (m_left_operand == nullptr) throw std::domain_error("ERROR : operand cannot be null");
    if (m_right_operand == nullptr) throw std::domain_error("ERROR : operand cannot be null");
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
            throw std::domain_error("ERROR : invalid operator type");
        }
    }
    str += m_right_operand->to_string();
    str += ")";
    return str;
}



Expression::Expression (std::shared_ptr<ExpUnit> exp_root) : m_exp_root(exp_root) {}
Expression::Expression (std::complex<double> constant_value) {
    m_exp_root = std::make_shared<Constant>(constant_value);
}
Expression::Expression () {
    m_exp_root = std::make_shared<Constant>(std::complex<double>{ 0.0, 0.0 });
}
void Expression::print () {
    if (m_exp_root == nullptr) throw std::domain_error("ERROR : root cannot be null");
    std::cout << m_exp_root->to_string() << std::endl;
}

std::ostream& operator<<(std::ostream& os, const Expression& exp) {
    os << exp.m_exp_root->to_string();
    return os;
}

bool Expression::has_value () const {
    if (m_exp_root == nullptr) return false;
    return m_exp_root->is_numeric();
}

bool Expression::is_zero () const {
    if (!has_value()) return false;
    return evaluate() == std::complex<double> { 0.0, 0.0 };
}

std::complex<double> Expression::evaluate () const {
    if (m_exp_root == nullptr) throw std::domain_error("ERROR : root cannot be null");
    return m_exp_root->get();
}

Expression Expression::operator+(const Expression& exp) const {
    std::shared_ptr<Operation> add_op = std::make_shared<Operation>(operation_type::add);
    add_op->set_left_operand(m_exp_root);
    add_op->set_right_operand(exp.m_exp_root);
    Expression new_exp {add_op};
    return std::move(new_exp);
}
Expression Expression::operator+(std::complex<double> constant_value) const {
    std::shared_ptr<Operation> add_op = std::make_shared<Operation>(operation_type::add);
    std::shared_ptr<Constant> const_val = std::make_shared<Constant>(constant_value);
    add_op->set_left_operand(m_exp_root);
    add_op->set_right_operand(const_val);
    Expression new_exp {add_op};
    return std::move(new_exp);
}
Expression Expression::operator+(std::shared_ptr<Variable> var) const {
    std::shared_ptr<Operation> add_op = std::make_shared<Operation>(operation_type::add);
    add_op->set_left_operand(m_exp_root);
    add_op->set_right_operand(var);
    Expression new_exp {add_op};
    return std::move(new_exp);
}

Expression& Expression::operator+=(const Expression& rhs) {
    std::shared_ptr<Operation> add_op = std::make_shared<Operation>(operation_type::add);
    add_op->set_left_operand(m_exp_root);
    add_op->set_right_operand(rhs.m_exp_root);
    m_exp_root = add_op;
    return *this;
}
Expression& Expression::operator+=(std::complex<double> constant_value) {
    std::shared_ptr<Operation> add_op = std::make_shared<Operation>(operation_type::add);
    std::shared_ptr<Constant> const_val = std::make_shared<Constant>(constant_value);
    add_op->set_left_operand(m_exp_root);
    add_op->set_right_operand(const_val);
    m_exp_root = add_op;
    return *this;
}
Expression& Expression::operator+=(std::shared_ptr<Variable> var) {
    std::shared_ptr<Operation> add_op = std::make_shared<Operation>(operation_type::add);
    add_op->set_left_operand(m_exp_root);
    add_op->set_right_operand(var);
    m_exp_root = add_op;
    return *this;
}

Expression Expression::operator-(const Expression& rhs) const {
    std::shared_ptr<Operation> sub_op = std::make_shared<Operation>(operation_type::sub);
    sub_op->set_left_operand(m_exp_root);
    sub_op->set_right_operand(rhs.m_exp_root);
    Expression new_exp {sub_op};
    return std::move(new_exp);
}
Expression Expression::operator-(std::complex<double> constant_value) const {
    std::shared_ptr<Operation> sub_op = std::make_shared<Operation>(operation_type::sub);
    std::shared_ptr<Constant> const_val = std::make_shared<Constant>(constant_value);
    sub_op->set_left_operand(m_exp_root);
    sub_op->set_right_operand(const_val);
    Expression new_exp {sub_op};
    return std::move(new_exp);
}
Expression Expression::operator-(std::shared_ptr<Variable> var) const {
    std::shared_ptr<Operation> sub_op = std::make_shared<Operation>(operation_type::sub);
    sub_op->set_left_operand(m_exp_root);
    sub_op->set_right_operand(var);
    Expression new_exp {sub_op};
    return std::move(new_exp);
}

Expression& Expression::operator-=(const Expression& rhs) {
    std::shared_ptr<Operation> sub_op = std::make_shared<Operation>(operation_type::sub);
    sub_op->set_left_operand(m_exp_root);
    sub_op->set_right_operand(rhs.m_exp_root);
    m_exp_root = sub_op;
    return *this;
}
Expression& Expression::operator-=(std::complex<double> constant_value) {
    std::shared_ptr<Operation> sub_op = std::make_shared<Operation>(operation_type::sub);
    std::shared_ptr<Constant> const_val = std::make_shared<Constant>(constant_value);
    sub_op->set_left_operand(m_exp_root);
    sub_op->set_right_operand(const_val);
    m_exp_root = sub_op;
    return *this;
}
Expression& Expression::operator-=(std::shared_ptr<Variable> var) {
    std::shared_ptr<Operation> sub_op = std::make_shared<Operation>(operation_type::sub);
    sub_op->set_left_operand(m_exp_root);
    sub_op->set_right_operand(var);
    m_exp_root = sub_op;
    return *this;
}

Expression Expression::operator*(const Expression& rhs) const {
    std::shared_ptr<Operation> mul_op = std::make_shared<Operation>(operation_type::mul);
    mul_op->set_left_operand(m_exp_root);
    mul_op->set_right_operand(rhs.m_exp_root);
    Expression new_exp {mul_op};
    return std::move(new_exp);
}
Expression Expression::operator*(std::complex<double> constant_value) const {
    std::shared_ptr<Operation> mul_op = std::make_shared<Operation>(operation_type::mul);
    std::shared_ptr<Constant> const_val = std::make_shared<Constant>(constant_value);
    mul_op->set_left_operand(m_exp_root);
    mul_op->set_right_operand(const_val);
    Expression new_exp {mul_op};
    return std::move(new_exp);
}
Expression Expression::operator*(std::shared_ptr<Variable> var) const {
    std::shared_ptr<Operation> mul_op = std::make_shared<Operation>(operation_type::mul);
    mul_op->set_left_operand(m_exp_root);
    mul_op->set_right_operand(var);
    Expression new_exp {mul_op};
    return std::move(new_exp);
}

Expression& Expression::operator*=(const Expression& rhs) {
    std::shared_ptr<Operation> mul_op = std::make_shared<Operation>(operation_type::mul);
    mul_op->set_left_operand(m_exp_root);
    mul_op->set_right_operand(rhs.m_exp_root);
    m_exp_root = mul_op;
    return *this;
}
Expression& Expression::operator*=(std::complex<double> constant_value) {
    std::shared_ptr<Operation> mul_op = std::make_shared<Operation>(operation_type::mul);
    std::shared_ptr<Constant> const_val = std::make_shared<Constant>(constant_value);
    mul_op->set_left_operand(m_exp_root);
    mul_op->set_right_operand(const_val);
    m_exp_root = mul_op;
    return *this;
}
Expression& Expression::operator*=(std::shared_ptr<Variable> var) {
    std::shared_ptr<Operation> mul_op = std::make_shared<Operation>(operation_type::mul);
    mul_op->set_left_operand(m_exp_root);
    mul_op->set_right_operand(var);
    m_exp_root = mul_op;
    return *this;
}

Expression Expression::operator/(const Expression& rhs) const {
    std::shared_ptr<Operation> div_op = std::make_shared<Operation>(operation_type::div);
    div_op->set_left_operand(m_exp_root);
    div_op->set_right_operand(rhs.m_exp_root);
    Expression new_exp {div_op};
    return std::move(new_exp);
}
Expression Expression::operator/(std::complex<double> constant_value) const {
    std::shared_ptr<Operation> div_op = std::make_shared<Operation>(operation_type::div);
    std::shared_ptr<Constant> const_val = std::make_shared<Constant>(constant_value);
    div_op->set_left_operand(m_exp_root);
    div_op->set_right_operand(const_val);
    Expression new_exp {div_op};
    return std::move(new_exp);
}
Expression Expression::operator/(std::shared_ptr<Variable> var) const {
    std::shared_ptr<Operation> div_op = std::make_shared<Operation>(operation_type::div);
    div_op->set_left_operand(m_exp_root);
    div_op->set_right_operand(var);
    Expression new_exp {div_op};
    return std::move(new_exp);
}

Expression& Expression::operator/=(const Expression& rhs) {
    std::shared_ptr<Operation> div_op = std::make_shared<Operation>(operation_type::div);
    div_op->set_left_operand(m_exp_root);
    div_op->set_right_operand(rhs.m_exp_root);
    m_exp_root = div_op;
    return *this;
}
Expression& Expression::operator/=(std::complex<double> constant_value) {
    std::shared_ptr<Operation> div_op = std::make_shared<Operation>(operation_type::div);
    std::shared_ptr<Constant> const_val = std::make_shared<Constant>(constant_value);
    div_op->set_left_operand(m_exp_root);
    div_op->set_right_operand(const_val);
    m_exp_root = div_op;
    return *this;
}
Expression& Expression::operator/=(std::shared_ptr<Variable> var) {
    std::shared_ptr<Operation> div_op = std::make_shared<Operation>(operation_type::div);
    div_op->set_left_operand(m_exp_root);
    div_op->set_right_operand(var);
    m_exp_root = div_op;
    return *this;
}

bool operator!=(const Expression& exp_0, const Expression& exp_1) {
    return exp_0.m_exp_root != exp_1.m_exp_root;
}

bool operator==(const Expression& exp_0, const Expression& exp_1) {
    return exp_0.m_exp_root == exp_1.m_exp_root;
}

} /* namespace zcalc */