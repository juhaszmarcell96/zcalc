#include <gtest/gtest.h>

#include <zcalc/common.hpp>
#include <zcalc/internal/equation_system.hpp>

TEST(LinearEquationSystemTest, EliminationTest1) {
    
    /*  2x + 0y + 1z =  3 */
    /*  4x + 2y + 1z =  3 */
    /* -2x + 8y + 2z = -8 */

    zcalc::EquationSystem eq_sys {};
    eq_sys.add_variable("x");
    eq_sys.add_variable("y");
    eq_sys.add_variable("z");
    eq_sys.set_num_equations(3);

    /*  2x + 0y + 1z =  3 */
    eq_sys.set_coefficient("x", 0, 2);
    eq_sys.set_coefficient("y", 0, 0);
    eq_sys.set_coefficient("z", 0, 1);
    eq_sys.set_result(0, 3);

    /*  4x + 2y + 1z =  3 */
    eq_sys.set_coefficient("x", 1, 4);
    eq_sys.set_coefficient("y", 1, 2);
    eq_sys.set_coefficient("z", 1, 1);
    eq_sys.set_result(1, 3);

    /* -2x + 8y + 2z = -8 */
    eq_sys.set_coefficient("x", 2, -2);
    eq_sys.set_coefficient("y", 2, 8);
    eq_sys.set_coefficient("z", 2, 2);
    eq_sys.set_result(2, -8);

    ASSERT_EQ(eq_sys.solve_for("x"), zcalc::complex_t(1.0, 0.0));
    ASSERT_EQ(eq_sys.solve_for("y"), zcalc::complex_t(-1.0, 0.0));
    ASSERT_EQ(eq_sys.solve_for("z"), zcalc::complex_t(1.0, 0.0));
    
}

TEST(LinearEquationSystemTest, EliminationTest3) {
    
    /* no solution */
    /*  1x + 1y +   2z =  3 */
    /*  2x + 2y +   5z = -4 */
    /*  5x + 5y + -11z =  6 */

    zcalc::EquationSystem eq_sys {};
    eq_sys.add_variable("x");
    eq_sys.add_variable("y");
    eq_sys.add_variable("z");
    eq_sys.set_num_equations(3);

    eq_sys.set_coefficient("x", 0, 1);
    eq_sys.set_coefficient("y", 0, 1);
    eq_sys.set_coefficient("z", 0, 2);
    eq_sys.set_result(0, 3);

    eq_sys.set_coefficient("x", 1, 2);
    eq_sys.set_coefficient("y", 1, 2);
    eq_sys.set_coefficient("z", 1, 5);
    eq_sys.set_result(1, -4);

    eq_sys.set_coefficient("x", 2, 5);
    eq_sys.set_coefficient("y", 2, 5);
    eq_sys.set_coefficient("z", 2, -11);
    eq_sys.set_result(2, 6);

    try {
        eq_sys.solve_for("x");
        ASSERT_FALSE(true);
    }
    catch (...) {
        ASSERT_FALSE(false);
    }
}

TEST(LinearEquationSystemTest, EliminationTest4) {
    
    /* infinite solutions */
    /*  2x +  1y +  -3z =  1 */
    /*  4x +  2y +  -6z =  2 */
    /* -8x + -4y + -12z = -4 */

    zcalc::EquationSystem eq_sys {};
    eq_sys.add_variable("x");
    eq_sys.add_variable("y");
    eq_sys.add_variable("z");
    eq_sys.set_num_equations(3);

    eq_sys.set_coefficient("x", 0, 2);
    eq_sys.set_coefficient("y", 0, 1);
    eq_sys.set_coefficient("z", 0, -3);
    eq_sys.set_result(0, 1);

    eq_sys.set_coefficient("x", 1, 4);
    eq_sys.set_coefficient("y", 1, 2);
    eq_sys.set_coefficient("z", 1, -6);
    eq_sys.set_result(1, 2);

    eq_sys.set_coefficient("x", 2, -8);
    eq_sys.set_coefficient("y", 2, -4);
    eq_sys.set_coefficient("z", 2, -12);
    eq_sys.set_result(2, -4);

    try {
        eq_sys.solve_for("x");
        ASSERT_FALSE(true);
    }
    catch (...) {
        ASSERT_FALSE(false);
    }
}

TEST(LinearEquationSystemTest, EliminationTest5) {
    
    /*  2x + 1y +  3z =  1 */
    /*  2x + 6y +  8z =  3 */
    /*  6x + 8y + 18z =  5 */

    zcalc::EquationSystem eq_sys {};
    eq_sys.add_variable("x");
    eq_sys.add_variable("y");
    eq_sys.add_variable("z");
    eq_sys.set_num_equations(3);

    eq_sys.set_coefficient("x", 0, 2);
    eq_sys.set_coefficient("y", 0, 1);
    eq_sys.set_coefficient("z", 0, 3);
    eq_sys.set_result(0, 1);

    eq_sys.set_coefficient("x", 1, 2);
    eq_sys.set_coefficient("y", 1, 6);
    eq_sys.set_coefficient("z", 1, 8);
    eq_sys.set_result(1, 3);

    eq_sys.set_coefficient("x", 2, 6);
    eq_sys.set_coefficient("y", 2, 8);
    eq_sys.set_coefficient("z", 2, 18);
    eq_sys.set_result(2, 5);

    ASSERT_EQ(eq_sys.solve_for("x"), 3.0/10.0);
    ASSERT_EQ(eq_sys.solve_for("y"), 2.0/5.0);
    ASSERT_EQ(eq_sys.solve_for("z"), 0.0);
    
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

    zcalc::EquationSystem eq_sys {};
    eq_sys.add_variable("us");
    eq_sys.add_variable("u1");
    eq_sys.add_variable("u2");
    eq_sys.add_variable("is");
    eq_sys.add_variable("i1");
    eq_sys.add_variable("i2");
    eq_sys.set_num_equations(7);

    eq_sys.set_coefficient("is", 0, -1);
    eq_sys.set_coefficient("i1", 0, -1);

    eq_sys.set_coefficient("is", 1,  1);
    eq_sys.set_coefficient("i2", 1,  1);

    eq_sys.set_coefficient("i1", 2,  1);
    eq_sys.set_coefficient("i2", 2, -1);

    eq_sys.set_coefficient("us", 3,  1);
    eq_sys.set_coefficient("u1", 3, -1);
    eq_sys.set_coefficient("u2", 3, -1);

    eq_sys.set_coefficient("u1", 4,  1);
    eq_sys.set_coefficient("i1", 4, -10);        /* -R1 */

    eq_sys.set_coefficient("u2", 5,  1);
    eq_sys.set_coefficient("i2", 5, -10);        /* -R2 */

    eq_sys.set_coefficient("us", 6,  1);
    eq_sys.set_result(6, 5);                     /*  Us */

    ASSERT_EQ(eq_sys.solve_for("us"), 5.0);
    ASSERT_EQ(eq_sys.solve_for("u1"), 5.0/2.0);
    ASSERT_EQ(eq_sys.solve_for("u2"), 5.0/2.0);
    ASSERT_EQ(eq_sys.solve_for("is"), -1.0/4.0);
    ASSERT_EQ(eq_sys.solve_for("i1"), 1.0/4.0);
    ASSERT_EQ(eq_sys.solve_for("i2"), 1.0/4.0);
}

// TEST(LinearEquationSystemTest, SimpleCircuitTest2) {

//     std::vector<zcalc::Complex> result;
//     bool success = false;

//     zcalc::LinearEquation<zcalc::Complex> eq_0 {6};
//     eq_0[3] = zcalc::Complex{-1.0, 0.0};
//     eq_0[4] = zcalc::Complex{-1.0, 0.0};
//     zcalc::LinearEquation<zcalc::Complex> eq_1 {6};
//     eq_1[3] = zcalc::Complex{1.0, 0.0};
//     eq_1[5] = zcalc::Complex{1.0, 0.0};
//     zcalc::LinearEquation<zcalc::Complex> eq_2 {6};
//     eq_2[4] = zcalc::Complex{1.0, 0.0};
//     eq_2[5] = zcalc::Complex{-1.0, 0.0};
//     zcalc::LinearEquation<zcalc::Complex> eq_3 {6};
//     eq_3[0] = zcalc::Complex{1.0, 0.0};
//     eq_3[1] = zcalc::Complex{-1.0, 0.0};
//     eq_3[2] = zcalc::Complex{-1.0, 0.0};
//     zcalc::LinearEquation<zcalc::Complex> eq_4 {6};
//     eq_4[1] = zcalc::Complex{1.0, 0.0};
//     eq_4[4] = zcalc::Complex{-10.0, 0.0};        /* -R1 -> 10/3V (1/3A) */
//     zcalc::LinearEquation<zcalc::Complex> eq_5 {6};
//     eq_5[2] = zcalc::Complex{1.0, 0.0};
//     eq_5[5] = zcalc::Complex{-5.0, 0.0};         /* -R2 -> 5/3V (1/3A)  */
//     zcalc::LinearEquation<zcalc::Complex> eq_6 {6};
//     eq_6[0] = zcalc::Complex{1.0, 0.0};
//     eq_6.set_result(zcalc::Complex{5.0, 0.0});   /* Us */

//     zcalc::LinearEquationSystem lin_equ_sys {6};
//     lin_equ_sys.append_equation(eq_0);
//     lin_equ_sys.append_equation(eq_1);
//     lin_equ_sys.append_equation(eq_2);
//     lin_equ_sys.append_equation(eq_3);
//     lin_equ_sys.append_equation(eq_4);
//     lin_equ_sys.append_equation(eq_5);
//     lin_equ_sys.append_equation(eq_6);

//     success = lin_equ_sys.solve(result);

//     ASSERT_EQ(true, success);
    
//     ASSERT_EQ(result[0], zcalc::Complex(5.0, 0.0));
//     ASSERT_EQ(result[1], zcalc::Complex(10.0/3.0, 0.0));
//     ASSERT_EQ(result[2], zcalc::Complex(5.0/3.0, 0.0));
//     ASSERT_EQ(result[3], zcalc::Complex(-1.0/3.0, 0.0));
//     ASSERT_EQ(result[4], zcalc::Complex(1.0/3.0, 0.0));
//     ASSERT_EQ(result[5], zcalc::Complex(1.0/3.0, 0.0));
// }