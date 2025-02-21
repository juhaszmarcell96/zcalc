#include <gtest/gtest.h>

#include <zcalc/math/matrix.hpp>

TEST(MatrixTest, MatrixAdditionTest) {
    zcalc::math::Matrix<std::complex<double>> matrix_0 {3, 3};
    matrix_0(1, 2) = {1.0, 1.0};
    zcalc::math::Matrix<std::complex<double>> matrix_1 {3, 3};
    matrix_1(1, 2) = {1.0, 1.0};

    zcalc::math::Matrix<std::complex<double>> result = matrix_0 + matrix_1;

    zcalc::math::Matrix<std::complex<double>> expected_result {3, 3};
    expected_result(0, 0) = {0.0, 0.0}; expected_result(0, 1) = {0.0, 0.0}; expected_result(0, 2) = {0.0, 0.0};
    expected_result(1, 0) = {0.0, 0.0}; expected_result(1, 1) = {0.0, 0.0}; expected_result(1, 2) = {2.0, 2.0};
    expected_result(2, 0) = {0.0, 0.0}; expected_result(2, 1) = {0.0, 0.0}; expected_result(2, 2) = {0.0, 0.0};

    ASSERT_EQ(result, expected_result);

    expected_result(0, 0) = {1.0, 0.0};
    ASSERT_NE(result, expected_result);
}

TEST(MatrixTest, MatrixMultiplicationTest) {
    zcalc::math::Matrix<double> matrix_0 {2, 3};
    matrix_0(0, 0) = 1.0; matrix_0(0, 1) = 2.0; matrix_0(0, 2) = 3.0;
    matrix_0(1, 0) = 4.0; matrix_0(1, 1) = 5.0; matrix_0(1, 2) = 6.0;

    zcalc::math::Matrix<double> matrix_1 {3, 1};
    matrix_1(0, 0) = 1.0;
    matrix_1(1, 0) = 2.0;
    matrix_1(2, 0) = 3.0;

    zcalc::math::Matrix<double> result = matrix_0 * matrix_1;

    zcalc::math::Matrix<double> expected_result {2, 1};
    expected_result(0, 0) = 14.0;
    expected_result(1, 0) = 32.0;

    ASSERT_EQ(result, expected_result);
}