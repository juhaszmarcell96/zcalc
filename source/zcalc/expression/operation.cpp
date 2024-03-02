#include "zcalc/expression/operation.hpp"
#include "zcalc/expression/constant.hpp"
#include "zcalc/expression/term_factory.hpp"

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

void Operation::reduce () {
    if (m_left_operand == nullptr) { throw std::runtime_error("ERROR : left operand is null"); }
    if (m_right_operand == nullptr) { throw std::runtime_error("ERROR : right operand is null"); }
    m_left_operand->reduce();
    m_right_operand->reduce();

    if (m_left_operand->is_numeric()) {
        m_left_operand = TermFactory::create(m_left_operand->get());
    }
    if (m_right_operand->is_numeric()) {
        m_right_operand = TermFactory::create(m_right_operand->get());
    }

    // a(b+c) = ab+ac
    if ((m_type == operation_types::mul) || (m_type == operation_types::div)) {
        if (m_left_operand->is_constant() || m_left_operand->is_variable()) {
            if (m_right_operand->is_operation()) {
                Operation* right_op = dynamic_cast<Operation*>(m_right_operand.get());
                operation_types op_type = right_op->get_operation_type();
                if ((op_type == operation_types::add) || (op_type == operation_types::sub)) {
                    operation_types old_type = m_type;
                    m_type = op_type;
                    auto new_left_operand = TermFactory::create(old_type, m_left_operand, right_op->get_left_operand());
                    auto new_right_operand = TermFactory::create(old_type, m_left_operand, right_op->get_right_operand());
                    m_left_operand = new_left_operand;
                    m_right_operand = new_right_operand;
                }
            }
        }
    }
    return;
}
bool Operation::is_zero () const {
    return std::abs(get()) < epsilon;
}

bool Operation::is_one () const {
    return ((std::abs(get().real() - 1.0)) < epsilon) && (std::abs(get().imag()) < epsilon);
}

complex Operation::get () const {
    if (m_left_operand == nullptr) { throw std::runtime_error("ERROR : operand cannot be null"); }
    if (m_right_operand == nullptr) { throw std::runtime_error("ERROR : operand cannot be null"); }
    switch(m_type) {
        case operation_types::add : {
            return m_left_operand->get() + m_right_operand->get();
        }
        case operation_types::sub : {
            return m_left_operand->get() - m_right_operand->get();
        }
        case operation_types::mul : {
            return m_left_operand->get() * m_right_operand->get();
        }
        case operation_types::div : {
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