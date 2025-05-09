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

/* capacitor equivalent circuit */

int main () {

    zcalc::Network lc_filter { };
    lc_filter.add_node ("gnd");
    lc_filter.add_node ("in");
    lc_filter.add_node ("out");
    auto Us = lc_filter.add_voltage_source ("Us", 1.0, zcalc::math::Frequency::create_from_hz(0.0), "in", "gnd");
    auto Rout = lc_filter.add_resistor("R_output", 10e9, "out", "gnd");
    lc_filter.add_inductor("L", 10e-9, "in", "out");        /* 10nH */
    lc_filter.add_capacitor("C", 100e-9, "out", "gnd");     /* 100nF */

    zcalc::plot::PlotterConfig config {};
    config.filename = "lc_filter";
    config.input_source = Us;
    config.output_component = Rout;
    config.min_frequency = zcalc::math::Frequency::create_from_hz(1.0e6);
    config.max_frequency = zcalc::math::Frequency::create_from_hz(1.1e7);
    config.num_points = 1.0e3;

    zcalc::plot::html::Plotter plotter {};
    plotter.plot(lc_filter, config);

    return 0;
}