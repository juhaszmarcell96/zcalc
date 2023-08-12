#include <gtest/gtest.h>

#include <zcalc/internal/fraction.hpp>

TEST(FractionText, FractionConstructorTest) {
    zcalc::Fraction f0 {0.1};
    zcalc::Fraction f1 {123.4};
    zcalc::Fraction f3 {1e-12};

    ASSERT_EQ(f0, zcalc::Fraction(1, 10));
    ASSERT_EQ(f1, zcalc::Fraction(617, 5));
    ASSERT_EQ(f3, zcalc::Fraction(1, 1000000000000));

    ASSERT_EQ(f0.evaluate(), 0.1);
    ASSERT_EQ(f1.evaluate(), 123.4);
    ASSERT_EQ(f3.evaluate(), 1e-12);
}

TEST(FractionText, FractionOperationTest) {
    zcalc::Fraction f0 {1, 3};
    zcalc::Fraction f1 {-3, 4};

    ASSERT_EQ(f0 + f1, zcalc::Fraction(-5, 12));
    ASSERT_EQ(f0 - f1, zcalc::Fraction(13, 12));
    ASSERT_EQ(f0 * f1, zcalc::Fraction(-1, 4));
    ASSERT_EQ(f0 / f1, zcalc::Fraction(-4, 9));

    f0 += f1;

    ASSERT_EQ(f0, zcalc::Fraction(-5, 12));

    f0 -= f1;

    ASSERT_EQ(f0, zcalc::Fraction(1, 3));

    f0 *= f1;

    ASSERT_EQ(f0, zcalc::Fraction(-1, 4));

    f0 /= f1;

    ASSERT_EQ(f0, zcalc::Fraction(1, 3));

    ASSERT_EQ(f0 == f1, false);
    ASSERT_EQ(f0 == f0, true);
}