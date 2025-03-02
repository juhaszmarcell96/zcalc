#include <zcalc/common.hpp>
#include <zcalc/network.hpp>

#include <zcalc/plot/html/plotter.hpp>

#include <cmath>
#include <fstream>
#include <iostream>


int main () {
    zcalc::Network network { };
    network.add_node ("gnd");
    network.add_node ("in");
    network.add_node ("A");
    network.add_node ("out");
    network.add_voltage_source ("Us", 1.0, 0.0, "in", "gnd");
    network.add_resistor("R_Us", 35, "in", "A"); // voltage source internal resistance
    network.add_capacitor("C1", 2.4e-12, "A", "gnd"); // 2.4pF
    network.add_inductor("L1", 2.4e-9, "A", "out"); // 2.4nH
    network.add_capacitor("C2", 2.0e-12, "out", "gnd"); // 2pF
    network.add_resistor("antenna", 50, "out", "gnd"); // 50 ohm antenna

    zcalc::plot::html::Plotter plotter {};
    plotter.plot("bluetooth", network, "Us", "antenna", 2.4e9);

    return 0;
}