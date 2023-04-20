#include <gtest/gtest.h>

#include <include/matrix.hpp>

#include <complex>

TEST(MatrixTest, MatrixAdditionTest) {
    zcalc::Matrix<std::complex<double>> matrix_0 {3, 3};
    matrix_0(1, 2) = {1.0, 1.0};
    zcalc::Matrix<std::complex<double>> matrix_1 {3, 3};
    matrix_1(1, 2) = {1.0, 1.0};

    zcalc::Matrix<std::complex<double>> result = matrix_0 + matrix_1;

    zcalc::Matrix<std::complex<double>> expected_result {3, 3};
    expected_result(0, 0) = {0.0, 0.0}; expected_result(0, 1) = {0.0, 0.0}; expected_result(0, 2) = {0.0, 0.0};
    expected_result(1, 0) = {0.0, 0.0}; expected_result(1, 1) = {0.0, 0.0}; expected_result(1, 2) = {2.0, 2.0};
    expected_result(2, 0) = {0.0, 0.0}; expected_result(2, 1) = {0.0, 0.0}; expected_result(2, 2) = {0.0, 0.0};

    ASSERT_EQ(result, expected_result);

    expected_result(0, 0) = {1.0, 0.0};
    ASSERT_NE(result, expected_result);
}

TEST(MatrixTest, MatrixMultiplicationTest) {
    zcalc::Matrix<double> matrix_0 {2, 3};
    matrix_0(0, 0) = 1.0; matrix_0(0, 1) = 2.0; matrix_0(0, 2) = 3.0;
    matrix_0(1, 0) = 4.0; matrix_0(1, 1) = 5.0; matrix_0(1, 2) = 6.0;

    zcalc::Matrix<double> matrix_1 {3, 1};
    matrix_1(0, 0) = 1.0;
    matrix_1(1, 0) = 2.0;
    matrix_1(2, 0) = 3.0;

    zcalc::Matrix<double> result = matrix_0 * matrix_1;

    zcalc::Matrix<double> expected_result {2, 1};
    expected_result(0, 0) = 14.0;
    expected_result(1, 0) = 32.0;

    ASSERT_EQ(result, expected_result);
}

TEST(MatrixTest, MatrixEliminationTest) {
    /* no solution */
    zcalc::Matrix<double> matrix {4, 4};
    matrix(0, 0) = 1.0; matrix(0, 1) = 2.0; matrix(0, 2) = 1.0; matrix(0, 3) = 1.0;
    matrix(1, 0) = 2.0; matrix(1, 1) = 3.0; matrix(1, 2) = 2.0; matrix(1, 3) = 1.0;
    matrix(2, 0) = 3.0; matrix(2, 1) = 3.0; matrix(2, 2) = 2.0; matrix(2, 3) = 0.0;
    matrix(3, 0) = 1.0; matrix(3, 1) = 1.0; matrix(3, 2) = 2.0; matrix(3, 3) = 1.0;

    std::vector<double> result;
    bool success = matrix.solve_system_of_linear_equations(result);

    ASSERT_EQ(false, success);

    /* solution should be found */
    /*  2x + 0y + 1z =  3 */
    /*  4x + 2y + 1z =  3 */
    /* -2x + 8y + 2z = -8 */
    zcalc::Matrix<double> matrix_1 {3, 4};
    matrix_1(0, 0) =  2.0; matrix_1(0, 1) = 0.0; matrix_1(0, 2) = 1.0; matrix_1(0, 3) = 3.0;
    matrix_1(1, 0) =  4.0; matrix_1(1, 1) = 2.0; matrix_1(1, 2) = 1.0; matrix_1(1, 3) = 3.0;
    matrix_1(2, 0) = -2.0; matrix_1(2, 1) = 8.0; matrix_1(2, 2) = 2.0; matrix_1(2, 3) = -8.0;

    success = matrix_1.solve_system_of_linear_equations(result);

    ASSERT_EQ(true, success);
    ASSERT_EQ( 1.0, result[0]);
    ASSERT_EQ(-1.0, result[1]);
    ASSERT_EQ( 1.0, result[2]);

    /* no solution */
    /*  1x + 1y +   2z =  3 */
    /*  2x + 2y +   5z = -4 */
    /*  5x + 5y + -11z =  6 */
    zcalc::Matrix<double> matrix_2 {3, 4};
    matrix_2(0, 0) =  1.0; matrix_2(0, 1) = 1.0; matrix_2(0, 2) =   2.0; matrix_2(0, 3) =  3.0;
    matrix_2(1, 0) =  2.0; matrix_2(1, 1) = 2.0; matrix_2(1, 2) =   5.0; matrix_2(1, 3) = -4.0;
    matrix_2(2, 0) =  5.0; matrix_2(2, 1) = 5.0; matrix_2(2, 2) = -11.0; matrix_2(2, 3) =  6.0;

    success = matrix_2.solve_system_of_linear_equations(result);

    ASSERT_EQ(false, success);

    /* infinite solutions */
    zcalc::Matrix<double> matrix_3 {3, 4};
    matrix_3(0, 0) =  2.0; matrix_3(0, 1) =  1.0; matrix_3(0, 2) =  -3.0; matrix_3(0, 3) =  1.0;
    matrix_3(1, 0) =  4.0; matrix_3(1, 1) =  2.0; matrix_3(1, 2) =  -6.0; matrix_3(1, 3) =  2.0;
    matrix_3(2, 0) = -8.0; matrix_3(2, 1) = -4.0; matrix_3(2, 2) = -12.0; matrix_3(2, 3) = -4.0;

    success = matrix_3.solve_system_of_linear_equations(result);

    ASSERT_EQ(false, success);

    /* solution should be found */
    /*  2x + 1y +  3z =  1 */
    /*  2x + 6y +  8z =  3 */
    /*  6x + 8y + 18z =  5 */
    zcalc::Matrix<double> matrix_4 {3, 4};
    matrix_4(0, 0) = 2.0; matrix_4(0, 1) = 1.0; matrix_4(0, 2) =  3.0; matrix_4(0, 3) = 1.0;
    matrix_4(1, 0) = 2.0; matrix_4(1, 1) = 6.0; matrix_4(1, 2) =  8.0; matrix_4(1, 3) = 3.0;
    matrix_4(2, 0) = 6.0; matrix_4(2, 1) = 8.0; matrix_4(2, 2) = 18.0; matrix_4(2, 3) = 5.0;

    success = matrix_4.solve_system_of_linear_equations(result);

    ASSERT_EQ(true, success);
    ASSERT_EQ(3.0/10.0, result[0]);
    ASSERT_EQ(2.0/5.0, result[1]);
    ASSERT_EQ(0.0, result[2]);
}