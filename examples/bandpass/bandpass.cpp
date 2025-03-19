/*
 * Copyright (C) 2025 Marcell Juhasz
 *
 * This software is licensed under a non-commercial license.
 * Non-commercial use (personal, academic, research) is allowed for free.
 * Commercial use requires a paid license.
 * Hosting as a service is prohibited without explicit permission.
 *
 * See LICENSE for details or contact marcell.juhasz96@gmail.com.
 */

#include <zcalc/common.hpp>
#include <zcalc/network.hpp>

#include <zcalc/plot/html/plotter.hpp>

#include <cmath>
#include <fstream>
#include <iostream>


int main () {

    zcalc::Network bandpass { };
    bandpass.add_node("A");
    bandpass.add_node ("gnd");
    bandpass.add_node ("in");
    bandpass.add_node ("out");
    auto Us = bandpass.add_voltage_source ("Us", 1.0, zcalc::math::Frequency{}, "in", "gnd");
    auto Rout = bandpass.add_resistor("R_output", 10e9, "out", "gnd");
    bandpass.add_capacitor("C1", 15e-9, "in", "A");
    bandpass.add_resistor("R1", 10e3, "A", "gnd");
    bandpass.add_resistor("R2", 10e3, "A", "out");
    bandpass.add_capacitor("C2", 560.0e-12, "out", "gnd");

    zcalc::plot::PlotterConfig config {};
    config.filename = "bandpass";
    config.input_source = Us;
    config.output_component = Rout;
    config.min_frequency = zcalc::math::Frequency::create_from_hz(1.0e1);
    config.max_frequency = zcalc::math::Frequency::create_from_hz(1.0e7);
    config.num_points = 1.0e3;

    zcalc::plot::html::Plotter plotter {};
    plotter.plot(bandpass, config);

    return 0;
}