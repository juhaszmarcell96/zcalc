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
    network.add_voltage_source ("Us", 1.0, zcalc::math::Frequency::create_from_hz(0.0), "in", "gnd");
    network.add_resistor("R_Us", 35, "in", "A"); // voltage source internal resistance
    network.add_capacitor("C1", 2.4e-12, "A", "gnd"); // 2.4pF
    network.add_inductor("L1", 2.4e-9, "A", "out"); // 2.4nH
    network.add_capacitor("C2", 2.0e-12, "out", "gnd"); // 2pF
    network.add_resistor("antenna", 50, "out", "gnd"); // 50 ohm antenna

    zcalc::plot::PlotterConfig config {};
    config.filename = "bluetooth";
    config.input_source = "Us";
    config.output_component = "antenna";
    config.target_frequency = zcalc::math::Frequency::create_from_hz(2.4e9);
    config.min_frequency = zcalc::math::Frequency::create_from_hz(1);
    config.max_frequency = zcalc::math::Frequency::create_from_hz(1.0e10);
    config.granularity = 0.05;

    zcalc::plot::html::Plotter plotter {};
    plotter.plot(network, config);

    return 0;
}