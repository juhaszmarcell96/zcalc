#include <gtest/gtest.h>

#include <zcalc/expression/expression.hpp>

#include <sstream>
#include <string>

TEST(SimplificationTest, ConstantSimplification) {

    // 8 + 3 * (2 * 3)
    zcalc::Expression exp {
        zcalc::Expression(8) +
        zcalc::Expression(3) * (
            zcalc::Expression(2) *
            zcalc::Expression(3)
        )
    };

    std::stringstream stream;

    stream << exp;
    ASSERT_EQ(stream.str(), "((8,0)+((3,0)*((2,0)*(3,0))))");
    ASSERT_TRUE(exp.get_root()->is_operation());
    exp.simplify();
    stream.str(std::string());
    stream << exp;
    ASSERT_TRUE(exp.get_root()->is_constant());
    ASSERT_EQ(stream.str(), "(26,0)");
}

TEST(SimplificationTest, SimplifyTest) {
    // 2 * ( 2 + 3 )
    zcalc::Expression exp {
        zcalc::Expression("x") * (
            zcalc::Expression(2) +
            zcalc::Expression("y")
        )
    };

    std::cout << exp << std::endl;
    exp.simplify();
    std::cout << exp << std::endl;
}