#include <zcalc/common.hpp>
#include <zcalc/network.hpp>

#include <zcalc/plot/plotter.hpp>

#include <cmath>
#include <fstream>
#include <iostream>


int main () {

    zcalc::Network bandpass { };
    bandpass.add_node("A");
    bandpass.add_node ("gnd");
    bandpass.add_node ("in");
    bandpass.add_node ("out");
    bandpass.add_voltage_source ("Us", 1.0, 0.0, "in", "gnd");
    bandpass.add_resistor("R_output", 10e9, "out", "gnd");
    bandpass.add_capacitor("C1", 15e-9, "in", "A");
    bandpass.add_resistor("R1", 10e3, "A", "gnd");
    bandpass.add_resistor("R2", 10e3, "A", "out");
    bandpass.add_capacitor("C2", 560.0e-12, "out", "gnd");

    zcalc::Plotter plotter {};
    plotter.plot("bandpass", bandpass, "Us", "R_output");

    return 0;
}