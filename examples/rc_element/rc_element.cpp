#include <zcalc/common.hpp>
#include <zcalc/network.hpp>

#include <zcalc/plot/html/plotter.hpp>

#include <cmath>
#include <fstream>
#include <iostream>


int main () {

    zcalc::Network rc_net { };
    rc_net.add_node ("gnd");
    rc_net.add_node ("in");
    rc_net.add_node ("out");
    rc_net.add_voltage_source ("Us", 1.0, zcalc::math::Frequency::create_from_hz(0.0), "in", "gnd");
    rc_net.add_resistor("R_output", 10e9, "out", "gnd");
    rc_net.add_resistor("R", 50.0, "in", "out");
    rc_net.add_capacitor("C", 100.0e-6, "out", "gnd");

    zcalc::plot::PlotterConfig config {};
    config.filename = "rc_element";
    config.input_source = "Us";
    config.output_component = "R_output";
    config.min_frequency = zcalc::math::Frequency::create_from_hz(1);
    config.max_frequency = zcalc::math::Frequency::create_from_hz(1.0e10);
    config.granularity = 0.05;

    zcalc::plot::html::Plotter plotter {};
    plotter.plot(rc_net, config);

    return 0;
}