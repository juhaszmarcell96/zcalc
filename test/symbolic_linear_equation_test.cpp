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