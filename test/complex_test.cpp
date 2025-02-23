#include <gtest/gtest.h>

#include <zcalc/math/complex.hpp>

namespace zcalc::math {

const double comparison_epsilon = 1e-9; // Define a small epsilon for floating-point comparisons

TEST(ComplexTest, SimpleTest) {
    zcalc::math::Complex c0 {5.0, 3.0};
    zcalc::math::Complex c1 {-2.0, 8.5};

    zcalc::math::Complex expected_result {-35.5, 36.5};

    ASSERT_EQ(c0 * c1, expected_result);

    zcalc::math::Complex c0_orig = c0;
    c0 += zcalc::math::Complex {zcalc::epsilon / 2.0, 0.0};

    ASSERT_EQ(c0, c0_orig);

    c0 += zcalc::math::Complex {zcalc::epsilon, 0.0};

    ASSERT_NE(c0, c0_orig);
}

TEST(ComplexTest, ConstructorTests) {
    Complex c1;
    ASSERT_EQ(c1.real(), 0.0);
    ASSERT_EQ(c1.imag(), 0.0);

    Complex c2(3.5, -2.5);
    ASSERT_EQ(c2.real(), 3.5);
    ASSERT_EQ(c2.imag(), -2.5);

    Complex c3(4.0);
    ASSERT_EQ(c3.real(), 4.0);
    ASSERT_EQ(c3.imag(), 0.0);

    Complex c4(2, 3);
    ASSERT_EQ(c4.real(), 2);
    ASSERT_EQ(c4.imag(), 3);
}

TEST(ComplexTest, UnaryOperators) {
    Complex c(3.0, -4.0);
    Complex neg_c = -c;
    ASSERT_EQ(neg_c.real(), -3.0);
    ASSERT_EQ(neg_c.imag(), 4.0);
    
    Complex pos_c = +c;
    ASSERT_EQ(pos_c.real(), 3.0);
    ASSERT_EQ(pos_c.imag(), -4.0);
}

TEST(ComplexTest, ArithmeticOperations) {
    Complex c1(1.0, 2.0);
    Complex c2(3.0, 4.0);
    Complex sum = c1 + c2;
    ASSERT_EQ(sum.real(), 4.0);
    ASSERT_EQ(sum.imag(), 6.0);

    Complex diff = c1 - c2;
    ASSERT_EQ(diff.real(), -2.0);
    ASSERT_EQ(diff.imag(), -2.0);

    Complex prod = c1 * c2;
    ASSERT_EQ(prod.real(), -5.0);
    ASSERT_EQ(prod.imag(), 10.0);

    Complex quot = c1 / c2;
    ASSERT_NEAR(quot.real(), 0.44, comparison_epsilon);
    ASSERT_NEAR(quot.imag(), 0.08, comparison_epsilon);
}

TEST(ComplexTest, CompoundAssignmentOperators) {
    Complex c1(1.0, 2.0);
    Complex c2(3.0, 4.0);
    
    c1 += c2;
    ASSERT_EQ(c1.real(), 4.0);
    ASSERT_EQ(c1.imag(), 6.0);

    c1 -= c2;
    ASSERT_EQ(c1.real(), 1.0);
    ASSERT_EQ(c1.imag(), 2.0);

    c1 *= c2;
    ASSERT_EQ(c1.real(), -5.0);
    ASSERT_EQ(c1.imag(), 10.0);

    c1 /= c2;
    ASSERT_NEAR(c1.real(), 1.0, comparison_epsilon);
    ASSERT_NEAR(c1.imag(), 2.0, comparison_epsilon);
}

TEST(ComplexTest, ComparisonOperators) {
    Complex c1(1.0, 2.0);
    Complex c2(1.0 + epsilon / 2.0, 2.0);
    Complex c3(1.0 + epsilon * 4.0, 2.0);
    
    ASSERT_EQ(c1, c2);
    ASSERT_NE(c1, c3);
}

TEST(ComplexTest, MagnitudeAndPhase) {
    Complex c(3.0, 4.0);
    ASSERT_EQ(c.abs(), 5.0);
    ASSERT_NEAR(c.arg(), atan2(4.0, 3.0), comparison_epsilon);
}

TEST(ComplexTest, StreamOperator) {
    Complex c(2.0, -3.0);
    std::ostringstream oss;
    oss << c;
    ASSERT_EQ(oss.str(), "(2-j3)");
}

TEST(ComplexTest, EdgeCases) {
    Complex zero(0.0, 0.0);
    ASSERT_EQ(zero.abs(), 0.0);
    ASSERT_EQ(zero.arg(), 0.0);

    Complex purelyReal(5.0, 0.0);
    ASSERT_EQ(purelyReal.arg(), 0.0);

    Complex purelyImaginary(0.0, 5.0);
    ASSERT_NEAR(purelyImaginary.arg(), M_PI_2, comparison_epsilon);

    Complex negativeReal(-5.0, 0.0);
    ASSERT_NEAR(negativeReal.arg(), M_PI, comparison_epsilon);
}

} // namespace zcalc::math