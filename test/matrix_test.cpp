#include <gtest/gtest.h>

#include <include/matrix.hpp>

#include <complex>

TEST(MatrixTest, MatrixAdditionTest) {
    std::complex<double> zero_value { 0.0, 0.0 };
    zcalc::Expression zero_exp {zero_value};

    zcalc::Matrix matrix_0 {3, 3, zero_exp};
    matrix_0(1, 2) = zcalc::Expression{{1.0, 1.0}};
    zcalc::Matrix matrix_1 {3, 3, zero_exp};
    matrix_1(1, 2) = zcalc::Expression{{1.0, 1.0}};

    zcalc::Matrix result = matrix_0 + matrix_1;

    ASSERT_EQ(result[0][0].evaluate(), zero_value);
    ASSERT_EQ(result[0][1].evaluate(), zero_value);
    ASSERT_EQ(result[0][2].evaluate(), zero_value);
    ASSERT_EQ(result[1][0].evaluate(), zero_value);
    ASSERT_EQ(result[1][1].evaluate(), zero_value);
    ASSERT_EQ(result[1][2].evaluate(), std::complex<double>(2.0, 2.0));
    ASSERT_EQ(result[2][0].evaluate(), zero_value);
    ASSERT_EQ(result[2][1].evaluate(), zero_value);
    ASSERT_EQ(result[2][2].evaluate(), zero_value);
}

TEST(MatrixTest, MatrixMultiplicationTest) {
    std::complex<double> zero_value { 0.0, 0.0 };
    zcalc::Expression zero_exp {zero_value};

    zcalc::Matrix matrix_0 {2, 3, zero_exp};
    matrix_0(0, 0) = zcalc::Expression{{1.0, 0.0}};
    matrix_0(0, 1) = zcalc::Expression{{2.0, 0.0}};
    matrix_0(0, 2) = zcalc::Expression{{3.0, 0.0}};
    matrix_0(1, 0) = zcalc::Expression{{4.0, 0.0}};
    matrix_0(1, 1) = zcalc::Expression{{5.0, 0.0}};
    matrix_0(1, 2) = zcalc::Expression{{6.0, 0.0}};

    zcalc::Matrix matrix_1 {3, 1, zero_value};
    matrix_1(0, 0) = zcalc::Expression{{1.0, 0.0}};
    matrix_1(1, 0) = zcalc::Expression{{2.0, 0.0}};
    matrix_1(2, 0) = zcalc::Expression{{3.0, 0.0}};

    zcalc::Matrix result = matrix_0 * matrix_1;
    
    ASSERT_EQ(result.get_num_rows(), 2);
    ASSERT_EQ(result.get_num_cols(), 1);
    
    ASSERT_EQ(result[0][0].evaluate(), std::complex<double>(14.0, 0.0));
    ASSERT_EQ(result[1][0].evaluate(), std::complex<double>(32.0, 0.0));
}

TEST(MatrixTest, MatrixEliminationTest) {
    std::complex<double> zero_value { 0.0, 0.0 };
    zcalc::Expression zero_exp {zero_value};

    std::vector<zcalc::Expression> result;
    bool success = false;

    /* no solution */
    zcalc::Matrix matrix {4, 4, zero_exp};
    matrix(0, 0) = zcalc::Expression{{1.0, 0.0}};
    matrix(0, 1) = zcalc::Expression{{2.0, 0.0}};
    matrix(0, 2) = zcalc::Expression{{1.0, 0.0}};
    matrix(0, 3) = zcalc::Expression{{1.0, 0.0}};

    matrix(1, 0) = zcalc::Expression{{2.0, 0.0}};
    matrix(1, 1) = zcalc::Expression{{3.0, 0.0}};
    matrix(1, 2) = zcalc::Expression{{2.0, 0.0}};
    matrix(1, 3) = zcalc::Expression{{1.0, 0.0}};

    matrix(2, 0) = zcalc::Expression{{3.0, 0.0}};
    matrix(2, 1) = zcalc::Expression{{3.0, 0.0}};
    matrix(2, 2) = zcalc::Expression{{2.0, 0.0}};
    matrix(2, 3) = zcalc::Expression{{0.0, 0.0}};

    matrix(3, 0) = zcalc::Expression{{1.0, 0.0}};
    matrix(3, 1) = zcalc::Expression{{1.0, 0.0}};
    matrix(3, 2) = zcalc::Expression{{2.0, 0.0}};
    matrix(3, 3) = zcalc::Expression{{1.0, 0.0}};

    success = matrix.solve_system_of_linear_equations(result);

    ASSERT_EQ(false, success);

    /* solution should be found */
    /*  2x + 0y + 1z =  3 */
    /*  4x + 2y + 1z =  3 */
    /* -2x + 8y + 2z = -8 */
    zcalc::Matrix matrix_1 {3, 4, zero_exp};
    matrix_1(0, 0) = zcalc::Expression{{2.0, 0.0}};
    matrix_1(0, 1) = zcalc::Expression{{0.0, 0.0}};
    matrix_1(0, 2) = zcalc::Expression{{1.0, 0.0}};
    matrix_1(0, 3) = zcalc::Expression{{3.0, 0.0}};

    matrix_1(1, 0) = zcalc::Expression{{4.0, 0.0}};
    matrix_1(1, 1) = zcalc::Expression{{2.0, 0.0}};
    matrix_1(1, 2) = zcalc::Expression{{1.0, 0.0}};
    matrix_1(1, 3) = zcalc::Expression{{3.0, 0.0}};

    matrix_1(2, 0) = zcalc::Expression{{-2.0, 0.0}};
    matrix_1(2, 1) = zcalc::Expression{{8.0, 0.0}};
    matrix_1(2, 2) = zcalc::Expression{{2.0, 0.0}};;
    matrix_1(2, 3) = zcalc::Expression{{-8.0, 0.0}};

    success = matrix_1.solve_system_of_linear_equations(result);

    ASSERT_EQ(true, success);
    ASSERT_EQ(result[0].evaluate(), std::complex<double>(1.0, 0.0));
    ASSERT_EQ(result[1].evaluate(), std::complex<double>(-1.0, 0.0));
    ASSERT_EQ(result[2].evaluate(), std::complex<double>(1.0, 0.0));

    /* no solution */
    /*  1x + 1y +   2z =  3 */
    /*  2x + 2y +   5z = -4 */
    /*  5x + 5y + -11z =  6 */
    zcalc::Matrix matrix_2 {3, 4, zero_exp};
    matrix_2(0, 0) = zcalc::Expression{{1.0, 0.0}};
    matrix_2(0, 1) = zcalc::Expression{{1.0, 0.0}};
    matrix_2(0, 2) = zcalc::Expression{{2.0, 0.0}};
    matrix_2(0, 3) = zcalc::Expression{{3.0, 0.0}};

    matrix_2(1, 0) = zcalc::Expression{{2.0, 0.0}};
    matrix_2(1, 1) = zcalc::Expression{{2.0, 0.0}};
    matrix_2(1, 2) = zcalc::Expression{{5.0, 0.0}};
    matrix_2(1, 3) = zcalc::Expression{{-4.0, 0.0}};

    matrix_2(2, 0) = zcalc::Expression{{5.0, 0.0}};
    matrix_2(2, 1) = zcalc::Expression{{5.0, 0.0}};
    matrix_2(2, 2) = zcalc::Expression{{-11.0, 0.0}};
    matrix_2(2, 3) = zcalc::Expression{{6.0, 0.0}};

    success = matrix_2.solve_system_of_linear_equations(result);

    ASSERT_EQ(false, success);

    /* infinite solutions */
    zcalc::Matrix matrix_3 {3, 4, zero_exp};
    matrix_3(0, 0) = zcalc::Expression{{2.0, 0.0}};
    matrix_3(0, 1) = zcalc::Expression{{1.0, 0.0}};
    matrix_3(0, 2) = zcalc::Expression{{-3.0, 0.0}};
    matrix_3(0, 3) = zcalc::Expression{{1.0, 0.0}};

    matrix_3(1, 0) = zcalc::Expression{{4.0, 0.0}};
    matrix_3(1, 1) = zcalc::Expression{{2.0, 0.0}};
    matrix_3(1, 2) = zcalc::Expression{{-6.0, 0.0}};
    matrix_3(1, 3) = zcalc::Expression{{2.0, 0.0}};

    matrix_3(2, 0) = zcalc::Expression{{-8.0, 0.0}};
    matrix_3(2, 1) = zcalc::Expression{{-4.0, 0.0}};
    matrix_3(2, 2) = zcalc::Expression{{-12.0, 0.0}};
    matrix_3(2, 3) = zcalc::Expression{{-4.0, 0.0}};

    success = matrix_3.solve_system_of_linear_equations(result);

    ASSERT_EQ(false, success);

    /* solution should be found */
    /*  2x + 1y +  3z =  1 */
    /*  2x + 6y +  8z =  3 */
    /*  6x + 8y + 18z =  5 */
    zcalc::Matrix matrix_4 {3, 4, zero_exp};
    matrix_4(0, 0) = zcalc::Expression{{2.0, 0.0}};
    matrix_4(0, 1) = zcalc::Expression{{1.0, 0.0}};
    matrix_4(0, 2) = zcalc::Expression{{3.0, 0.0}};
    matrix_4(0, 3) = zcalc::Expression{{1.0, 0.0}};

    matrix_4(1, 0) = zcalc::Expression{{2.0, 0.0}};
    matrix_4(1, 1) = zcalc::Expression{{6.0, 0.0}};
    matrix_4(1, 2) = zcalc::Expression{{8.0, 0.0}};
    matrix_4(1, 3) = zcalc::Expression{{3.0, 0.0}};

    matrix_4(2, 0) = zcalc::Expression{{6.0, 0.0}};
    matrix_4(2, 1) = zcalc::Expression{{8.0, 0.0}};
    matrix_4(2, 2) = zcalc::Expression{{18.0, 0.0}};
    matrix_4(2, 3) = zcalc::Expression{{5.0, 0.0}};

    success = matrix_4.solve_system_of_linear_equations(result);

    ASSERT_EQ(true, success);
    ASSERT_EQ(result[0].evaluate(), std::complex<double>(3.0/10.0, 0.0));
    ASSERT_EQ(result[1].evaluate(), std::complex<double>(2.0/5.0, 0.0));
    ASSERT_EQ(result[2].evaluate(), std::complex<double>(0.0, 0.0));

}

TEST(MatrixTest, MatrixWithVariable) {
    std::complex<double> zero_value { 0.0, 0.0 };
    zcalc::Expression zero_exp {zero_value};

    std::vector<zcalc::Expression> result;
    bool success = false;
    
    std::shared_ptr<zcalc::Variable> a = std::make_shared<zcalc::Variable>("a");
    std::shared_ptr<zcalc::Variable> b = std::make_shared<zcalc::Variable>("b");

    /*  1x + -3y +  2z =  5 */
    /*  2x +  3y + -1z =  6 */
    /*  4x + -3y +  az =  b */
    zcalc::Matrix matrix {3, 4, zero_value};
    matrix[0][0] = zcalc::Expression{1};
    matrix[0][1] = zcalc::Expression{-3};
    matrix[0][2] = zcalc::Expression{2};
    matrix[0][3] = zcalc::Expression{5};
    matrix[1][0] = zcalc::Expression{2};
    matrix[1][1] = zcalc::Expression{3};
    matrix[1][2] = zcalc::Expression{-1};
    matrix[1][3] = zcalc::Expression{6};
    matrix[2][0] = zcalc::Expression{4};
    matrix[2][1] = zcalc::Expression{-3};
    matrix[2][2] = zcalc::Expression{a};
    matrix[2][3] = zcalc::Expression{b};

    success = matrix.solve_system_of_linear_equations(result);

    ASSERT_EQ(true, success);

    //std::cout << matrix << std::endl << std::endl;

    /* a != 3, b = R ==> 1 solution -> true */
    /* a = 3, b = 16 ==> infinite solutions -> false */
    /* a = 3, b != 16 ==> 0 solution -> false */

    a->set_value(2);
    b->set_value(3);

    constexpr double epsilon = 1e-10;

    /* double comparison problems occurred (-0.6666667 != -0.6666667) */
    if (result[0].evaluate().real() < -2.0/3.0 - epsilon) ASSERT_EQ(true, false);
    if (result[0].evaluate().real() > -2.0/3.0 + epsilon) ASSERT_EQ(true, false);
    if (result[1].evaluate().real() < 61.0/9.0 - epsilon) ASSERT_EQ(true, false);
    if (result[1].evaluate().real() > 61.0/9.0 + epsilon) ASSERT_EQ(true, false);
    if (result[2].evaluate().real() < 13.0 - epsilon) ASSERT_EQ(true, false);
    if (result[2].evaluate().real() > 13.0 + epsilon) ASSERT_EQ(true, false);
    ASSERT_EQ(true, true);
}