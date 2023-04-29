#include <gtest/gtest.h>

#include <include/complex.hpp>
#include <include/linear_equation.hpp>
#include <include/linear_equation_system.hpp>

TEST(LinearEquationSystemTest, EliminationTest) {

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