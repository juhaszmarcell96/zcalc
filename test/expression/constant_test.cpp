#include <gtest/gtest.h>

#include <zcalc/expression/constant.hpp>

TEST(ConstantTest, ZeroTest) {
    zcalc::Constant c { zcalc::complex { 0.0, 0.0 } };

    ASSERT_EQ(c.get_value(), zcalc::complex(0.0, 0.0));
    ASSERT_TRUE(c.is_zero());
    ASSERT_FALSE(c.is_one());
}

TEST(ConstantTest, OneTest) {
    zcalc::Constant c { zcalc::complex { 1.0, 0.0 } };

    ASSERT_EQ(c.get_value(), zcalc::complex(1.0, 0.0));
    ASSERT_FALSE(c.is_zero());
    ASSERT_TRUE(c.is_one());
}

TEST(ConstantTest, CustomNumberTest) {
    zcalc::Constant c { zcalc::complex { 1.53, -12.89 } };

    ASSERT_EQ(c.get_value(), zcalc::complex(1.53, -12.89));
    ASSERT_FALSE(c.is_zero());
    ASSERT_FALSE(c.is_one());
}