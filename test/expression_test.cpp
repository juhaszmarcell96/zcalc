#include <gtest/gtest.h>

#include <include/expression.hpp>

#include <complex>

TEST(ExpressionTest, SimpleExpression) {
    zcalc::Expression exp {5};
    exp += 3;
    exp += 2;
    exp /= 5;

    std::complex<double> expected_result { 2.0, 0.0 };

    ASSERT_EQ(exp.evaluate(), expected_result);
}

TEST(ExpressionTest, VariableTest) {
    std::shared_ptr<zcalc::Variable> x = std::make_shared<zcalc::Variable>("x");

    zcalc::Expression exp {x};
    exp *= 3;
    exp += 5;

    x->set_value(5);

    std::complex<double> expected_result { 20.0, 0.0 };

    ASSERT_EQ(exp.evaluate(), expected_result);
}

TEST(ExpressionTest, MultipleExpressions) {
    std::shared_ptr<zcalc::Variable> x = std::make_shared<zcalc::Variable>("x");

    zcalc::Expression exp {x};
    exp *= 3;

    zcalc::Expression exp2 {5};
    exp2 += 3;
    exp2 += 4;
    exp2 *= x;

    exp += exp2;

    x->set_value(5);

    std::complex<double> expected_result { 75.0, 0.0 };

    ASSERT_EQ(exp.evaluate(), expected_result);

    x->set_value(10);

    expected_result = std::complex<double> { 150.0, 0.0 };

    ASSERT_EQ(exp.evaluate(), expected_result);
}