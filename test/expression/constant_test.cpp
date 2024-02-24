#include <gtest/gtest.h>

#include <zcalc/expression/constant.hpp>

TEST(ConstantTest, ZeroTest) {
    zcalc::Constant c { zcalc::complex { 0.0, 0.0 } };

    ASSERT_TRUE(c.is_numeric());
    ASSERT_EQ(c.get(), zcalc::complex(0.0, 0.0));
    ASSERT_TRUE(c.is_zero());
    ASSERT_FALSE(c.is_one());
    ASSERT_EQ(c.to_string(), "(0.000000,0.000000)");
}

TEST(ConstantTest, OneTest) {
    zcalc::Constant c { zcalc::complex { 1.0, 0.0 } };

    ASSERT_TRUE(c.is_numeric());
    ASSERT_EQ(c.get(), zcalc::complex(1.0, 0.0));
    ASSERT_FALSE(c.is_zero());
    ASSERT_TRUE(c.is_one());
    ASSERT_EQ(c.to_string(), "(1.000000,0.000000)");
}

TEST(ConstantTest, CustomNumberTest) {
    zcalc::Constant c { zcalc::complex { 1.53, -12.89 } };

    ASSERT_TRUE(c.is_numeric());
    ASSERT_EQ(c.get(), zcalc::complex(1.53, -12.89));
    ASSERT_FALSE(c.is_zero());
    ASSERT_FALSE(c.is_one());
    ASSERT_EQ(c.to_string(), "(1.530000,-12.890000)");
}