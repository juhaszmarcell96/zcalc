#include "zcalc/expression/operation.hpp"
#include "zcalc/expression/constant.hpp"

#include <memory>

namespace zcalc {

bool Operation::is_numeric () {
    if (m_left_operand == nullptr) return false;
    if (m_right_operand == nullptr) return false;
    if (!m_left_operand->is_numeric()) return false;
    if (!m_right_operand->is_numeric()) return false;
    return true;
}

void Operation::reduce () {
    if (m_left_operand == nullptr) { throw std::runtime_error("ERROR : left operand is null"); }
    if (m_right_operand == nullptr) { throw std::runtime_error("ERROR : right operand is null"); }

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
bool Operation::is_zero () {
    return std::abs(get()) < epsilon;
}

bool Operation::is_one () {
    return ((std::abs(get().real() - 1.0)) < epsilon) && (std::abs(get().imag()) < epsilon);
}

complex Operation::get () {
    if (m_left_operand == nullptr) { throw std::runtime_error("ERROR : operand cannot be null"); }
    if (m_right_operand == nullptr) { throw std::runtime_error("ERROR : operand cannot be null"); }
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

void Operation::set_left_operand (std::shared_ptr<Term> operand) {
    m_left_operand = operand;
}

void Operation::set_right_operand (std::shared_ptr<Term> operand) {
    m_right_operand = operand;
}

void Operation::print (std::ostream &os) {
    if (m_left_operand == nullptr) { throw std::runtime_error("ERROR : operand cannot be null"); }
    if (m_right_operand == nullptr) { throw std::runtime_error("ERROR : operand cannot be null"); }
    os << "(";
    m_left_operand->print(os);
    switch(m_type) {
        case operation_type::add : { os << "+"; break; }
        case operation_type::sub : { os << "-"; break; }
        case operation_type::mul : { os << "*"; break; }
        case operation_type::div : { os << "/"; break; }
        default : {
            throw std::runtime_error("ERROR : invalid operator type");
        }
    }
    m_right_operand->print(os);
    os << ")";
}

} // namespace zcalc