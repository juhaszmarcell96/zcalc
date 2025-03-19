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

    zcalc::Network capacitor { };
    capacitor.add_node ("gnd");
    capacitor.add_node ("in");
    capacitor.add_node ("A");
    capacitor.add_node ("B");

    auto Is = capacitor.add_current_source ("Is", 1.0, zcalc::math::Frequency::create_from_hz(0.0), "in", "gnd");

    capacitor.add_capacitor("C", 100.0e-9, "in", "A"); // 100nF
    capacitor.add_resistor("R_esr", 0.01, "A", "B"); // 10mohm
    capacitor.add_inductor("L_esl", 10.0e-9, "B", "gnd"); // 10nH

    auto Rout = capacitor.add_resistor("R_output", 10e9, "in", "gnd");

    zcalc::plot::PlotterConfig config {};
    config.filename = "capacitor";
    config.input_source = Is;
    config.output_component = Rout;
    config.min_frequency = zcalc::math::Frequency::create_from_hz(1.0e6);
    config.max_frequency = zcalc::math::Frequency::create_from_hz(2.0e7);
    config.num_points = 1.0e3;

    zcalc::plot::html::Plotter plotter {};
    plotter.plot(capacitor, config);

    return 0;
}