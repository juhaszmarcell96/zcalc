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

TEST(MatrixTest, ConstructorInvalidDimensions) {
    ASSERT_THROW(zcalc::math::Matrix<double>(0, 3), std::invalid_argument);
    ASSERT_THROW(zcalc::math::Matrix<double>(3, 0), std::invalid_argument);
}

TEST(MatrixTest, ConstructorValidDimensions) {
    zcalc::math::Matrix<int> matrix(2, 3);
    ASSERT_EQ(matrix.get_num_rows(), 2);
    ASSERT_EQ(matrix.get_num_cols(), 3);
}

TEST(MatrixTest, ElementAccess) {
    zcalc::math::Matrix<int> matrix(2, 2);
    matrix(0, 0) = 42;
    matrix(1, 1) = 24;
    ASSERT_EQ(matrix(0, 0), 42);
    ASSERT_EQ(matrix(1, 1), 24);
}

TEST(MatrixTest, CopyAssignment) {
    zcalc::math::Matrix<int> matrix_0(2, 2);
    matrix_0(0, 0) = 1; matrix_0(1, 1) = 2;

    zcalc::math::Matrix<int> matrix_1 = matrix_0;
    ASSERT_EQ(matrix_1(0, 0), 1);
    ASSERT_EQ(matrix_1(1, 1), 2);
}

TEST(MatrixTest, EqualityAndInequalityOperators) {
    zcalc::math::Matrix<int> matrix_0(2, 2);
    zcalc::math::Matrix<int> matrix_1(2, 2);
    ASSERT_EQ(matrix_0, matrix_1);

    matrix_0(0, 0) = 1;
    ASSERT_NE(matrix_0, matrix_1);
}

TEST(MatrixTest, MatrixAddition) {
    zcalc::math::Matrix<int> matrix_0(2, 2);
    zcalc::math::Matrix<int> matrix_1(2, 2);
    matrix_0(0, 0) = 1; matrix_1(0, 0) = 2;

    zcalc::math::Matrix<int> result = matrix_0 + matrix_1;
    ASSERT_EQ(result(0, 0), 3);
}

TEST(MatrixTest, MatrixAdditionInvalidDimensions) {
    zcalc::math::Matrix<int> matrix_0(2, 2);
    zcalc::math::Matrix<int> matrix_1(3, 3);
    ASSERT_THROW(matrix_0 + matrix_1, std::invalid_argument);
}

TEST(MatrixTest, MatrixSubtraction) {
    zcalc::math::Matrix<int> matrix_0(2, 2);
    zcalc::math::Matrix<int> matrix_1(2, 2);
    matrix_0(0, 0) = 5; matrix_1(0, 0) = 3;

    zcalc::math::Matrix<int> result = matrix_0 - matrix_1;
    ASSERT_EQ(result(0, 0), 2);
}

TEST(MatrixTest, ScalarMultiplication) {
    zcalc::math::Matrix<int> matrix(2, 2);
    matrix(0, 0) = 2;

    zcalc::math::Matrix<int> result = matrix * 3;
    ASSERT_EQ(result(0, 0), 6);

    zcalc::math::Matrix<int> result2 = 3 * matrix;
    ASSERT_EQ(result2(0, 0), 6);
}

TEST(MatrixTest, ScalarDivision) {
    zcalc::math::Matrix<double> matrix(2, 2);
    matrix(0, 0) = 6.0;

    zcalc::math::Matrix<double> result = matrix / 3.0;
    ASSERT_EQ(result(0, 0), 2.0);
}

TEST(MatrixTest, MatrixMultiplication) {
    zcalc::math::Matrix<int> matrix_0(2, 3);
    matrix_0(0, 0) = 1; matrix_0(0, 1) = 2; matrix_0(0, 2) = 3;
    matrix_0(1, 0) = 4; matrix_0(1, 1) = 5; matrix_0(1, 2) = 6;

    zcalc::math::Matrix<int> matrix_1(3, 2);
    matrix_1(0, 0) = 7; matrix_1(0, 1) = 8;
    matrix_1(1, 0) = 9; matrix_1(1, 1) = 10;
    matrix_1(2, 0) = 11; matrix_1(2, 1) = 12;

    zcalc::math::Matrix<int> result = matrix_0 * matrix_1;

    ASSERT_EQ(result(0, 0), 58);
    ASSERT_EQ(result(0, 1), 64);
    ASSERT_EQ(result(1, 0), 139);
    ASSERT_EQ(result(1, 1), 154);
}

TEST(MatrixTest, MatrixMultiplicationInvalidDimensions) {
    zcalc::math::Matrix<int> matrix_0(2, 2);
    zcalc::math::Matrix<int> matrix_1(3, 3);
    ASSERT_THROW(matrix_0 * matrix_1, std::invalid_argument);
}