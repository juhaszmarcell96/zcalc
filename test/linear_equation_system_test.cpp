#include <gtest/gtest.h>

#include <include/complex.hpp>
#include <include/linear_equation.hpp>
#include <include/linear_equation_system.hpp>

TEST(LinearEquationSystemTest, EliminationTest1) {

    bool success = false;

    /*  2x + 0y + 1z =  3 */
    zcalc::LinearEquation<zcalc::Complex> eq_0 {3};
    eq_0.set_coefficient(0, zcalc::Complex{2.0, 0.0});
    eq_0.set_coefficient(1, zcalc::Complex{0.0, 0.0});
    eq_0.set_coefficient(2, zcalc::Complex{1.0, 0.0});
    eq_0.set_result(zcalc::Complex{3.0, 0.0});

    /*  4x + 2y + 1z =  3 */
    zcalc::LinearEquation<zcalc::Complex> eq_1 {3};
    eq_1.set_coefficient(0, zcalc::Complex{4.0, 0.0});
    eq_1.set_coefficient(1, zcalc::Complex{2.0, 0.0});
    eq_1.set_coefficient(2, zcalc::Complex{1.0, 0.0});
    eq_1.set_result(zcalc::Complex{3.0, 0.0});

    /* -2x + 8y + 2z = -8 */
    zcalc::LinearEquation<zcalc::Complex> eq_2 {3};
    eq_2.set_coefficient(0, zcalc::Complex{-2.0, 0.0});
    eq_2.set_coefficient(1, zcalc::Complex{8.0, 0.0});
    eq_2.set_coefficient(2, zcalc::Complex{2.0, 0.0});
    eq_2.set_result(zcalc::Complex{-8.0, 0.0});

    zcalc::LinearEquationSystem lin_equ_sys {3};
    lin_equ_sys.append_equation(eq_0);
    lin_equ_sys.append_equation(eq_1);
    lin_equ_sys.append_equation(eq_2);

    std::vector<zcalc::Complex> solution;

    success = lin_equ_sys.solve(solution);

    ASSERT_EQ(success, true);
    ASSERT_EQ(solution[0], zcalc::Complex(1.0, 0.0));
    ASSERT_EQ(solution[1], zcalc::Complex(-1.0, 0.0));
    ASSERT_EQ(solution[2], zcalc::Complex(1.0, 0.0));
    
}

TEST(LinearEquationSystemTest, EliminationTest2) {

    bool success = false;

    zcalc::LinearEquation<zcalc::Complex> eq_0 {4};
    eq_0[0] = zcalc::Complex{1.0, 0.0};
    eq_0[1] = zcalc::Complex{2.0, 0.0};
    eq_0[2] = zcalc::Complex{1.0, 0.0};
    eq_0.set_result(zcalc::Complex{1.0, 0.0});

    zcalc::LinearEquation<zcalc::Complex> eq_1 {4};
    eq_1[0] = zcalc::Complex{2.0, 0.0};
    eq_1[1] = zcalc::Complex{3.0, 0.0};
    eq_1[2] = zcalc::Complex{2.0, 0.0};
    eq_1.set_result(zcalc::Complex{1.0, 0.0});

    zcalc::LinearEquation<zcalc::Complex> eq_2 {4};
    eq_2[0] = zcalc::Complex{3.0, 0.0};
    eq_2[1] = zcalc::Complex{3.0, 0.0};
    eq_2[2] = zcalc::Complex{2.0, 0.0};
    eq_2.set_result(zcalc::Complex{0.0, 0.0});

    zcalc::LinearEquation<zcalc::Complex> eq_3 {4};
    eq_3[0] = zcalc::Complex{1.0, 0.0};
    eq_3[1] = zcalc::Complex{1.0, 0.0};
    eq_3[2] = zcalc::Complex{2.0, 0.0};
    eq_3.set_result(zcalc::Complex{1.0, 0.0});

    zcalc::LinearEquationSystem lin_equ_sys {4};
    lin_equ_sys.append_equation(eq_0);
    lin_equ_sys.append_equation(eq_1);
    lin_equ_sys.append_equation(eq_2);
    lin_equ_sys.append_equation(eq_3);

    std::vector<zcalc::Complex> solution;

    success = lin_equ_sys.solve(solution);

    ASSERT_EQ(success, false);
}

TEST(LinearEquationSystemTest, EliminationTest3) {

    /* no solution */
    /*  1x + 1y +   2z =  3 */
    /*  2x + 2y +   5z = -4 */
    /*  5x + 5y + -11z =  6 */

    bool success = false;

    zcalc::LinearEquation<zcalc::Complex> eq_0 {3};
    eq_0[0] = zcalc::Complex{1.0, 0.0};
    eq_0[1] = zcalc::Complex{1.0, 0.0};
    eq_0[2] = zcalc::Complex{2.0, 0.0};
    eq_0.set_result(zcalc::Complex{3.0, 0.0});

    zcalc::LinearEquation<zcalc::Complex> eq_1 {3};
    eq_1[0] = zcalc::Complex{2.0, 0.0};
    eq_1[1] = zcalc::Complex{2.0, 0.0};
    eq_1[2] = zcalc::Complex{5.0, 0.0};
    eq_1.set_result(zcalc::Complex{-4.0, 0.0});

    zcalc::LinearEquation<zcalc::Complex> eq_2 {3};
    eq_2[0] = zcalc::Complex{5.0, 0.0};
    eq_2[1] = zcalc::Complex{5.0, 0.0};
    eq_2[2] = zcalc::Complex{-11.0, 0.0};
    eq_2.set_result(zcalc::Complex{6.0, 0.0});

    zcalc::LinearEquationSystem lin_equ_sys {3};
    lin_equ_sys.append_equation(eq_0);
    lin_equ_sys.append_equation(eq_1);
    lin_equ_sys.append_equation(eq_2);

    std::vector<zcalc::Complex> solution;

    success = lin_equ_sys.solve(solution);

    ASSERT_EQ(success, false);
}

TEST(LinearEquationSystemTest, EliminationTest4) {

    /* infinite solutions */

    bool success = false;

    zcalc::LinearEquation<zcalc::Complex> eq_0 {3};
    eq_0[0] = zcalc::Complex{2.0, 0.0};
    eq_0[1] = zcalc::Complex{1.0, 0.0};
    eq_0[2] = zcalc::Complex{-3.0, 0.0};
    eq_0.set_result(zcalc::Complex{1.0, 0.0});

    zcalc::LinearEquation<zcalc::Complex> eq_1 {3};
    eq_1[0] = zcalc::Complex{4.0, 0.0};
    eq_1[1] = zcalc::Complex{2.0, 0.0};
    eq_1[2] = zcalc::Complex{-6.0, 0.0};
    eq_1.set_result(zcalc::Complex{2.0, 0.0});

    zcalc::LinearEquation<zcalc::Complex> eq_2 {3};
    eq_2[0] = zcalc::Complex{-8.0, 0.0};
    eq_2[1] = zcalc::Complex{-4.0, 0.0};
    eq_2[2] = zcalc::Complex{-12.0, 0.0};
    eq_2.set_result(zcalc::Complex{-4.0, 0.0});

    zcalc::LinearEquationSystem lin_equ_sys {3};
    lin_equ_sys.append_equation(eq_0);
    lin_equ_sys.append_equation(eq_1);
    lin_equ_sys.append_equation(eq_2);

    std::vector<zcalc::Complex> solution;

    success = lin_equ_sys.solve(solution);

    ASSERT_EQ(success, false);
}

TEST(LinearEquationSystemTest, EliminationTest5) {

    /* solution should be found */
    /*  2x + 1y +  3z =  1 */
    /*  2x + 6y +  8z =  3 */
    /*  6x + 8y + 18z =  5 */

    bool success = false;

    zcalc::LinearEquation<zcalc::Complex> eq_0 {3};
    eq_0.set_coefficient(0, zcalc::Complex{2.0, 0.0});
    eq_0.set_coefficient(1, zcalc::Complex{1.0, 0.0});
    eq_0.set_coefficient(2, zcalc::Complex{3.0, 0.0});
    eq_0.set_result(zcalc::Complex{1.0, 0.0});

    zcalc::LinearEquation<zcalc::Complex> eq_1 {3};
    eq_1.set_coefficient(0, zcalc::Complex{2.0, 0.0});
    eq_1.set_coefficient(1, zcalc::Complex{6.0, 0.0});
    eq_1.set_coefficient(2, zcalc::Complex{8.0, 0.0});
    eq_1.set_result(zcalc::Complex{3.0, 0.0});

    zcalc::LinearEquation<zcalc::Complex> eq_2 {3};
    eq_2.set_coefficient(0, zcalc::Complex{6.0, 0.0});
    eq_2.set_coefficient(1, zcalc::Complex{8.0, 0.0});
    eq_2.set_coefficient(2, zcalc::Complex{18.0, 0.0});
    eq_2.set_result(zcalc::Complex{5.0, 0.0});

    zcalc::LinearEquationSystem lin_equ_sys {3};
    lin_equ_sys.append_equation(eq_0);
    lin_equ_sys.append_equation(eq_1);
    lin_equ_sys.append_equation(eq_2);

    std::vector<zcalc::Complex> solution;

    success = lin_equ_sys.solve(solution);

    ASSERT_EQ(success, true);
    ASSERT_EQ(solution[0], zcalc::Complex(3.0/10.0, 0.0));
    ASSERT_EQ(solution[1], zcalc::Complex(2.0/5.0, 0.0));
    ASSERT_EQ(solution[2], zcalc::Complex(0.0, 0.0));
    
}

TEST(LinearEquationSystemTest, SimpleCircuitTest1) {
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

    std::vector<zcalc::Complex> result;
    bool success = false;

    zcalc::LinearEquation<zcalc::Complex> eq_0 {6};
    eq_0[3] = zcalc::Complex{-1.0, 0.0};
    eq_0[4] = zcalc::Complex{-1.0, 0.0};
    zcalc::LinearEquation<zcalc::Complex> eq_1 {6};
    eq_1[3] = zcalc::Complex{1.0, 0.0};
    eq_1[5] = zcalc::Complex{1.0, 0.0};
    zcalc::LinearEquation<zcalc::Complex> eq_2 {6};
    eq_2[4] = zcalc::Complex{1.0, 0.0};
    eq_2[5] = zcalc::Complex{-1.0, 0.0};
    zcalc::LinearEquation<zcalc::Complex> eq_3 {6};
    eq_3[0] = zcalc::Complex{1.0, 0.0};
    eq_3[1] = zcalc::Complex{-1.0, 0.0};
    eq_3[2] = zcalc::Complex{-1.0, 0.0};
    zcalc::LinearEquation<zcalc::Complex> eq_4 {6};
    eq_4[1] = zcalc::Complex{1.0, 0.0};
    eq_4[4] = zcalc::Complex{-10.0, 0.0};        /* -R1 */
    zcalc::LinearEquation<zcalc::Complex> eq_5 {6};
    eq_5[2] = zcalc::Complex{1.0, 0.0};
    eq_5[5] = zcalc::Complex{-10.0, 0.0};        /* -R2 */
    zcalc::LinearEquation<zcalc::Complex> eq_6 {6};
    eq_6[0] = zcalc::Complex{1.0, 0.0};
    eq_6.set_result(zcalc::Complex{5.0, 0.0});   /* Us */

    zcalc::LinearEquationSystem lin_equ_sys {6};
    lin_equ_sys.append_equation(eq_0);
    lin_equ_sys.append_equation(eq_1);
    lin_equ_sys.append_equation(eq_2);
    lin_equ_sys.append_equation(eq_3);
    lin_equ_sys.append_equation(eq_4);
    lin_equ_sys.append_equation(eq_5);
    lin_equ_sys.append_equation(eq_6);

    success = lin_equ_sys.solve(result);

    ASSERT_EQ(true, success);
    
    ASSERT_EQ(result[0], zcalc::Complex(5.0, 0.0));
    ASSERT_EQ(result[1], zcalc::Complex(5.0/2.0, 0.0));
    ASSERT_EQ(result[2], zcalc::Complex(5.0/2.0, 0.0));
    ASSERT_EQ(result[3], zcalc::Complex(-1.0/4.0, 0.0));
    ASSERT_EQ(result[4], zcalc::Complex(1.0/4.0, 0.0));
    ASSERT_EQ(result[5], zcalc::Complex(1.0/4.0, 0.0));
}

TEST(LinearEquationSystemTest, SimpleCircuitTest2) {

    std::vector<zcalc::Complex> result;
    bool success = false;

    zcalc::LinearEquation<zcalc::Complex> eq_0 {6};
    eq_0[3] = zcalc::Complex{-1.0, 0.0};
    eq_0[4] = zcalc::Complex{-1.0, 0.0};
    zcalc::LinearEquation<zcalc::Complex> eq_1 {6};
    eq_1[3] = zcalc::Complex{1.0, 0.0};
    eq_1[5] = zcalc::Complex{1.0, 0.0};
    zcalc::LinearEquation<zcalc::Complex> eq_2 {6};
    eq_2[4] = zcalc::Complex{1.0, 0.0};
    eq_2[5] = zcalc::Complex{-1.0, 0.0};
    zcalc::LinearEquation<zcalc::Complex> eq_3 {6};
    eq_3[0] = zcalc::Complex{1.0, 0.0};
    eq_3[1] = zcalc::Complex{-1.0, 0.0};
    eq_3[2] = zcalc::Complex{-1.0, 0.0};
    zcalc::LinearEquation<zcalc::Complex> eq_4 {6};
    eq_4[1] = zcalc::Complex{1.0, 0.0};
    eq_4[4] = zcalc::Complex{-10.0, 0.0};        /* -R1 -> 10/3V (1/3A) */
    zcalc::LinearEquation<zcalc::Complex> eq_5 {6};
    eq_5[2] = zcalc::Complex{1.0, 0.0};
    eq_5[5] = zcalc::Complex{-5.0, 0.0};         /* -R2 -> 5/3V (1/3A)  */
    zcalc::LinearEquation<zcalc::Complex> eq_6 {6};
    eq_6[0] = zcalc::Complex{1.0, 0.0};
    eq_6.set_result(zcalc::Complex{5.0, 0.0});   /* Us */

    zcalc::LinearEquationSystem lin_equ_sys {6};
    lin_equ_sys.append_equation(eq_0);
    lin_equ_sys.append_equation(eq_1);
    lin_equ_sys.append_equation(eq_2);
    lin_equ_sys.append_equation(eq_3);
    lin_equ_sys.append_equation(eq_4);
    lin_equ_sys.append_equation(eq_5);
    lin_equ_sys.append_equation(eq_6);

    success = lin_equ_sys.solve(result);

    ASSERT_EQ(true, success);
    
    ASSERT_EQ(result[0], zcalc::Complex(5.0, 0.0));
    ASSERT_EQ(result[1], zcalc::Complex(10.0/3.0, 0.0));
    ASSERT_EQ(result[2], zcalc::Complex(5.0/3.0, 0.0));
    ASSERT_EQ(result[3], zcalc::Complex(-1.0/3.0, 0.0));
    ASSERT_EQ(result[4], zcalc::Complex(1.0/3.0, 0.0));
    ASSERT_EQ(result[5], zcalc::Complex(1.0/3.0, 0.0));
}