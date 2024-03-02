#include <gtest/gtest.h>

#include <zcalc/expression/expression.hpp>

TEST(ConstantRuleTest, SimplifyTest) {

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