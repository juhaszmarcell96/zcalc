#include <zcalc/common.hpp>
#include <zcalc/network.hpp>

#include <zcalc/plot/html/plotter.hpp>

#include <cmath>
#include <fstream>
#include <iostream>


int main () {
    zcalc::Network lora_filter { };
    lora_filter.add_node ("gnd");
    lora_filter.add_node ("in");
    lora_filter.add_node ("out");
    lora_filter.add_voltage_source ("Us", 1.0, zcalc::math::Frequency::create_from_hz(0.0), "in", "gnd");
    lora_filter.add_resistor("R_output", 10e9, "out", "gnd");
    lora_filter.add_capacitor("C1", 4.7e-12, "in", "gnd");
    lora_filter.add_capacitor("C2", 1.2e-12, "in", "out");
    lora_filter.add_inductor("L1", 6.2e-9, "in", "out");
    lora_filter.add_capacitor("C3", 1.8e-12, "out", "gnd");
    lora_filter.add_resistor("RL", 50.0, "out", "gnd");

    zcalc::plot::PlotterConfig config {};
    config.filename = "lora_filter";
    config.input_source = "Us";
    config.output_component = "R_output";
    config.target_frequency = zcalc::math::Frequency::create_from_hz(868.0e6);
    config.min_frequency = zcalc::math::Frequency::create_from_hz(1.0e8);
    config.max_frequency = zcalc::math::Frequency::create_from_hz(1.0e10);
    config.num_points = 1.0e3;

    zcalc::plot::html::Plotter plotter {};
    plotter.plot(lora_filter, config);

    return 0;
}