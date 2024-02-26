#include "zcalc/expression/operation.hpp"
#include "zcalc/expression/constant.hpp"
#include "zcalc/expression/term_factory.hpp"

#include <memory>

namespace zcalc {

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

    // a(b+c) = ab+ac | a is const
    /*
    if ((m_type == operation_type::mul) || (m_type == operation_type::div)) {
        if (m_left_operand->is_constant() || m_left_operand->is_variable()) {
            if (m_right_operand->is_operation()) {
                Operation* right_op = dynamic_cast<Operation*>(m_right_operand.get());
                operation_type op_type = right_op->get_type();
                if ((op_type == operation_type::add) || (op_type == operation_type::sub)) {
                    operation_type old_type = m_type;
                    m_type = op_type;
                    m_left_operand = TermFactory::create(old_type, m_left_operand, right_op->get_left_operand());
                    m_right_operand = TermFactory::create(old_type, m_left_operand, right_op->get_right_operand());
                }
            }
        }
    }
    */
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

//const std::shared_ptr<const Term> Operation::get_left_operand () const {
std::shared_ptr<Term> Operation::get_left_operand () {
    return m_left_operand;
}

void Operation::set_right_operand (std::shared_ptr<Term> operand) {
    m_right_operand = operand;
}

//const std::shared_ptr<const Term> Operation::get_right_operand () const {
std::shared_ptr<Term> Operation::get_right_operand () {
    return m_right_operand;
}

void Operation::print (std::ostream &os) const {
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

operation_type Operation::get_type () const { return m_type; }

bool Operation::is_constant () const { return false; }
bool Operation::is_variable () const { return false; }
bool Operation::is_operation () const {return true; }

} // namespace zcalc