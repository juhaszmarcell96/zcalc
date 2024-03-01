#include <gtest/gtest.h>

#include <zcalc/expression/operation.hpp>
#include <zcalc/expression/constant.hpp>

TEST(OperationTest, EmptyOpTest) {
    zcalc::Operation op { zcalc::operation_types::add };

    ASSERT_FALSE(op.is_numeric());
    EXPECT_THROW(op.reduce(), std::runtime_error);
    EXPECT_THROW(op.is_zero(), std::runtime_error);
    EXPECT_THROW(op.is_one(), std::runtime_error);
    EXPECT_THROW(op.get(), std::runtime_error);
}

TEST(OperationTest, ConstantOpTest) {
    zcalc::Operation op { zcalc::operation_types::add };
    std::shared_ptr<zcalc::Constant> c1 = std::make_shared<zcalc::Constant>(zcalc::complex { 1.0, 0.0 });
    std::shared_ptr<zcalc::Constant> c2 = std::make_shared<zcalc::Constant>(zcalc::complex { 2.0, 0.0 });

    op.set_left_operand(c1);
    op.set_right_operand(c2);

    ASSERT_TRUE(op.is_numeric());
    ASSERT_FALSE(op.is_zero());
    ASSERT_FALSE(op.is_one());
    ASSERT_EQ(op.get(), zcalc::complex(3.0, 0.0));
}