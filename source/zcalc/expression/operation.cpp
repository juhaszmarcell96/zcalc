#include "zcalc/expression/operation.hpp"
#include "zcalc/expression/constant.hpp"
#include "zcalc/expression/term_factory.hpp"
#include "zcalc/expression/rule_pool.hpp"

#include <memory>

namespace zcalc {

term_types Operation::get_type () const { return term_types::operation; }

bool Operation::is_numeric () const {
    if (m_left_operand == nullptr) return false;
    if (m_right_operand == nullptr) return false;
    if (!m_left_operand->is_numeric()) return false;
    if (!m_right_operand->is_numeric()) return false;
    return true;
}

void Operation::simplify () {
    if (m_left_operand == nullptr) { throw std::runtime_error("ERROR : left operand is null"); }
    if (m_right_operand == nullptr) { throw std::runtime_error("ERROR : right operand is null"); }
    m_left_operand->simplify();
    m_right_operand->simplify();

    while (true) {
        bool rule_applied = false;
        for (const std::shared_ptr<Rule> rule : RulePool::rules) {
            if (rule->apply(m_left_operand)) {
                rule_applied = true;
                break;
            }
        }
        if (rule_applied == false) {
            break;
        }
    }
    return;
}

bool Operation::is_zero () const {
    return std::abs(get_value()) < epsilon;
}

bool Operation::is_one () const {
    return ((std::abs(get_value().real() - 1.0)) < epsilon) && (std::abs(get_value().imag()) < epsilon);
}

complex Operation::get_value () const {
    if (m_left_operand == nullptr) { throw std::runtime_error("ERROR : operand cannot be null"); }
    if (m_right_operand == nullptr) { throw std::runtime_error("ERROR : operand cannot be null"); }
    switch(m_type) {
        case operation_types::add : {
            return m_left_operand->get_value() + m_right_operand->get_value();
        }
        case operation_types::sub : {
            return m_left_operand->get_value() - m_right_operand->get_value();
        }
        case operation_types::mul : {
            return m_left_operand->get_value() * m_right_operand->get_value();
        }
        case operation_types::div : {
            return m_left_operand->get_value() / m_right_operand->get_value(); /* TODO -> check if it is 0, math error */
        }
        default : {
            throw std::runtime_error("ERROR : invalid operator type");
        }
    }
}

void Operation::set_left_operand (std::shared_ptr<Term> operand) {
    m_left_operand = operand;
}

const std::shared_ptr<Term> Operation::get_left_operand () const {
    return m_left_operand;
}

void Operation::set_right_operand (std::shared_ptr<Term> operand) {
    m_right_operand = std::move(operand);
}

const std::shared_ptr<Term> Operation::get_right_operand () const {
    return m_right_operand;
}

void Operation::print (std::ostream &os) const {
    if (m_left_operand == nullptr) { throw std::runtime_error("ERROR : operand cannot be null"); }
    if (m_right_operand == nullptr) { throw std::runtime_error("ERROR : operand cannot be null"); }
    os << "(";
    m_left_operand->print(os);
    switch(m_type) {
        case operation_types::add : { os << "+"; break; }
        case operation_types::sub : { os << "-"; break; }
        case operation_types::mul : { os << "*"; break; }
        case operation_types::div : { os << "/"; break; }
        default : {
            throw std::runtime_error("ERROR : invalid operator type");
        }
    }
    m_right_operand->print(os);
    os << ")";
}

operation_types Operation::get_operation_type () const { return m_type; }
void Operation::set_operation_type (operation_types type) { m_type = type; }

bool Operation::is_constant () const { return false; }
bool Operation::is_variable () const { return false; }
bool Operation::is_operation () const {return true; }

} // namespace zcalc