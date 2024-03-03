#include "zcalc/expression/term_factory.hpp"
#include "zcalc/expression/constant.hpp"
#include "zcalc/expression/term.hpp"
#include "zcalc/expression/operation.hpp"
#include "zcalc/expression/variable.hpp"
#include "zcalc/expression/variable_pool.hpp"

namespace zcalc {

std::shared_ptr<Term> TermFactory::create (const std::string& var_name, complex coeff) {
    VariablePool::define_variable(var_name);
    return std::make_shared<Variable>(var_name, coeff);
}

std::shared_ptr<Term> TermFactory::create (complex value) {
    return std::make_shared<Constant>(value);
}

std::shared_ptr<Term> TermFactory::create (double value) {
    return std::make_shared<Constant>(value);
}

std::shared_ptr<Term> TermFactory::create (int value) {
    return std::make_shared<Constant>(value);
}

std::shared_ptr<Term> TermFactory::create (operation_types type, std::shared_ptr<Term> lhs, std::shared_ptr<Term> rhs) {
    switch(type) {
        case operation_types::add : {
            std::shared_ptr<Operation> new_op = std::make_shared<Operation>(operation_types::add);
            new_op->set_left_operand(lhs);
            new_op->set_right_operand(rhs);
            return new_op;
        }
        case operation_types::sub : {
            std::shared_ptr<Operation> new_op = std::make_shared<Operation>(operation_types::sub);
            new_op->set_left_operand(lhs);
            new_op->set_right_operand(rhs);
            return new_op;
        }
        case operation_types::mul : {
            std::shared_ptr<Operation> new_op = std::make_shared<Operation>(operation_types::mul);
            new_op->set_left_operand(lhs);
            new_op->set_right_operand(rhs);
            return new_op;
        }
        case operation_types::div : {
            std::shared_ptr<Operation> new_op = std::make_shared<Operation>(operation_types::div);
            new_op->set_left_operand(lhs);
            new_op->set_right_operand(rhs);
            return new_op;
        }
        default : {
            throw std::runtime_error("ERROR : invalid operator type");
        }
    }
}

} // namespace zcalc