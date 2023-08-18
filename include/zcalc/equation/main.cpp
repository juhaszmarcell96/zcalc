
#include "equation.hpp"

int main() {

    LinearEquation equation {};

    equation.add_variable("x");
    equation.set_coeff("x", 5.0);
    equation.set_eq(6.0);
    if (equation.solve_for("x")) {
        std::cout << equation.get_value("x") << std::endl;
    }

    Expression exp {complex{5.0, 0.0}};
    exp += 3;
    exp += 2;
    exp /= 5;
    std::cout << exp << std::endl;
    std::cout << exp.evaluate() << std::endl;
    
    std::shared_ptr<Variable> x = std::make_shared<Variable>("x");
    Expression exp1 {x};
    exp1 *= 3;
    exp1 += 5;
    x->set_value(complex{5.0, 0.0});
    std::cout << exp1 << std::endl;
    std::cout << exp1.evaluate() << std::endl;

    
    std::shared_ptr<Variable> y = std::make_shared<Variable>("y");
    Expression exp2 {y};
    exp2 *= 3;

    Expression exp3 {complex{5.0, 0.0}};
    exp3 += 3;
    exp3 += 4;
    exp3 *= y;

    exp2 += exp3;

    y->set_value(complex{5.0, 0.0});

    std::cout << exp2 << std::endl;
    y->set_value(5);
    std::cout << exp2.evaluate() << std::endl;
    y->set_value(10);
    std::cout << exp2.evaluate() << std::endl;

    return 0;
}