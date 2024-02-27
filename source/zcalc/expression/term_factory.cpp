#include "zcalc/expression/term_factory.hpp"
#include "zcalc/expression/constant.hpp"
#include "zcalc/expression/term.hpp"
#include "zcalc/expression/operation.hpp"
#include "zcalc/expression/variable.hpp"
#include "zcalc/expression/variable_pool.hpp"

namespace zcalc {

std::unique_ptr<Term> TermFactory::create (const std::string& var_name) {
    VariablePool::define_variable(var_name);
    return std::make_unique<Variable>(var_name);
}

std::unique_ptr<Term> TermFactory::create (complex value) {
    return std::make_unique<Constant>(value);
}

std::unique_ptr<Term> TermFactory::create (operation_type type, std::unique_ptr<Term>&& lhs, std::unique_ptr<Term>&& rhs) {
    switch(type) {
        case operation_type::add : {
            if (lhs->is_numeric() && rhs->is_numeric()) {
                return std::make_unique<Constant>(lhs->get() + rhs->get());
            }
            else if (lhs->is_numeric()) {
                if (lhs->is_zero()) {
                    return std::move(rhs);
                }
            }
            else if (rhs->is_numeric()) {
                if (rhs->is_zero()) {
                    return std::move(lhs);
                }
            }
            std::unique_ptr<Operation> new_op = std::make_unique<Operation>(operation_type::add);
            new_op->set_left_operand(std::move(lhs));
            new_op->set_right_operand(std::move(rhs));
            new_op->reduce();
            return new_op;
        }
        case operation_type::sub : {
            if (lhs->is_numeric() && rhs->is_numeric()) {
                return std::make_unique<Constant>(lhs->get() - rhs->get());
            }
            else if (lhs->is_numeric()) {
                if (lhs->is_zero()) {
                    return std::move(rhs);
                }
            }
            else if (rhs->is_numeric()) {
                if (rhs->is_zero()) {
                    return std::move(lhs);
                }
            }
            std::unique_ptr<Operation> new_op = std::make_unique<Operation>(operation_type::sub);
            new_op->set_left_operand(std::move(lhs));
            new_op->set_right_operand(std::move(rhs));
            new_op->reduce();
            return new_op;
        }
        case operation_type::mul : {
            if (lhs->is_numeric() && rhs->is_numeric()) {
                return std::make_unique<Constant>(lhs->get() * rhs->get());
            }
            else if (lhs->is_numeric()) {
                if (lhs->is_zero()) {
                    return std::make_unique<Constant>(complex{0.0, 0.0});
                }
                else if (lhs->is_one()) {
                    return std::move(rhs);
                }
            }
            else if (rhs->is_numeric()) {
                if (rhs->is_zero()) {
                    return std::make_unique<Constant>(complex{0.0, 0.0});
                }
                else if (rhs->is_one()) {
                    return std::move(lhs);
                }
            }
            std::unique_ptr<Operation> new_op = std::make_unique<Operation>(operation_type::mul);
            new_op->set_left_operand(std::move(lhs));
            new_op->set_right_operand(std::move(rhs));
            new_op->reduce();
            return new_op;
        }
        case operation_type::div : {
            if (lhs->is_numeric() && rhs->is_numeric()) {
                return std::make_unique<Constant>(lhs->get() / rhs->get());
            }
            else if (lhs->is_numeric()) {
                if (lhs->is_zero()) {
                    return std::make_unique<Constant>(complex{0.0, 0.0});
                }
            }
            else if (rhs->is_numeric()) {
                if (rhs->is_zero()) {
                    throw std::runtime_error("ERROR : cannot divide by 0");
                }
                else if (rhs->is_one()) {
                    return std::move(lhs);
                }
            }
            std::unique_ptr<Operation> new_op = std::make_unique<Operation>(operation_type::div);
            new_op->set_left_operand(std::move(lhs));
            new_op->set_right_operand(std::move(rhs));
            //new_op->reduce();
            return new_op;
        }
        default : {
            throw std::runtime_error("ERROR : invalid operator type");
        }
    }
}

} // namespace zcalc