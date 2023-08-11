#include <zcalc/common.hpp>
#include <zcalc/network.hpp>
#include <zcalc/resistor.hpp>
#include <zcalc/capacitor.hpp>
#include <zcalc/inductor.hpp>

#include <zcalc/plot/plotter.hpp>

#include <cmath>
#include <fstream>
#include <iostream>


int main () {

    zcalc::Network bandpass { };
    bandpass.add_node("A");
    bandpass.add_capacitor("C1", 0.1e-6, "in", "A");
    bandpass.add_resistor("R1", 1000.0, "A", "gnd");
    bandpass.add_resistor("R2", 47000.0, "A", "out");
    bandpass.add_capacitor("C2", 470.0e-12, "out", "gnd");

    zcalc::Plotter plotter {};
    plotter.plot("tmp", bandpass);

    return 0;
}