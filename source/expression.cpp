#include <include/expression.hpp>


namespace zcalc {

Constant::Constant (std::complex<double> value) : m_value(value) {}
std::complex<double> Constant::get () {
    return m_value;
}
void Constant::print() const { std::cout << m_value; }



Variable::Variable (const std::string& id) : m_id(id) {}
std::complex<double> Variable::get () {
    if (!m_value_known) throw std::domain_error("ERROR : variable value is unknown");
    return m_value;
}
void Variable::print() const { std::cout << m_id; }
void Variable::set_value (std::complex<double> value) {
    m_value = value;
    m_value_known = true;
}



Operation::Operation (operation_type type) : m_type (type) {}
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
            return m_left_operand->get() / m_right_operand->get();
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
void Operation::print() const {
    if (m_left_operand == nullptr) throw std::domain_error("ERROR : operand cannot be null");
    if (m_right_operand == nullptr) throw std::domain_error("ERROR : operand cannot be null");
    std::cout << "(";
    m_left_operand->print();
    switch(m_type) {
        case operation_type::add : {
            std::cout << "+";
            break;
        }
        case operation_type::sub : {
            std::cout << "-";
            break;
        }
        case operation_type::mul : {
            std::cout << "*";
            break;
        }
        case operation_type::div : {
            std::cout << "/";
            break;
        }
        default : {
            throw std::domain_error("ERROR : invalid operator type");
        }
    }
    m_right_operand->print();
    std::cout << ")";
}



Expression::Expression (std::shared_ptr<ExpUnit> exp_root) : m_exp_root(exp_root) {}
Expression::Expression (std::complex<double> constant_value) {
    m_exp_root = std::make_shared<Constant>(constant_value);
}
void Expression::print () {
    if (m_exp_root == nullptr) throw std::domain_error("ERROR : root cannot be null");
    m_exp_root->print();
    std::cout << std::endl;
}
std::complex<double> Expression::evaluate () {
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

Expression Expression::operator-(const Expression& rhs) {
    std::shared_ptr<Operation> sub_op = std::make_shared<Operation>(operation_type::sub);
    sub_op->set_left_operand(m_exp_root);
    sub_op->set_right_operand(rhs.m_exp_root);
    Expression new_exp {sub_op};
    return std::move(new_exp);
}
Expression Expression::operator-(std::complex<double> constant_value) {
    std::shared_ptr<Operation> sub_op = std::make_shared<Operation>(operation_type::sub);
    std::shared_ptr<Constant> const_val = std::make_shared<Constant>(constant_value);
    sub_op->set_left_operand(m_exp_root);
    sub_op->set_right_operand(const_val);
    Expression new_exp {sub_op};
    return std::move(new_exp);
}
Expression Expression::operator-(std::shared_ptr<Variable> var) {
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

Expression Expression::operator*(const Expression& rhs) {
    std::shared_ptr<Operation> mul_op = std::make_shared<Operation>(operation_type::mul);
    mul_op->set_left_operand(m_exp_root);
    mul_op->set_right_operand(rhs.m_exp_root);
    Expression new_exp {mul_op};
    return std::move(new_exp);
}
Expression Expression::operator*(std::complex<double> constant_value) {
    std::shared_ptr<Operation> mul_op = std::make_shared<Operation>(operation_type::mul);
    std::shared_ptr<Constant> const_val = std::make_shared<Constant>(constant_value);
    mul_op->set_left_operand(m_exp_root);
    mul_op->set_right_operand(const_val);
    Expression new_exp {mul_op};
    return std::move(new_exp);
}
Expression Expression::operator*(std::shared_ptr<Variable> var) {
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

Expression Expression::operator/(const Expression& rhs) {
    std::shared_ptr<Operation> div_op = std::make_shared<Operation>(operation_type::div);
    div_op->set_left_operand(m_exp_root);
    div_op->set_right_operand(rhs.m_exp_root);
    Expression new_exp {div_op};
    return std::move(new_exp);
}
Expression Expression::operator/(std::complex<double> constant_value) {
    std::shared_ptr<Operation> div_op = std::make_shared<Operation>(operation_type::div);
    std::shared_ptr<Constant> const_val = std::make_shared<Constant>(constant_value);
    div_op->set_left_operand(m_exp_root);
    div_op->set_right_operand(const_val);
    Expression new_exp {div_op};
    return std::move(new_exp);
}
Expression Expression::operator/(std::shared_ptr<Variable> var) {
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

} /* namespace zcalc */