#include <zcalc/common.hpp>
#include <zcalc/network.hpp>
#include <zcalc/resistor.hpp>
#include <zcalc/capacitor.hpp>
#include <zcalc/inductor.hpp>

#include <zcalc/plot/plotter.hpp>

#include <cmath>
#include <fstream>
#include <iostream>

/* capacitor equivalent circuit */

int main () {

    zcalc::Network lc_filter { };
    lc_filter.add_inductor("L", 10e-9, "in", "out");        /* 10nH */
    lc_filter.add_capacitor("C", 100e-9, "out", "gnd");     /* 100nF */

    zcalc::Plotter plotter {};
    plotter.plot("lc_filter", lc_filter);

    return 0;
}