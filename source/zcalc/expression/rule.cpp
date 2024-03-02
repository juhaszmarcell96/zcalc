#pragma once

#include <zcalc/expression/rule.hpp>
#include <zcalc/expression/term_factory.hpp>

#include <tuple>

namespace zcalc {

bool DistributiveRule::simplify (Operation* operation) const {
    if (!operation) { return false; }
    // a(b+c) = ab+ac
    // (b+c)a = ba+ca
    // (a+b)(c+d) = ac + ad + bc + bd
    operation_types this_op_type = operation->get_operation_type();
    if ((this_op_type != operation_types::mul) && (this_op_type != operation_types::div)) { return false; }

    const auto lhs = operation->get_left_operand();
    const auto rhs = operation->get_right_operand();
    if (!lhs || !rhs) { return false; }

    term_types l_type = lhs->get_type();
    term_types r_type = rhs->get_type();

    if ((l_type != term_types::operation) && (r_type != term_types::operation)) { return false; }
    
    if (r_type == term_types::operation) {
        const Operation* right_op = dynamic_cast<const Operation*>(rhs.get());
        operation_types op_type = right_op->get_operation_type();
        if ((op_type == operation_types::add) || (op_type == operation_types::sub)) {
            operation->set_operation_type(op_type);
            const auto rl_op = right_op->get_left_operand();
            const auto rr_op = right_op->get_right_operand();
            if (!rl_op || !rr_op) { return false; }
            auto new_left_operand = TermFactory::create(this_op_type, lhs, rl_op);
            auto new_right_operand = TermFactory::create(this_op_type, lhs, rr_op);
            operation->set_left_operand(new_left_operand);
            operation->set_right_operand(new_right_operand);
            return true;
        }
    }

    return false;
}

bool AssociativeRule::simplify (Operation* operation) const {
    if (!operation) { return false; }
    // (a * b) * c = a * (b * c)
    // (a + b) + c = a + (b + c)
    operation_types this_op_type = operation->get_operation_type();
    if ((this_op_type != operation_types::sub) && (this_op_type != operation_types::div)) { return false; }

    const auto lhs = operation->get_left_operand();
    const auto rhs = operation->get_right_operand();
    if (!lhs || !rhs) { return false; }

    term_types l_type = lhs->get_type();
    term_types r_type = rhs->get_type();

    if ((l_type != term_types::operation) && (r_type != term_types::operation)) { return false; }
    
    if (r_type == term_types::operation) {
        const Operation* right_op = dynamic_cast<const Operation*>(rhs.get());
        operation_types op_type = right_op->get_operation_type();
        if ((op_type == operation_types::add) || (op_type == operation_types::sub)) {
            operation->set_operation_type(op_type);
            const auto rl_op = right_op->get_left_operand();
            const auto rr_op = right_op->get_right_operand();
            if (!rl_op || !rr_op) { return false; }
            auto new_left_operand = TermFactory::create(this_op_type, lhs, rl_op);
            auto new_right_operand = TermFactory::create(this_op_type, lhs, rr_op);
            operation->set_left_operand(new_left_operand);
            operation->set_right_operand(new_right_operand);
            return true;
        }
    }

    return false;
}

} // namespace zcalc