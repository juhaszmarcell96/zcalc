#include <zcalc/common.hpp>
#include <zcalc/network.hpp>

#include <zcalc/plot/plotter.hpp>

#include <cmath>
#include <fstream>
#include <iostream>


int main () {
    zcalc::Network lora_filter { };
    lora_filter.set_frequency(868.0e6);
    lora_filter.add_node ("gnd");
    lora_filter.add_node ("in");
    lora_filter.add_node ("out");
    lora_filter.add_source ("Us", 1.0, "in", "gnd");
    lora_filter.add_resistor("R_output", 10e9, "out", "gnd");
    lora_filter.add_capacitor("C1", 4.7e-12, "in", "gnd");
    lora_filter.add_capacitor("C2", 1.2e-12, "in", "out");
    lora_filter.add_inductor("L1", 6.2e-9, "in", "out");
    lora_filter.add_capacitor("C3", 1.8e-12, "out", "gnd");
    lora_filter.add_resistor("RL", 50.0, "out", "gnd");

    zcalc::Plotter plotter {};
    plotter.plot("lora_filter", lora_filter, lora_filter.get_component_id("R_output"));

    return 0;
}