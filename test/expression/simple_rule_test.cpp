#include <gtest/gtest.h>

#include <zcalc/expression/expression.hpp>
#include <zcalc/expression/variable_pool.hpp>
#include <zcalc/expression/operation.hpp>

TEST(SimpleRuleTest, ConstantExpressionTest) {

    // 8 + 3 * (2 * 3)
    zcalc::Expression exp {
        zcalc::Expression(8) +
        zcalc::Expression(3) * (
            zcalc::Expression(2) *
            zcalc::Expression(3)
        )
    };

    ASSERT_TRUE(exp.get_root()->is_operation());
    auto value = exp.evaluate();
    exp.simplify();
    ASSERT_TRUE(exp.get_root()->is_constant());
    ASSERT_EQ(exp.evaluate(), value);
}

TEST(SimpleRuleTest, MulByOneLeft) {
    zcalc::VariablePool::define_variable("x");

    // 1 * (2 + x * 3)
    zcalc::Expression exp {
        zcalc::Expression(1) * (
            zcalc::Expression(2) +
            zcalc::Expression("x") *
            zcalc::Expression(3)
        )
    };

    {
        // ((1,0)*((2,0)+(x*(3,0))))
        const auto root = exp.get_root();
        ASSERT_TRUE(root);
        ASSERT_TRUE(root->is_operation());
        const auto root_op = std::dynamic_pointer_cast<zcalc::Operation>(root);
        ASSERT_TRUE(root_op);
        ASSERT_EQ(root_op->get_operation_type(), zcalc::operation_types::mul);
        const auto lhs = root_op->get_left_operand();
        const auto rhs = root_op->get_right_operand();
        ASSERT_TRUE(lhs);
        ASSERT_TRUE(rhs);
        ASSERT_TRUE(lhs->is_constant());
        ASSERT_TRUE(rhs->is_operation());
        ASSERT_EQ(lhs->get_value(), zcalc::complex(1.0, 0.0));
    }
    exp.simplify();
    {
        // ((2,0)+(x*(3,0)))
        const auto root = exp.get_root();
        ASSERT_TRUE(root);
        ASSERT_TRUE(root->is_operation());
        const auto root_op = std::dynamic_pointer_cast<zcalc::Operation>(root);
        ASSERT_TRUE(root_op);
        ASSERT_EQ(root_op->get_operation_type(), zcalc::operation_types::add);
        const auto lhs = root_op->get_left_operand();
        const auto rhs = root_op->get_right_operand();
        ASSERT_TRUE(lhs);
        ASSERT_TRUE(rhs);
        ASSERT_TRUE(lhs->is_constant());
        ASSERT_TRUE(rhs->is_operation());
        ASSERT_EQ(lhs->get_value(), zcalc::complex(2.0, 0.0));
        
        // check right-hand side of the addition operation
        ASSERT_TRUE(rhs->is_operation());
        const auto rhs_op = std::dynamic_pointer_cast<zcalc::Operation>(rhs);
        ASSERT_TRUE(rhs_op);
        ASSERT_EQ(rhs_op->get_operation_type(), zcalc::operation_types::mul);
        const auto rhs_lhs = rhs_op->get_left_operand();
        const auto rhs_rhs = rhs_op->get_right_operand();

        // check variable part of the multiplication
        ASSERT_TRUE(rhs_lhs->is_variable());
        ASSERT_EQ(std::dynamic_pointer_cast<zcalc::Variable>(rhs_lhs)->get_name(), "x");

        // check constant part of the multiplication
        ASSERT_TRUE(rhs_rhs->is_constant());
        ASSERT_EQ(rhs_rhs->get_value(), zcalc::complex(3.0, 0.0));
    }

    zcalc::VariablePool::undefine_variable("x");
}

TEST(SimpleRuleTest, MulByOneRight) {
    zcalc::VariablePool::define_variable("y");

    // (y * 2 + 3) * 1
    zcalc::Expression exp {
        (zcalc::Expression("y") * zcalc::Expression(2) + zcalc::Expression(3)) * zcalc::Expression(1)
    };

    // Before simplification
    {
        const auto root = exp.get_root();
        ASSERT_TRUE(root);
        ASSERT_TRUE(root->is_operation());
        const auto root_op = std::dynamic_pointer_cast<zcalc::Operation>(root);
        ASSERT_EQ(root_op->get_operation_type(), zcalc::operation_types::mul);
        const auto rhs = root_op->get_right_operand();
        ASSERT_TRUE(rhs->is_constant());
        ASSERT_EQ(rhs->get_value(), zcalc::complex(1.0, 0.0));
    }

    exp.simplify();

    // After simplification, expecting (y*2 + 3)
    {
        const auto root = exp.get_root();
        ASSERT_TRUE(root);
        ASSERT_TRUE(root->is_operation());
        const auto root_op = std::dynamic_pointer_cast<zcalc::Operation>(root);
        ASSERT_EQ(root_op->get_operation_type(), zcalc::operation_types::add);
        const auto lhs = root_op->get_left_operand();
        ASSERT_TRUE(lhs->is_operation()); // y*2 part
        const auto rhs = root_op->get_right_operand();
        ASSERT_TRUE(rhs->is_constant()); // 3 part
        ASSERT_EQ(rhs->get_value(), zcalc::complex(3.0, 0.0));
    }

    zcalc::VariablePool::undefine_variable("y");
}

TEST(SimpleRuleTest, DivByOne) {
    zcalc::VariablePool::define_variable("z");

    // (4 + z * 2) / 1
    zcalc::Expression exp {
        (zcalc::Expression(4) + zcalc::Expression("z") * zcalc::Expression(2)) / zcalc::Expression(1)
    };

    // Before simplification
    {
        const auto root = exp.get_root();
        ASSERT_TRUE(root);
        ASSERT_TRUE(root->is_operation());
        const auto root_op = std::dynamic_pointer_cast<zcalc::Operation>(root);
        ASSERT_EQ(root_op->get_operation_type(), zcalc::operation_types::div);
        const auto rhs = root_op->get_right_operand();
        ASSERT_TRUE(rhs->is_constant());
        ASSERT_EQ(rhs->get_value(), zcalc::complex(1.0, 0.0));
    }

    exp.simplify();

    // After simplification, expecting (4+z*2)
    {
        const auto root = exp.get_root();
        ASSERT_TRUE(root);
        ASSERT_TRUE(root->is_operation());
        const auto root_op = std::dynamic_pointer_cast<zcalc::Operation>(root);
        ASSERT_EQ(root_op->get_operation_type(), zcalc::operation_types::add);
        const auto lhs = root_op->get_left_operand();
        ASSERT_TRUE(lhs->is_constant()); // 4 part
        ASSERT_EQ(lhs->get_value(), zcalc::complex(4.0, 0.0));
        const auto rhs = root_op->get_right_operand();
        ASSERT_TRUE(rhs->is_operation()); // z*2 part
    }

    zcalc::VariablePool::undefine_variable("z");
}

TEST(SimpleRuleTest, MultiplyByZero) {
    zcalc::VariablePool::define_variable("x");

    // x * 0
    zcalc::Expression exp { zcalc::Expression("x") * zcalc::Expression(0) };

    exp.simplify();

    // Check that the simplified expression is 0
    const auto root = exp.get_root();
    ASSERT_TRUE(root->is_constant());
    ASSERT_EQ(root->get_value(), zcalc::complex(0.0, 0.0));

    zcalc::VariablePool::undefine_variable("x");
}

TEST(SimpleRuleTest, ZeroMultiplyByA) {
    zcalc::VariablePool::define_variable("y");

    // 0 * (y + 2)
    zcalc::Expression exp = zcalc::Expression(0) * (zcalc::Expression("y") + zcalc::Expression(2));

    exp.simplify();

    // Check that the simplified expression is 0
    const auto root = exp.get_root();
    ASSERT_TRUE(root->is_constant());
    ASSERT_EQ(root->get_value(), zcalc::complex(0.0, 0.0));

    zcalc::VariablePool::undefine_variable("y");
}

TEST(SimpleRuleTest, DivideByZero) {
    zcalc::VariablePool::define_variable("z");

    // z / 0
    zcalc::Expression exp = zcalc::Expression("z") / zcalc::Expression(0);
    ASSERT_THROW(exp.simplify(), std::runtime_error);

    zcalc::VariablePool::undefine_variable("z");
}

TEST(SimpleRuleTest, ZeroDivideByA) {
    zcalc::VariablePool::define_variable("w");

    // 0 / (w + 1)
    zcalc::Expression exp = zcalc::Expression(0) / (zcalc::Expression("w") + zcalc::Expression(1));

    exp.simplify();

    // Check that the simplified expression is 0
    const auto root = exp.get_root();
    ASSERT_TRUE(root->is_constant());
    ASSERT_EQ(root->get_value(), zcalc::complex(0.0, 0.0));

    zcalc::VariablePool::undefine_variable("w");
}

TEST(SimpleRuleTest, AddZero) {
    zcalc::VariablePool::define_variable("v");

    // (v * 2) + 0
    zcalc::Expression exp = (zcalc::Expression("v") * zcalc::Expression(2)) + zcalc::Expression(0);

    exp.simplify();

    // Check that the simplified expression is (v * 2)
    const auto root = exp.get_root();
    ASSERT_TRUE(root->is_operation());
    ASSERT_EQ(std::dynamic_pointer_cast<zcalc::Operation>(root)->get_operation_type(), zcalc::operation_types::mul);

    zcalc::VariablePool::undefine_variable("v");
}

TEST(SimpleRuleTest, ZeroAdd) {
    zcalc::VariablePool::define_variable("u");

    // 0 + (u / 2)
    zcalc::Expression exp = zcalc::Expression(0) + (zcalc::Expression("u") / zcalc::Expression(2));

    exp.simplify();

    // Check that the simplified expression is (u / 2)
    const auto root = exp.get_root();
    ASSERT_TRUE(root->is_operation());
    ASSERT_EQ(std::dynamic_pointer_cast<zcalc::Operation>(root)->get_operation_type(), zcalc::operation_types::div);

    zcalc::VariablePool::undefine_variable("u");
}

TEST(SimpleRuleTest, SubtractZero) {
    zcalc::VariablePool::define_variable("t");

    // (t + 2) - 0
    zcalc::Expression exp = (zcalc::Expression("t") + zcalc::Expression(2)) - zcalc::Expression(0);

    exp.simplify();

    // Check that the simplified expression is (t ^ 2)
    const auto root = exp.get_root();
    ASSERT_TRUE(root->is_operation());
    ASSERT_EQ(std::dynamic_pointer_cast<zcalc::Operation>(root)->get_operation_type(), zcalc::operation_types::add);

    zcalc::VariablePool::undefine_variable("t");
}