#include <gtest/gtest.h>

#include <zcalc/expression/expression.hpp>
#include <zcalc/expression/variable_pool.hpp>
#include <zcalc/expression/operation.hpp>
#include <zcalc/expression/term_factory.hpp>
#include <zcalc/expression/rule.hpp>

TEST(SimpleRuleTest, ConstantExpressionTest) {

    // 8 + 3 * (2 * 3)
    auto const_8 = zcalc::TermFactory::create(8);
    auto const_3 = zcalc::TermFactory::create(3);
    auto const_2 = zcalc::TermFactory::create(2);
    auto op_mul_inner = zcalc::TermFactory::create(zcalc::operation_types::mul, const_2, const_3);
    auto op_mul_outer = zcalc::TermFactory::create(zcalc::operation_types::mul, const_3, op_mul_inner);
    auto root = zcalc::TermFactory::create(zcalc::operation_types::add, const_8, op_mul_outer);

    zcalc::ConstantRule rule {};
    rule.apply(root);

    ASSERT_TRUE(root->is_constant());
    ASSERT_EQ(root->get_value(), zcalc::complex(26.0, 0.0));
}

TEST(SimpleRuleTest, MulByOneLeft) {
    zcalc::VariablePool::define_variable("x");

    // 1 * (2 + x * 3)
    auto const_1 = zcalc::TermFactory::create(1);
    auto const_2 = zcalc::TermFactory::create(2);
    auto var_x = zcalc::TermFactory::create("x");
    auto const_3 = zcalc::TermFactory::create(3);
    auto op_mul = zcalc::TermFactory::create(zcalc::operation_types::mul, var_x, const_3);
    auto op_add = zcalc::TermFactory::create(zcalc::operation_types::add, const_2, op_mul);
    auto root = zcalc::TermFactory::create(zcalc::operation_types::mul, const_1, op_add);

    {
        // ((1,0)*((2,0)+(x*(3,0))))
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
    zcalc::OneRule rule {};
    rule.apply(root);
    {
        // ((2,0)+(x*(3,0)))
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
    auto var_y = zcalc::TermFactory::create("y");
    auto const_2 = zcalc::TermFactory::create(2);
    auto const_3 = zcalc::TermFactory::create(3);
    auto const_1 = zcalc::TermFactory::create(1);
    auto op_mul = zcalc::TermFactory::create(zcalc::operation_types::mul, var_y, const_2);
    auto op_add = zcalc::TermFactory::create(zcalc::operation_types::add, op_mul, const_3);
    auto root = zcalc::TermFactory::create(zcalc::operation_types::mul, op_add, const_1);

    // Before simplification
    {
        ASSERT_TRUE(root->is_operation());
        const auto root_op = std::dynamic_pointer_cast<zcalc::Operation>(root);
        ASSERT_EQ(root_op->get_operation_type(), zcalc::operation_types::mul);
        const auto rhs = root_op->get_right_operand();
        ASSERT_TRUE(rhs->is_constant());
        ASSERT_EQ(rhs->get_value(), zcalc::complex(1.0, 0.0));
    }

    zcalc::OneRule rule {};
    rule.apply(root);

    // After simplification, expecting (y*2 + 3)
    {
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
    auto const_4 = zcalc::TermFactory::create(4);
    auto var_z = zcalc::TermFactory::create("z");
    auto const_2 = zcalc::TermFactory::create(2);
    auto const_1 = zcalc::TermFactory::create(1);
    auto op_mul = zcalc::TermFactory::create(zcalc::operation_types::mul, var_z, const_2);
    auto op_add = zcalc::TermFactory::create(zcalc::operation_types::add, const_4, op_mul);
    auto root = zcalc::TermFactory::create(zcalc::operation_types::div, op_add, const_1);

    // Before simplification
    {
        ASSERT_TRUE(root->is_operation());
        const auto root_op = std::dynamic_pointer_cast<zcalc::Operation>(root);
        ASSERT_EQ(root_op->get_operation_type(), zcalc::operation_types::div);
        const auto rhs = root_op->get_right_operand();
        ASSERT_TRUE(rhs->is_constant());
        ASSERT_EQ(rhs->get_value(), zcalc::complex(1.0, 0.0));
    }

    zcalc::OneRule rule {};
    rule.apply(root);

    // After simplification, expecting (4+z*2)
    {
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
    auto var_x = zcalc::TermFactory::create("x");
    auto const_0 = zcalc::TermFactory::create(0);
    auto root = zcalc::TermFactory::create(zcalc::operation_types::mul, var_x, const_0);

    zcalc::ZeroRule rule {};
    rule.apply(root);

    // Check that the simplified expression is 0
    ASSERT_TRUE(root->is_constant());
    ASSERT_EQ(root->get_value(), zcalc::complex(0.0, 0.0));

    zcalc::VariablePool::undefine_variable("x");
}

TEST(SimpleRuleTest, ZeroMultiplyByA) {
    zcalc::VariablePool::define_variable("y");

    // 0 * (y + 2)
    auto const_0 = zcalc::TermFactory::create(0);
    auto var_y = zcalc::TermFactory::create("y");
    auto const_2 = zcalc::TermFactory::create(2);
    auto op_add = zcalc::TermFactory::create(zcalc::operation_types::add, var_y, const_2);
    auto root = zcalc::TermFactory::create(zcalc::operation_types::mul, const_0, op_add);

    zcalc::ZeroRule rule {};
    rule.apply(root);

    // Check that the simplified expression is 0
    ASSERT_TRUE(root->is_constant());
    ASSERT_EQ(root->get_value(), zcalc::complex(0.0, 0.0));

    zcalc::VariablePool::undefine_variable("y");
}

TEST(SimpleRuleTest, DivideByZero) {
    zcalc::VariablePool::define_variable("z");

    // z / 0
    auto var_z = zcalc::TermFactory::create("z");
    auto const_0 = zcalc::TermFactory::create(0);
    auto root = zcalc::TermFactory::create(zcalc::operation_types::div, var_z, const_0);

    zcalc::ZeroRule rule {};
    ASSERT_THROW(rule.apply(root);, std::runtime_error);

    zcalc::VariablePool::undefine_variable("z");
}

TEST(SimpleRuleTest, ZeroDivideByA) {
    zcalc::VariablePool::define_variable("w");

    // 0 / (w + 1)
    auto const_0 = zcalc::TermFactory::create(0);
    auto var_w = zcalc::TermFactory::create("w");
    auto const_1 = zcalc::TermFactory::create(1);
    auto op_add = zcalc::TermFactory::create(zcalc::operation_types::add, var_w, const_1);
    auto root = zcalc::TermFactory::create(zcalc::operation_types::div, const_0, op_add);

    zcalc::ZeroRule rule {};
    rule.apply(root);

    // Check that the simplified expression is 0
    ASSERT_TRUE(root->is_constant());
    ASSERT_EQ(root->get_value(), zcalc::complex(0.0, 0.0));

    zcalc::VariablePool::undefine_variable("w");
}

TEST(SimpleRuleTest, AddZero) {
    zcalc::VariablePool::define_variable("v");

    // (v * 2) + 0
    auto var_v = zcalc::TermFactory::create("v");
    auto const_2 = zcalc::TermFactory::create(2);
    auto const_0 = zcalc::TermFactory::create(0);
    auto op_mul = zcalc::TermFactory::create(zcalc::operation_types::mul, var_v, const_2);
    auto root = zcalc::TermFactory::create(zcalc::operation_types::add, op_mul, const_0);

    zcalc::ZeroRule rule {};
    rule.apply(root);

    // Check that the simplified expression is (v * 2)
    ASSERT_TRUE(root->is_operation());
    ASSERT_EQ(std::dynamic_pointer_cast<zcalc::Operation>(root)->get_operation_type(), zcalc::operation_types::mul);

    zcalc::VariablePool::undefine_variable("v");
}

TEST(SimpleRuleTest, ZeroAdd) {
    zcalc::VariablePool::define_variable("u");

    // 0 + (u / 2)
    zcalc::Expression exp = zcalc::Expression(0) + (zcalc::Expression("u") / zcalc::Expression(2));
    auto var_u = zcalc::TermFactory::create("u");
    auto const_2 = zcalc::TermFactory::create(2);
    auto op_div = zcalc::TermFactory::create(zcalc::operation_types::div, var_u, const_2);
    auto const_0 = zcalc::TermFactory::create(0);
    auto root = zcalc::TermFactory::create(zcalc::operation_types::add, const_0, op_div);

    zcalc::ZeroRule rule {};
    rule.apply(root);

    // Check that the simplified expression is (u / 2)
    ASSERT_TRUE(root->is_operation());
    ASSERT_EQ(std::dynamic_pointer_cast<zcalc::Operation>(root)->get_operation_type(), zcalc::operation_types::div);

    zcalc::VariablePool::undefine_variable("u");
}

TEST(SimpleRuleTest, SubtractZero) {
    zcalc::VariablePool::define_variable("t");

    // (t + 2) - 0
    auto var_t = zcalc::TermFactory::create("t");
    auto const_2 = zcalc::TermFactory::create(2);
    auto const_0 = zcalc::TermFactory::create(0);
    auto op_add = zcalc::TermFactory::create(zcalc::operation_types::add, var_t, const_2);
    auto root = zcalc::TermFactory::create(zcalc::operation_types::sub, op_add, const_0);

    zcalc::ZeroRule rule {};
    rule.apply(root);

    // Check that the simplified expression is (t + 2)
    ASSERT_TRUE(root->is_operation());
    ASSERT_EQ(std::dynamic_pointer_cast<zcalc::Operation>(root)->get_operation_type(), zcalc::operation_types::add);

    zcalc::VariablePool::undefine_variable("t");
}