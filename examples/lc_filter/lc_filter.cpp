#include <zcalc/common.hpp>
#include <zcalc/network.hpp>

#include <zcalc/plot/plotter.hpp>

#include <cmath>
#include <fstream>
#include <iostream>

/* capacitor equivalent circuit */

int main () {

    zcalc::Network lc_filter { };
    lc_filter.add_node ("gnd");
    lc_filter.add_node ("in");
    lc_filter.add_node ("out");
    lc_filter.add_voltage_source ("Us", 1.0, 0.0, "in", "gnd");
    lc_filter.add_resistor("R_output", 10e9, "out", "gnd");
    lc_filter.add_inductor("L", 10e-9, "in", "out");        /* 10nH */
    lc_filter.add_capacitor("C", 100e-9, "out", "gnd");     /* 100nF */

    zcalc::Plotter plotter {};
    plotter.plot("lc_filter", lc_filter, "Us", "R_output");

    return 0;
}