#include <zcalc/common.hpp>
#include <zcalc/network.hpp>
#include <zcalc/resistor.hpp>
#include <zcalc/capacitor.hpp>
#include <zcalc/inductor.hpp>


int main () {
    zcalc::Network test_network { };
    test_network.set_frequency(50.0e3);
    //test_network.add_node("gnd");
    //test_network.add_node("in");
    //test_network.add_node("out");
    //test_network.add_source("U1", 5, "in", "gnd");
    test_network.add_resistor("R1", 10, "in", "out");
    test_network.add_resistor("R2", 10, "out", "gnd");
    test_network.compute();
    test_network.print();
    test_network.print_equations();

    return 0;
}