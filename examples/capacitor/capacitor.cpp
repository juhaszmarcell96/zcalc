#include <zcalc/common.hpp>
#include <zcalc/network.hpp>

#include <zcalc/plot/plotter.hpp>

#include <cmath>
#include <fstream>
#include <iostream>


int main () {

    zcalc::Network capacitor { };
    capacitor.add_node ("gnd");
    capacitor.add_node ("in");
    capacitor.add_node ("A");
    capacitor.add_node ("B");

    capacitor.add_current_source ("Is", 1.0, "in", "gnd");

    capacitor.add_capacitor("C", 100.0e-9, "in", "A"); // 100nF
    capacitor.add_resistor("R_esr", 0.01, "A", "B"); // 10mohm
    capacitor.add_inductor("L_esl", 10.0e-9, "B", "gnd"); // 10nH

    capacitor.add_resistor("R_output", 10e9, "in", "gnd");

    zcalc::Plotter plotter {};
    plotter.plot("capacitor", capacitor, capacitor.get_component_id("R_output"));

    return 0;
}