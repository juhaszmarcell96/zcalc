#include <gtest/gtest.h>

#include <zcalc/math/complex.hpp>
#include <zcalc/math/linear_equation.hpp>

using namespace zcalc::math;

TEST(LinearEquationTest, SingleEquationTest) {
    /* 2x + y = 3 */
    LinearEquation<int> eq {2};
    eq.set_coefficient(0, 2);
    eq.set_coefficient(1, 1);
    eq.set_result(3);

    eq *= 2;

    ASSERT_EQ(eq.get_coefficient(0), 4);
    ASSERT_EQ(eq.get_coefficient(1), 2);
    ASSERT_EQ(eq.get_result(), 6);

    eq /= 2;

    ASSERT_EQ(eq.get_coefficient(0), 2);
    ASSERT_EQ(eq.get_coefficient(1), 1);
    ASSERT_EQ(eq.get_result(), 3);
}

TEST(LinearEquationTest, ComplexEquationTest) {
    /* 2x + y = 3 */
    LinearEquation<Complex> eq_0 {2};
    eq_0.set_coefficient(0, Complex{2.0, 0.0});
    eq_0.set_coefficient(1, Complex{1.0, 0.0});
    eq_0.set_result(Complex{3.0, 0.0});

    eq_0 *= Complex{2.0, 0.0};

    /* 4x + 2y = 6 */
    ASSERT_EQ(eq_0.get_coefficient(0), Complex(4.0, 0.0));
    ASSERT_EQ(eq_0.get_coefficient(1), Complex(2.0, 0.0));
    ASSERT_EQ(eq_0.get_result(), Complex(6.0, 0.0));

    /* 0.5x + 0.5y = 2 */
    LinearEquation<Complex> eq_1 {2};
    eq_1.set_coefficient(0, Complex{0.5, 0.0});
    eq_1.set_coefficient(1, Complex{0.5, 0.0});
    eq_1.set_result(Complex{2.0, 0.0});

    LinearEquation<Complex> result = eq_0 / Complex(2.0, 0.0) + eq_1 * Complex(2.0, 0.0);

    /* 3x + 2y = 7 */
    ASSERT_EQ(result.get_coefficient(0), Complex(3.0, 0.0));
    ASSERT_EQ(result.get_coefficient(1), Complex(2.0, 0.0));
    ASSERT_EQ(result.get_result(), Complex(7.0, 0.0));
}

TEST(LinearEquationTest, ConstructorInitializesCorrectly) {
    LinearEquation<double> eq(3, "TestEq");
    EXPECT_EQ(eq.get_num_variables(), 3);
    EXPECT_EQ(eq.get_result(), 0.0);
    EXPECT_TRUE(eq.is_full_zero());
}

TEST(LinearEquationTest, SetAndGetCoefficient) {
    LinearEquation<double> eq(3);
    eq.set_coefficient(1, 5.0);
    EXPECT_DOUBLE_EQ(eq.get_coefficient(1), 5.0);
}

TEST(LinearEquationTest, SetAndGetResult) {
    LinearEquation<double> eq(3);
    eq.set_result(10.0);
    EXPECT_DOUBLE_EQ(eq.get_result(), 10.0);
}

TEST(LinearEquationTest, IsZeroFunction) {
    LinearEquation<double> eq(3);
    EXPECT_TRUE(eq.is_full_zero());
    eq.set_coefficient(1, 2.0);
    EXPECT_FALSE(eq.is_zero());
    eq.set_coefficient(1, 0.0);
    EXPECT_TRUE(eq.is_zero());
}

TEST(LinearEquationTest, AdditionOperator) {
    LinearEquation<double> eq1(2);
    LinearEquation<double> eq2(2);
    eq1.set_coefficient(0, 1.0);
    eq1.set_coefficient(1, 2.0);
    eq1.set_result(3.0);
    eq2.set_coefficient(0, 4.0);
    eq2.set_coefficient(1, 5.0);
    eq2.set_result(6.0);
    
    LinearEquation<double> sum = eq1 + eq2;
    EXPECT_DOUBLE_EQ(sum.get_coefficient(0), 5.0);
    EXPECT_DOUBLE_EQ(sum.get_coefficient(1), 7.0);
    EXPECT_DOUBLE_EQ(sum.get_result(), 9.0);
}

TEST(LinearEquationTest, SubtractionOperator) {
    LinearEquation<double> eq1(2);
    LinearEquation<double> eq2(2);
    eq1.set_coefficient(0, 5.0);
    eq1.set_coefficient(1, 6.0);
    eq1.set_result(7.0);
    eq2.set_coefficient(0, 1.0);
    eq2.set_coefficient(1, 2.0);
    eq2.set_result(3.0);
    
    LinearEquation<double> diff = eq1 - eq2;
    EXPECT_DOUBLE_EQ(diff.get_coefficient(0), 4.0);
    EXPECT_DOUBLE_EQ(diff.get_coefficient(1), 4.0);
    EXPECT_DOUBLE_EQ(diff.get_result(), 4.0);
}

TEST(LinearEquationTest, MultiplicationOperator) {
    LinearEquation<double> eq(2);
    eq.set_coefficient(0, 2.0);
    eq.set_coefficient(1, 3.0);
    eq.set_result(4.0);
    
    LinearEquation<double> product = eq * 2.0;
    EXPECT_DOUBLE_EQ(product.get_coefficient(0), 4.0);
    EXPECT_DOUBLE_EQ(product.get_coefficient(1), 6.0);
    EXPECT_DOUBLE_EQ(product.get_result(), 8.0);
}

TEST(LinearEquationTest, DivisionOperator) {
    LinearEquation<double> eq(2);
    eq.set_coefficient(0, 6.0);
    eq.set_coefficient(1, 8.0);
    eq.set_result(10.0);
    
    LinearEquation<double> quotient = eq / 2.0;
    EXPECT_DOUBLE_EQ(quotient.get_coefficient(0), 3.0);
    EXPECT_DOUBLE_EQ(quotient.get_coefficient(1), 4.0);
    EXPECT_DOUBLE_EQ(quotient.get_result(), 5.0);
}

TEST(LinearEquationTest, DivisionByZeroThrows) {
    LinearEquation<double> eq(2);
    eq.set_coefficient(0, 6.0);
    eq.set_coefficient(1, 8.0);
    eq.set_result(10.0);
    
    EXPECT_THROW(eq / 0.0, std::invalid_argument);
}

TEST(LinearEquationTest, GetFirstNonZeroIndex) {
    LinearEquation<double> eq(3);
    eq.set_coefficient(0, 0.0);
    eq.set_coefficient(1, 3.0);
    eq.set_coefficient(2, 5.0);
    EXPECT_EQ(eq.get_first_nonzero_coeff_index(), 1);
}

TEST(LinearEquationTest, StreamingOperator) {
    LinearEquation<double> eq(2, "Equation1");
    eq.set_coefficient(0, 1.5);
    eq.set_coefficient(1, -2.0);
    eq.set_result(3.0);
    
    std::ostringstream os;
    os << eq;
    EXPECT_EQ(os.str(), "Equation1,1.5,-2,3");
}