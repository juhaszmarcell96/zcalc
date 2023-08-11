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
    bandpass.add_capacitor("C1", 15e-9, "in", "A");
    bandpass.add_resistor("R1", 10e3, "A", "gnd");
    bandpass.add_resistor("R2", 10e3, "A", "out");
    bandpass.add_capacitor("C2", 560.0e-12, "out", "gnd");

    zcalc::Plotter plotter {};
    plotter.plot("tmp", bandpass);

    return 0;
}