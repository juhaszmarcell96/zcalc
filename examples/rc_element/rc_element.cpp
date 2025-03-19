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

    zcalc::Network rc_net { };
    rc_net.add_node ("gnd");
    rc_net.add_node ("in");
    rc_net.add_node ("out");
    auto Us = rc_net.add_voltage_source ("Us", 1.0, zcalc::math::Frequency::create_from_hz(0.0), "in", "gnd");
    auto Rout = rc_net.add_resistor("R_output", 10e9, "out", "gnd");
    rc_net.add_resistor("R", 50.0, "in", "out");
    rc_net.add_capacitor("C", 100.0e-6, "out", "gnd");

    zcalc::plot::PlotterConfig config {};
    config.filename = "rc_element";
    config.input_source = Us;
    config.output_component = Rout;
    config.min_frequency = zcalc::math::Frequency::create_from_hz(1);
    config.max_frequency = zcalc::math::Frequency::create_from_hz(1.0e3);
    config.num_points = 1.0e3;

    zcalc::plot::html::Plotter plotter {};
    plotter.plot(rc_net, config);

    return 0;
}