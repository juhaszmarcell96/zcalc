#include <gtest/gtest.h>

#include <zcalc/expression/variable.hpp>
#include <zcalc/expression/variable_pool.hpp>

#include <sstream>

TEST(VariableTest, Test) {
    zcalc::Variable v { "x" };

    std::stringstream ss;
    v.print(ss);
    ASSERT_EQ(ss.str(), "x");

    ASSERT_FALSE(v.is_numeric());
    EXPECT_THROW(v.get_value(), std::runtime_error);
    EXPECT_THROW(v.is_zero(), std::runtime_error);
    EXPECT_THROW(v.is_one(), std::runtime_error);

    v.set_value(zcalc::complex{0.0, 0.0});
    ASSERT_TRUE(v.is_numeric());
    ASSERT_EQ(v.get_value(), zcalc::complex(0.0, 0.0));
    ASSERT_TRUE(v.is_zero());
    ASSERT_FALSE(v.is_one());

    v.unset_value();
    ASSERT_FALSE(v.is_numeric());
    EXPECT_THROW(v.get_value(), std::runtime_error);
    EXPECT_THROW(v.is_zero(), std::runtime_error);
    EXPECT_THROW(v.is_one(), std::runtime_error);

    v.set_value(zcalc::complex{1.0, 0.0});
    ASSERT_TRUE(v.is_numeric());
    ASSERT_EQ(v.get_value(), zcalc::complex(1.0, 0.0));
    ASSERT_FALSE(v.is_zero());
    ASSERT_TRUE(v.is_one());

    v.set_value(zcalc::complex{-0.6, 1.12});
    ASSERT_TRUE(v.is_numeric());
    ASSERT_EQ(v.get_value(), zcalc::complex(-0.6, 1.12));
    ASSERT_FALSE(v.is_zero());
    ASSERT_FALSE(v.is_one());

    zcalc::VariablePool::undefine_variable("x");
}