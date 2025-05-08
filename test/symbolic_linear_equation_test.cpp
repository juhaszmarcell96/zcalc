/*
 * Copyright (C) 2025 Marcell Juhasz
 *
 * This software is licensed under a non-commercial license.
 * Non-commercial use (personal, academic, research) is allowed for free.
 * Commercial use requires a paid license.
 * Hosting as a service is prohibited without explicit permission.
 *
 * See LICENSE for details or contact marcell.juhasz96@gmail.com.
 */

#include <gtest/gtest.h>

#include <zcalc/math/symbolic_linear_equation.hpp>

namespace zcalc::math {

TEST(SymbolicLinearEquationTest, SetterGetterTest) {
    SymbolicLinearEquation<double> equation { "eq" };
    equation.add_term("x", 1.0);
    equation.add_term("y", -2.5);
    equation.set_result(3.0);

    std::cout << equation << std::endl;

    ASSERT_EQ(equation.get_result(), 3.0);
    ASSERT_EQ(equation.get_coefficient("x"), 1.0);
    ASSERT_EQ(equation.get_coefficient("y"), -2.5);
    ASSERT_EQ(equation.get_coefficient("z"), 0.0);
}

TEST(SymbolicLinearEquationTest, MergeTermsTest) {
    SymbolicLinearEquation<double> equation { "eq" };
    equation.add_term("x", 1.0);
    equation.add_term("y", -2.5);
    equation.add_term("x", -2.1);
    equation.set_result(3.0);

    std::cout << equation << std::endl;

    ASSERT_EQ(equation.get_result(), 3.0);
    ASSERT_EQ(equation.get_coefficient("x"), -1.1);
    ASSERT_EQ(equation.get_coefficient("y"), -2.5);
    ASSERT_EQ(equation.get_coefficient("z"), 0.0);
}

} // namespace zcalc::math