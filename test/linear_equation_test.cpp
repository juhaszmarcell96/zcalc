#include <gtest/gtest.h>

#include <zcalc/math/complex.hpp>
#include <zcalc/math/linear_equation.hpp>

TEST(LinearEquationTest, SingleEquationTest) {
    /* 2x + y = 3 */
    zcalc::math::LinearEquation<int> eq {2};
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
    zcalc::math::LinearEquation<zcalc::math::Complex> eq_0 {2};
    eq_0.set_coefficient(0, zcalc::math::Complex{2.0, 0.0});
    eq_0.set_coefficient(1, zcalc::math::Complex{1.0, 0.0});
    eq_0.set_result(zcalc::math::Complex{3.0, 0.0});

    eq_0 *= zcalc::math::Complex{2.0, 0.0};

    /* 4x + 2y = 6 */
    ASSERT_EQ(eq_0.get_coefficient(0), zcalc::math::Complex(4.0, 0.0));
    ASSERT_EQ(eq_0.get_coefficient(1), zcalc::math::Complex(2.0, 0.0));
    ASSERT_EQ(eq_0.get_result(), zcalc::math::Complex(6.0, 0.0));

    /* 0.5x + 0.5y = 2 */
    zcalc::math::LinearEquation<zcalc::math::Complex> eq_1 {2};
    eq_1.set_coefficient(0, zcalc::math::Complex{0.5, 0.0});
    eq_1.set_coefficient(1, zcalc::math::Complex{0.5, 0.0});
    eq_1.set_result(zcalc::math::Complex{2.0, 0.0});

    zcalc::math::LinearEquation<zcalc::math::Complex> result = eq_0 / zcalc::math::Complex(2.0, 0.0) + eq_1 * zcalc::math::Complex(2.0, 0.0);

    /* 3x + 2y = 7 */
    ASSERT_EQ(result.get_coefficient(0), zcalc::math::Complex(3.0, 0.0));
    ASSERT_EQ(result.get_coefficient(1), zcalc::math::Complex(2.0, 0.0));
    ASSERT_EQ(result.get_result(), zcalc::math::Complex(7.0, 0.0));
}