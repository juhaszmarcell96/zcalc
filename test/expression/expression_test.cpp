#include <gtest/gtest.h>

#include <zcalc/expression/variable.hpp>
#include <zcalc/expression/variable_pool.hpp>
#include <zcalc/expression/expression.hpp>
#include <zcalc/expression/term_factory.hpp>

TEST(ExpressionTest, BuildingExpressionTest) {
    // 8x + 4 + 3 * (2x - 3)
    zcalc::Expression exp {
        zcalc::Expression(8) *
        zcalc::Expression("x") +
        zcalc::Expression(3) * (
            zcalc::Expression(2) *
            zcalc::Expression("x") -
            zcalc::Expression(3)
        )
    };

    std::cout << exp << std::endl;
    zcalc::VariablePool::set_variable("x", 1);
    ASSERT_EQ(exp.evaluate(), zcalc::complex(5.0, 0.0));
    zcalc::VariablePool::unset_variable("x");
    EXPECT_THROW(exp.evaluate(), std::runtime_error);
    zcalc::VariablePool::set_variable("x", 2);
    ASSERT_EQ(exp.evaluate(), zcalc::complex(19.0, 0.0));
    zcalc::VariablePool::set_variable("x", -1.5);
    ASSERT_EQ(exp.evaluate(), zcalc::complex(-30.0, 0.0));

    zcalc::VariablePool::undefine_variable("x");
}

TEST(ExpressionTest, ReduceTest) {
    // 2 * ( 2 + 3 )
    zcalc::Expression exp {
        zcalc::Expression("x") * (
            zcalc::Expression(2) +
            zcalc::Expression("y")
        )
    };

    std::cout << exp << std::endl;
    exp.reduce();
    std::cout << exp << std::endl;
}