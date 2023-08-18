
#include "equation_system.hpp"

int main() {

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

    zcalc::complex x_solution = eq_sys.solve_for("x");
    zcalc::complex y_solution = eq_sys.solve_for("y");
    zcalc::complex z_solution = eq_sys.solve_for("z");

    std::cout << "x = " << x_solution << std::endl; /*  1 */
    std::cout << "y = " << y_solution << std::endl; /* -1 */
    std::cout << "z = " << z_solution << std::endl; /*  1 */

    return 0;
}