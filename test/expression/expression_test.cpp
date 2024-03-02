#include <gtest/gtest.h>

#include <zcalc/expression/variable.hpp>
#include <zcalc/expression/variable_pool.hpp>
#include <zcalc/expression/expression.hpp>
#include <zcalc/expression/term_factory.hpp>

TEST(ExpressionTest, BuildingExpressionTest) {
    zcalc::VariablePool::define_variable("x");

    // 8x + 3 * (2x - 3)
    zcalc::Expression exp {
        zcalc::Expression(8) *
        zcalc::Expression("x") +
        zcalc::Expression(3) * (
            zcalc::Expression(2) *
            zcalc::Expression("x") -
            zcalc::Expression(3)
        )
    };

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

TEST(ExpressionTest, ComplexAdditionMultiplicationTest) {
    zcalc::VariablePool::define_variable("z");

    // (3 + 2i)z + (4 - i)(2z - 3)
    zcalc::Expression exp {
        zcalc::Expression(zcalc::complex(3, 2)) *
        zcalc::Expression("z") +
        zcalc::Expression(zcalc::complex(4, -1)) * (
            zcalc::Expression(2) *
            zcalc::Expression("z") -
            zcalc::Expression(3)
        )
    };

    // (3 + 2i) * (1 + 1i) + (4 - i) * (2 * (1 + 1i) - 3)
    zcalc::VariablePool::set_variable("z", zcalc::complex(1, 1));
    ASSERT_EQ(exp.evaluate(), zcalc::complex(-1.0, 14.0));
    // (3 + 2i) * (-1 + 2i) + (4 - i) * (2 * (-1 + 2i) - 3)
    zcalc::VariablePool::set_variable("z", zcalc::complex(-1, 2));
    ASSERT_EQ(exp.evaluate(), zcalc::complex(-23.0, 25.0));

    zcalc::VariablePool::undefine_variable("z");
}

TEST(ExpressionTest, NestedExpressionDivisionTest) {
    zcalc::VariablePool::define_variable("y");

    // ((5y + 2) / (3 - y)) + 4y
    zcalc::Expression exp {
        (zcalc::Expression(5) *
        zcalc::Expression("y") +
        zcalc::Expression(2)) /
        (zcalc::Expression(3) -
        zcalc::Expression("y")) +
        zcalc::Expression(4) *
        zcalc::Expression("y")
    };

    // ((5 * 1 + 2) / (3 - 1)) + 4 * 1
    zcalc::VariablePool::set_variable("y", 1);
    ASSERT_EQ(exp.evaluate(), zcalc::complex(7.5, 0.0));
    // ((5 * 0.5 + 2) / (3 - 0.5)) + 4 * 0.5
    zcalc::VariablePool::set_variable("y", 0.5);
    ASSERT_EQ(exp.evaluate(), zcalc::complex(3.8, 0.0));

    zcalc::VariablePool::undefine_variable("y");
}

TEST(ExpressionTest, ComplexNumberDivisionTest) {
    zcalc::VariablePool::define_variable("a");

    // (6a - (3 + 4i)) / (2a + (1 - 2i))
    zcalc::Expression exp {
        (zcalc::Expression(6) *
        zcalc::Expression("a") -
        zcalc::Expression(zcalc::complex(3, 4))) /
        (zcalc::Expression(2) *
        zcalc::Expression("a") +
        zcalc::Expression(zcalc::complex(1, -2)))
    };

    // (6 * (2 + 3i) - (3 + 4i)) / (2 * (2 + 3i) + (1 - 2i))
    zcalc::VariablePool::set_variable("a", zcalc::complex(2, 3));
    ASSERT_NEAR(exp.evaluate().real(), 2.46341463, 0.00000001);
    ASSERT_NEAR(exp.evaluate().imag(), 0.829268293, 0.00000001);
    // (6 * (1 - 1i) - (3 + 4i)) / (2 * (1 - 1i) + (1 - 2i))
    zcalc::VariablePool::set_variable("a", zcalc::complex(1, -1));
    ASSERT_EQ(exp.evaluate(), zcalc::complex(1.96, -0.72));

    zcalc::VariablePool::undefine_variable("a");
}

TEST(ExpressionTest, MultiVariableAddMulTest) {
    zcalc::VariablePool::define_variable("a");
    zcalc::VariablePool::define_variable("b");

    // (a + 2b) * (3a - b)
    zcalc::Expression exp {
        (zcalc::Expression("a") +
        zcalc::Expression(2) * zcalc::Expression("b")) *
        (zcalc::Expression(3) * zcalc::Expression("a") -
        zcalc::Expression("b"))
    };

    // (2 + 2*3) * (3*2 - 3) = (2 + 6) * (6 - 3) = 8 * 3
    zcalc::VariablePool::set_variable("a", 2);
    zcalc::VariablePool::set_variable("b", 3);
    ASSERT_EQ(exp.evaluate(), zcalc::complex(24.0, 0.0));
    // (4 + 2*1) * (3*4 - 1) = (4 + 2) * (12 - 1) = 6 * 11
    zcalc::VariablePool::set_variable("a", 4);
    zcalc::VariablePool::set_variable("b", 1);
    ASSERT_EQ(exp.evaluate(), zcalc::complex(66.0, 0.0));

    zcalc::VariablePool::undefine_variable("a");
    zcalc::VariablePool::undefine_variable("b");
}

TEST(ExpressionTest, ComplexNumberMultiVariableTest) {
    zcalc::VariablePool::define_variable("x");
    zcalc::VariablePool::define_variable("y");

    // x*(2 + y) + (1 - 2i)(x - y)
    zcalc::Expression exp {
        zcalc::Expression("x") * (
            zcalc::Expression(2) + zcalc::Expression("y")
        ) + zcalc::Expression(zcalc::complex(1, -2)) * (
            zcalc::Expression("x") - zcalc::Expression("y")
        )
    };

    // 2*(2 + 3) + (1 - 2i)*(2 - 3) = 2*5 + (1 - 2i)*(-1) = 10 - 1 + 2i = 9 + 2i
    zcalc::VariablePool::set_variable("x", 2);
    zcalc::VariablePool::set_variable("y", 3);
    ASSERT_EQ(exp.evaluate(), zcalc::complex(9.0, 2.0));
    // (1 + 2i)*(2 + (1 + 2i)) + (1 - 2i)*((1 + 2i) - (1 + 2i)) = (1 + 2i)*3 + (1 - 2i)*0 = 3 + 6i
    zcalc::VariablePool::set_variable("x", zcalc::complex(1, 2));
    zcalc::VariablePool::set_variable("y", zcalc::complex(1, 2));
    ASSERT_EQ(exp.evaluate(), zcalc::complex(-1, 8));

    zcalc::VariablePool::undefine_variable("x");
    zcalc::VariablePool::undefine_variable("y");
}

TEST(ExpressionTest, DivisionMultiplicationMultiVarTest) {
    zcalc::VariablePool::define_variable("m");
    zcalc::VariablePool::define_variable("n");

    // (4m / (2 + n)) + (3n * (m - 1))
    zcalc::Expression exp {
        (zcalc::Expression(4) * zcalc::Expression("m")) / (
            zcalc::Expression(2) + zcalc::Expression("n")
        ) + (zcalc::Expression(3) * zcalc::Expression("n")) * (
            zcalc::Expression("m") - zcalc::Expression(1)
        )
    };

    // (4*2 / (2 + 4)) + (3*4 * (2 - 1)) = (8 / 6) + (12 * 1) = 4/3 + 12 = 12 4/3
    zcalc::VariablePool::set_variable("m", 2);
    zcalc::VariablePool::set_variable("n", 4);
    ASSERT_EQ(exp.evaluate(), zcalc::complex(12 + 4.0/3.0, 0.0));
    // (4*3 / (2 + 2)) + (3*2 * (3 - 1)) = (12 / 4) + (6 * 2) = 3 + 12 = 15
    zcalc::VariablePool::set_variable("m", 3);
    zcalc::VariablePool::set_variable("n", 2);
    ASSERT_EQ(exp.evaluate(), zcalc::complex(15.0, 0.0));

    zcalc::VariablePool::undefine_variable("m");
    zcalc::VariablePool::undefine_variable("n");
}