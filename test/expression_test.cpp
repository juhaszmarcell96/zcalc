#include <gtest/gtest.h>

#include <include/expression.hpp>

TEST(ExpressionTest, SimpleExpression) {
    zcalc::Expression exp {zcalc::Complex{5.0, 0.0}};
    exp += 3;
    exp += 2;
    exp /= 5;

    zcalc::Complex expected_result { 2.0, 0.0 };

    ASSERT_EQ(exp.evaluate(), expected_result);
}

TEST(ExpressionTest, VariableTest) {
    std::shared_ptr<zcalc::Variable> x = std::make_shared<zcalc::Variable>("x");

    zcalc::Expression exp {x};
    exp *= 3;
    exp += 5;

    x->set_value(zcalc::Complex{5.0, 0.0});

    zcalc::Complex expected_result { 20.0, 0.0 };

    ASSERT_EQ(exp.evaluate(), expected_result);
}

TEST(ExpressionTest, MultipleExpressions) {
    std::shared_ptr<zcalc::Variable> x = std::make_shared<zcalc::Variable>("x");

    zcalc::Expression exp {x};
    exp *= 3;

    zcalc::Expression exp2 {zcalc::Complex{5.0, 0.0}};
    exp2 += 3;
    exp2 += 4;
    exp2 *= x;

    exp += exp2;

    x->set_value(zcalc::Complex{5.0, 0.0});

    zcalc::Complex expected_result { 75.0, 0.0 };

    ASSERT_EQ(exp.evaluate(), expected_result);

    x->set_value(10);

    expected_result = zcalc::Complex { 150.0, 0.0 };

    ASSERT_EQ(exp.evaluate(), expected_result);
}