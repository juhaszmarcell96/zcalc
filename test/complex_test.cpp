#include <gtest/gtest.h>

#include <zcalc/internal/complex.hpp>

TEST(ComplexTest, SimpleTest) {
    zcalc::Complex c0 {5.0, 3.0};
    zcalc::Complex c1 {-2.0, 8.5};

    zcalc::Complex expected_result {-35.5, 36.5};

    ASSERT_EQ(c0 * c1, expected_result);

    zcalc::Complex c0_orig = c0;
    c0 += zcalc::Complex {zcalc::epsilon / 2.0, 0.0};

    ASSERT_EQ(c0, c0_orig);

    c0 += zcalc::Complex {zcalc::epsilon, 0.0};

    ASSERT_NE(c0, c0_orig);
}