#include <zcalc/expression/rule.hpp>
#include <zcalc/expression/term_factory.hpp>

#include <tuple>

namespace zcalc {

bool ConstantRule::apply (std::shared_ptr<Term>& term) const {
    if (!term) { return false; }
    if (term->is_numeric() && !term->is_constant()) {
        term = TermFactory::create(term->get_value());
        return true;
    }
    return false;
}

bool OneRule::apply (std::shared_ptr<Term>& term) const {
    if (!term) { return false; }
    // a * 1 = a
    // 1 * a = a
    // a / 1 = a
    term_types term_type = term->get_type();
    if (term_type == term_types::constant) { return false; }
    if (term_type == term_types::variable) { return false; }

    std::shared_ptr<Operation> op = std::dynamic_pointer_cast<Operation>(term);

    operation_types op_type = op->get_operation_type();
    if (op_type == operation_types::add) { return false; }
    if (op_type == operation_types::sub) { return false; }

    const std::shared_ptr<Term> lhs = op->get_left_operand();
    const std::shared_ptr<Term> rhs = op->get_right_operand();

    if (op_type == operation_types::mul) {
        if (lhs->is_constant()) {
            if (lhs->is_one()) {
                term = rhs;
                return true;
            }
        }
        if (rhs->is_constant()) {
            if (rhs->is_one()) {
                term = lhs;
                return true;
            }
        }
    }
    if (op_type == operation_types::div) {
        if (rhs->is_constant()) {
            if (rhs->is_one()) {
                term = lhs;
                return true;
            }
        }
    }
    return false;
}

bool ZeroRule::apply (std::shared_ptr<Term>& term) const {
    if (!term) { return false; }
    // a * 0 = 0
    // 0 * a = 0
    // a / 0 = ERROR
    // 0 / a = 0
    // a + 0 = a
    // 0 + a = a
    // a - 0 = a
    term_types term_type = term->get_type();
    if (term_type == term_types::constant) { return false; }
    if (term_type == term_types::variable) { return false; }

    std::shared_ptr<Operation> op = std::dynamic_pointer_cast<Operation>(term);

    operation_types op_type = op->get_operation_type();

    const std::shared_ptr<Term> lhs = op->get_left_operand();
    const std::shared_ptr<Term> rhs = op->get_right_operand();

    if (op_type == operation_types::mul) {
        // 0 * a = 0
        if (lhs->is_constant()) {
            if (lhs->is_zero()) {
                term = TermFactory::create(complex{0.0, 0.0});
                return true;
            }
        }
        // a * 0 = 0
        if (rhs->is_constant()) {
            if (rhs->is_zero()) {
                term = TermFactory::create(complex{0.0, 0.0});
                return true;
            }
        }
    }
    if (op_type == operation_types::div) {
        // 0 / a = 0
        if (lhs->is_constant()) {
            if (lhs->is_zero()) {
                term = TermFactory::create(complex{0.0, 0.0});
                return true;
            }
        }
        // a / 0 = ERROR
        if (rhs->is_constant()) {
            if (rhs->is_zero()) {
                throw std::runtime_error("ERROR : cannot divide by 0");
            }
        }
    }
    if (op_type == operation_types::add) {
        // 0 + a = a
        if (lhs->is_constant()) {
            if (lhs->is_zero()) {
                term = rhs;
                return true;
            }
        }
        // a + 0 = a
        if (rhs->is_constant()) {
            if (rhs->is_zero()) {
                term = lhs;
                return true;
            }
        }
    }
    if (op_type == operation_types::sub) {
        // a - 0 = a
        if (rhs->is_constant()) {
            if (rhs->is_zero()) {
                term = lhs;
                return true;
            }
        }
    }
    return false;
}

/*

bool DistributiveRule::apply (Operation* operation) const {
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

bool AssociativeRule::apply (Operation* operation) const {
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

*/

} // namespace zcalc