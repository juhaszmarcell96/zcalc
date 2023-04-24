#include <gtest/gtest.h>

#include <include/complex.hpp>
#include <include/expression.hpp>
#include <include/matrix.hpp>

TEST(MatrixTest, MatrixAdditionTest) {
    zcalc::Complex zero_value { 0.0, 0.0 };
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
    ASSERT_EQ(result[1][2].evaluate(), zcalc::Complex(2.0, 2.0));
    ASSERT_EQ(result[2][0].evaluate(), zero_value);
    ASSERT_EQ(result[2][1].evaluate(), zero_value);
    ASSERT_EQ(result[2][2].evaluate(), zero_value);
}

TEST(MatrixTest, MatrixMultiplicationTest) {
    zcalc::Complex zero_value { 0.0, 0.0 };
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
    
    ASSERT_EQ(result[0][0].evaluate(), zcalc::Complex(14.0, 0.0));
    ASSERT_EQ(result[1][0].evaluate(), zcalc::Complex(32.0, 0.0));
}

TEST(MatrixTest, MatrixEliminationTest) {
    zcalc::Complex zero_value { 0.0, 0.0 };
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
    ASSERT_EQ(result[0].evaluate(), zcalc::Complex(1.0, 0.0));
    ASSERT_EQ(result[1].evaluate(), zcalc::Complex(-1.0, 0.0));
    ASSERT_EQ(result[2].evaluate(), zcalc::Complex(1.0, 0.0));

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
    ASSERT_EQ(result[0].evaluate(), zcalc::Complex(3.0/10.0, 0.0));
    ASSERT_EQ(result[1].evaluate(), zcalc::Complex(2.0/5.0, 0.0));
    ASSERT_EQ(result[2].evaluate(), zcalc::Complex(0.0, 0.0));

}

TEST(MatrixTest, MatrixWithVariable) {
    zcalc::Complex zero_value { 0.0, 0.0 };
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

    /* a != 3, b = R ==> 1 solution -> true */
    /* a = 3, b = 16 ==> infinite solutions -> false */
    /* a = 3, b != 16 ==> 0 solution -> false */

    a->set_value(2);
    b->set_value(3);
    
    ASSERT_EQ(result[0].evaluate(), zcalc::Complex(-2.0/3.0, 0.0));
    ASSERT_EQ(result[1].evaluate(), zcalc::Complex(61.0/9.0, 0.0));
    ASSERT_EQ(result[2].evaluate(), zcalc::Complex(13.0, 0.0));
}

TEST(MatrixTest, SimpleCircuitTest) {
    /**
     * Simple circuit consisting of a voltage source and 2 resistors in series.
     * -> the linear equation system is as follows
     *    - is - i1 = 0
     *    is + i2 = 0
     *    i1 - i2 = 0
     *    us - u2 - u1 = 0
     *    u1 - R1*i1 = 0
     *    u2 - R2*i2 = 0
     *    us = Us
     * 
     *  ->  us   u1   u2   is   i1   i2    b
     *      0     0    0   -1   -1    0    0
     *      0     0    0    1    0    1    0
     *      0     0    0    0    1   -1    0
     *      1    -1   -1    0    0    0    0
     *      0     1    0    0   -R1   0    0
     *      0     0    1    0    0   -R2   0
     *      1     0    0    0    0    0    Us
     * 
     *  Solution for Us=5V and R1=10ohm R2=10ohm -> is=i1=i2=5V/20ohm=0.25A (is has opposite direction, so it is negative), u1=u2=2.5V
    **/
    zcalc::Complex zero_value { 0.0, 0.0 };
    zcalc::Expression zero_exp {zero_value};

    std::vector<zcalc::Expression> result;
    bool success = false;
    
    std::shared_ptr<zcalc::Variable> Us = std::make_shared<zcalc::Variable>("Us");
    std::shared_ptr<zcalc::Variable> R1 = std::make_shared<zcalc::Variable>("R1");
    std::shared_ptr<zcalc::Variable> R2 = std::make_shared<zcalc::Variable>("R2");

    zcalc::Matrix matrix {7, 7, zero_value};
    matrix[0][3] = zcalc::Expression{-1};
    matrix[0][4] = zcalc::Expression{-1};
    matrix[1][3] = zcalc::Expression{1};
    matrix[1][5] = zcalc::Expression{1};
    matrix[2][4] = zcalc::Expression{1};
    matrix[2][5] = zcalc::Expression{-1};
    matrix[3][0] = zcalc::Expression{1};
    matrix[3][1] = zcalc::Expression{-1};
    matrix[3][2] = zcalc::Expression{-1};
    matrix[4][1] = zcalc::Expression{1};
    matrix[4][4] = zcalc::Expression{R1} * -1;
    matrix[5][2] = zcalc::Expression{1};
    matrix[5][5] = zcalc::Expression{R2} * -1;
    matrix[6][0] = zcalc::Expression{1};
    matrix[6][6] = zcalc::Expression{Us};

    matrix.print();

    success = matrix.solve_system_of_linear_equations(result);

    ASSERT_EQ(true, success);

    Us->set_value(5);
    R1->set_value(10);
    R2->set_value(10);
    
    ASSERT_EQ(result[0].evaluate(), zcalc::Complex(5.0, 0.0));
    ASSERT_EQ(result[1].evaluate(), zcalc::Complex(5.0/2.0, 0.0));
    ASSERT_EQ(result[2].evaluate(), zcalc::Complex(5.0/2.0, 0.0));
    ASSERT_EQ(result[3].evaluate(), zcalc::Complex(-1.0/4.0, 0.0));
    ASSERT_EQ(result[4].evaluate(), zcalc::Complex(1.0/4.0, 0.0));
    ASSERT_EQ(result[5].evaluate(), zcalc::Complex(1.0/4.0, 0.0));
}