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

int main () {
    zcalc::Network test_network { };
    test_network.add_node("gnd");
    test_network.add_node("in");
    test_network.add_node("out");
    test_network.add_voltage_source("U1", 5, zcalc::math::Frequency::create_from_hz(50.0e3), "in", "gnd");
    test_network.add_resistor("R1", 10, "in", "out");
    test_network.add_resistor("R2", 10, "out", "gnd");
    test_network.print();

    return 0;
}