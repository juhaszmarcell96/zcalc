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

#include <gtest/gtest.h>

#include <zcalc/common.hpp>
#include <zcalc/network.hpp>
#include <zcalc/network_calculator.hpp>
#include <zcalc/network_builder.hpp>
#include <zcalc/json/parser.hpp>

/*
{
    "n": 4,
    "c": [
        {
            "i": 0,
            "t": 0,
            "n0": 0,
            "n1": 1,
            "r": 5,
            "u": "k"
        },
        {
            "i": 1,
            "t": 1,
            "n0": 1,
            "n1": 2,
            "c": 0.1,
            "u": "u"
        },
        {
            "i": 2,
            "t": 2,
            "n0": 2,
            "n1": 3,
            "l": 10,
            "u": "m"
        },
        {
            "i": 3,
            "t": 4,
            "n0": 3,
            "n1": 0,
            "v": 5,
            "u": "",
            "p": 0,
            "f": 5000
        }
    ]
}
*/

TEST(NetworkJsonTest, VoltageDivider) {
    std::string json_network = R"(
        {
            "n": 3,
            "c": [
                {
                    "i": 0,
                    "t": 0,
                    "r": 10,
                    "u": 7,
                    "n0": 2,
                    "n1": 0
                },
                {
                    "i": 1,
                    "t": 0,
                    "r": 10,
                    "u": 7,
                    "n0": 1,
                    "n1": 2
                },
                {
                    "i": 2,
                    "t": 4,
                    "v": 1,
                    "u": 7,
                    "f": 0,
                    "p": 1,
                    "n0": 1,
                    "n1": 0
                }
            ]
        }
    )";

    zcalc::json::JsonParser parser { json_network };
    const auto json = parser.parse();
    auto test_network = zcalc::NetworkBuilder::from_json(json);
    ASSERT_TRUE(test_network.has_value());

    const auto results = zcalc::NetworkCalculator::compute(test_network.value());
    ASSERT_EQ(results.size(), 6);

    // Us
    ASSERT_EQ(results.at("2_i").size(), 1);
    ASSERT_EQ(results.at("2_i")[0].to_complex(), zcalc::math::Complex(-0.05, 0.0));
    ASSERT_EQ(results.at("2_i")[0].get_frequency().as_rad_per_sec(), 0.0);
    ASSERT_EQ(results.at("2_u").size(), 1);
    ASSERT_EQ(results.at("2_u")[0].to_complex(), zcalc::math::Complex(1.0, 0.0));
    ASSERT_EQ(results.at("2_u")[0].get_frequency().as_rad_per_sec(), 0.0);

    // R1
    ASSERT_EQ(results.at("0_i").size(), 1);
    ASSERT_EQ(results.at("0_i")[0].to_complex(), zcalc::math::Complex(0.05, 0.0));
    ASSERT_EQ(results.at("0_i")[0].get_frequency().as_rad_per_sec(), 0.0);
    ASSERT_EQ(results.at("0_u").size(), 1);
    ASSERT_EQ(results.at("0_u")[0].to_complex(), zcalc::math::Complex(0.5, 0.0));
    ASSERT_EQ(results.at("0_u")[0].get_frequency().as_rad_per_sec(), 0.0);

    // R2
    ASSERT_EQ(results.at("1_i").size(), 1);
    ASSERT_EQ(results.at("1_i")[0].to_complex(), zcalc::math::Complex(0.05, 0.0));
    ASSERT_EQ(results.at("1_i")[0].get_frequency().as_rad_per_sec(), 0.0);
    ASSERT_EQ(results.at("1_u").size(), 1);
    ASSERT_EQ(results.at("1_u")[0].to_complex(), zcalc::math::Complex(0.5, 0.0));
    ASSERT_EQ(results.at("1_u")[0].get_frequency().as_rad_per_sec(), 0.0);
}

/*

TEST(NetworkCalculatorTest, VoltageResponse) {
    zcalc::Network network {};
    network.add_node ("gnd");
    network.add_node ("in");
    network.add_node ("out");
    network.add_node ("A");
    network.add_voltage_source ("Us", 10.0, zcalc::math::Frequency::create_from_rad_per_sec(5000.0), "in", "gnd"); // 10V, 5krad/s (5/(2pi))
    network.add_capacitor("C1", 2.0e-6, "in", "out"); // 2uF
    network.add_capacitor("C2", 1.0e-6, "out", "gnd"); // 1uF
    network.add_resistor("R", 40, "out", "A"); // 40ohm
    network.add_inductor("L", 8.0e-3, "A", "gnd"); // 8mH
    const auto vmeter = network.add_voltmeter("voltmeter", "out", "gnd");

    const auto results = zcalc::NetworkCalculator::compute(network);
    ASSERT_EQ(results.at(vmeter->voltage()).size(), 1);
    ASSERT_EQ(results.at(vmeter->voltage())[0].to_complex(), zcalc::math::Complex(1.53846, 7.69231));
    ASSERT_EQ(results.at(vmeter->voltage())[0].get_frequency().as_rad_per_sec(), 5000.0);
}

TEST(NetworkCalculatorTest, VoltageAndCurrentResponse) {
    //
    //      in     ┌──────┐   A  ┌┐┌┐┌┐    B     ┌──────┐    out
    //     ┌───────┤  R1  ├──────┘└┘└┘└────o─────┤  R3  ├──────┐
    //     │       └──────┘         L      │     └──────┘      │
    //     │                               │                   │
    //  ┌──┼──┐ |                        ┌─┴─┐                 │
    //  │  │  │ | Us                     │R2 │            ┌────o────┐
    //  │  │  │ |                        │   │          ┌─┴─┐       |  C
    //  └──┼──┘ v                        └─┬─┘          │R4 │    ───┴───
    //     │                               │            │   │    ───┬───
    //     │              gnd              │            └─┬─┘       │
    //     └───────────────────────────────o──────────────o─────────┘
    //
    zcalc::Network network {};
    network.add_node ("gnd");
    network.add_node ("in");
    network.add_node ("out");
    network.add_node ("A");
    network.add_node ("B");
    network.add_voltage_source ("Us", 24.0, zcalc::math::Frequency::create_from_hz(5000.0), "in", "gnd"); // 24V, 5kHz
    network.add_resistor("R1", 500, "in", "A"); // 500ohm
    network.add_inductor("L", 10.0e-3, "A", "B"); // 10mH
    network.add_resistor("R2", 1000, "B", "gnd"); // 1kohm
    const auto R3 = network.add_resistor("R3", 800, "B", "out"); // 800ohm
    network.add_resistor("R4", 600, "out", "gnd"); // 600ohm
    const auto C = network.add_capacitor("C", 120.0e-9, "out", "gnd"); // 120nF

    const auto results = zcalc::NetworkCalculator::compute(network);
    ASSERT_EQ(results.at(C->voltage()).size(), 1);
    ASSERT_EQ(results.at(C->voltage())[0].to_complex(), zcalc::math::Complex(0.830672, -2.89235));
    ASSERT_EQ(results.at(C->voltage())[0].get_frequency().as_hz(), 5000.0);

    ASSERT_EQ(results.at(R3->current()).size(), 1);
    ASSERT_EQ(results.at(R3->current())[0].to_complex(), zcalc::math::Complex(0.0122884, -0.00168902));
    ASSERT_EQ(results.at(R3->current())[0].get_frequency().as_hz(), 5000.0);
}

TEST(NetworkCalculatorTest, SuperpositionTest) {
    //
    //                          B(1)       ┌──────┐    C(2)
    //     ┌────────────────────o──────────┤  R3  ├──────┐
    //     │                    │          └──────┘      │
    //   ┌─┴─┐                  │                        └─┐
    //   │R1 │                  │                        ┌─┘
    //   │   │                  │                        └─┐
    //   └─┬─┘                  │                        ┌─┘ L
    //     │ A(0)               │                        └─┐
    //  ┌──┼──┐ |             ┌─┴─┐                      ┌─┘
    //  │  │  │ | U1          │R2 │                      │ D(3)
    //  │  │  │ |             │   │                      │
    //  └──┼──┘ v             └─┬─┘                   ┌──┼──┐ |
    //     │                    │                     │  │  │ | U2
    //     │                    │  | I                │  │  │ |
    //     │                    │  V                  └──┼──┘ v
    //     │       gnd(4)       │                        │
    //     └────────────────────o────────────────────────┘
    //
    zcalc::Network network {};
    network.add_node ("A");
    network.add_node ("B");
    network.add_node ("C");
    network.add_node ("D");
    network.add_node ("gnd");

    network.add_voltage_source ("U1", 4.0, zcalc::math::Frequency::create_from_hz(0.0), "A", "gnd"); // 4VDC
    network.add_voltage_source ("U2", std::sqrt(2.0) * 6.0, zcalc::math::Frequency::create_from_rad_per_sec(10.0e3), "D", "gnd"); // sqrt(2)* 6V, 10krad/s (1591.5Hz)

    network.add_resistor("R1", 10, "B", "A"); // 10ohm
    const auto R2 = network.add_resistor("R2", 50, "B", "gnd"); // 50ohm
    network.add_resistor("R3", 5, "B", "C"); // 5ohm
    network.add_inductor("L", 1.0e-3, "C", "D"); // 1mH

    const auto results = zcalc::NetworkCalculator::compute(network);
    ASSERT_EQ(results.at(R2->current()).size(), 2);
    ASSERT_EQ(results.at(R2->current())[0].to_complex(), zcalc::math::Complex(0.025, 0.0));
    ASSERT_EQ(results.at(R2->current())[0].get_frequency().as_hz(), 0.0);
    ASSERT_NEAR(results.at(R2->current())[1].to_complex().real(), 0.0678555, 0.0001);
    ASSERT_NEAR(results.at(R2->current())[1].to_complex().imag(), -0.0509473, 0.0001);
    ASSERT_EQ(results.at(R2->current())[1].get_frequency().as_rad_per_sec(), 10.0e3);
}

TEST(NetworkCalculatorTest, VoltageControlledCurrentSourceTest) {
    //
    //                                    ┌──────┐  
    //                            ┌───────┤  R2  ├───────┐
    //                            │       └──────┘       │
    //                            │                      │
    //                            │                      │
    //      in     ┌──────┐   A   │        ┌┐┌┐┌┐        │      out
    //     ┌───────┤  R1  ├───────o────────┘└┘└┘└────────o───────────────────┐
    //     │       └──────┘       │           L          │                   │
    //     │                      │                      │                   │
    //  ┌──┼──┐ |                 |  C                 ┌─┴─┐                 │
    //  │  │  │ | Us           ───┴───                 │R3 │                / \   |
    //  │  │  │ |              ───┬───                 │   │               /___\  | DU
    //  └──┼──┘ v                 │                    └─┬─┘               \   /  V
    //     │                      │                      │                  \ /
    //     │              gnd     │                      │                   │
    //     └──────────────────────o──────────────────────o───────────────────┘
    //
    zcalc::Network network {};
    network.add_node ("gnd");
    network.add_node ("in");
    network.add_node ("out");
    network.add_node ("A");
    network.add_voltage_source ("Us", 10.0, zcalc::math::Frequency::create_from_rad_per_sec(5e3), "in", "gnd"); // 10V, 5krad/s
    network.add_resistor("R1", 1000, "in", "A"); // 1kohm
    network.add_resistor("R2", 1000, "A", "out"); // 1kohm
    network.add_resistor("R3", 1000, "out", "gnd"); // 1kohm
    network.add_inductor("L", 1.0, "A", "out"); // 1H
    const auto C = network.add_capacitor("C", 1.0e-6, "A", "gnd"); // 1uF
    const auto DU = network.add_voltage_controlled_current_source("DU", "out", "gnd", C, 0.5e-3); // 0.5mS

    auto results = zcalc::NetworkCalculator::compute(network);
    ASSERT_EQ(results.at(DU->voltage()).size(), 1);
    auto res = results.at(DU->voltage())[0].to_complex();
    res.set_print_format(zcalc::math::Complex::print_format::basic);
    auto expected = zcalc::math::Complex(0.0316742, -0.511312);
    expected.set_print_format(zcalc::math::Complex::print_format::basic);
    ASSERT_EQ(res, expected);
    ASSERT_EQ(results.at(DU->voltage())[0].get_frequency().as_rad_per_sec(), 5000.0);
}

TEST(NetworkCalculatorTest, VoltageControlledVoltageSourceTest) {
    //
    //                     V1
    //     ┌──────────────────────o──────────────────────o───────────────────┐
    //     │                      │                      │                   │
    //     │                      │                      │                   │
    //     │                     /│\   |               ┌─┴─┐               ┌─┴─┐ │
    //     │                    / │ \  | E1            │R3 │ │             │R4 │ │ IR4
    //     │                    \ │ /  V               │   │ │ UR3         │   │ V
    //     │                     \│/                   └─┬─┘ V             └─┬─┘
    //     │                      │                      │                   │
    //  ┌──┴──┐ ^                 |       ┌──────┐       │                   │
    //  │_____│ | I1          V2  o───────┤  R2  ├───────o V3                │ V4
    //  │     │ |                 |       └──────┘       │                   │
    //  └──┬──┘                   │                      │                ┌──┼──┐ |
    //     │                    ┌─┴─┐                 ┌──┴──┐ ^           │  │  │ | E2
    //     │                 │  │R1 │                 │_____│ | I2        │  │  │ |
    //     │             UR1 │  │   │                 │     │ |           └──┼──┘ v
    //     │                 V  └─┬─┘                 └──┬──┘                │
    //     │                      │                      │                   │
    //     │             gnd      │                      │                   │
    //     └──────────────────────o──────────────────────o───────────────────┘
    //
    zcalc::Network network {};
    network.add_node ("gnd");
    network.add_node ("V1");
    network.add_node ("V2");
    network.add_node ("V3");
    network.add_node ("V4");
    network.add_current_source("I1", 2.0e-3, zcalc::math::Frequency::create_dc(), "gnd", "V1"); // 2mA !!! pay attention to the direction (either rotate or -4mA)
    network.add_current_source("I2", 2.0e-3, zcalc::math::Frequency::create_dc(), "gnd", "V3"); // 2mA !!! pay attention to the direction (either rotate or -4mA)
    network.add_voltage_source("E2", 4.0, zcalc::math::Frequency::create_dc(), "V4", "gnd"); // 4V
    const auto R1 = network.add_resistor("R1", 1000, "V2", "gnd"); // 1kohm
    network.add_resistor("R2", 2000, "V2", "V3"); // 2kohm
    const auto R3 = network.add_resistor("R3", 3000, "V1", "V3"); // 3kohm
    const auto R4 = network.add_resistor("R4", 4000, "V1", "V4"); // 4kohm
    network.add_voltage_controlled_voltage_source("E1", "V1", "V2", R1, 2.0);

    const auto results = zcalc::NetworkCalculator::compute(network);

    // R3_u -> 1.03V
    // R1_u -> 2.86V
    // R4_i -> 1.15mA

    ASSERT_EQ(results.at(R1->voltage()).size(), 3);
    ASSERT_EQ(results.at(R1->voltage())[0].to_complex() + results.at(R1->voltage())[1].to_complex() + results.at(R1->voltage())[2].to_complex(), zcalc::math::Complex(2.85714, 0.0));
    ASSERT_EQ(results.at(R3->voltage()).size(), 3);
    ASSERT_EQ(results.at(R3->voltage())[0].to_complex() + results.at(R3->voltage())[1].to_complex() + results.at(R3->voltage())[2].to_complex(), zcalc::math::Complex(1.02857, 0.0));
    ASSERT_EQ(results.at(R4->current()).size(), 3);
    ASSERT_EQ(results.at(R4->current())[0].to_complex() + results.at(R4->current())[1].to_complex() + results.at(R4->current())[2].to_complex(), zcalc::math::Complex(0.00115, 0.0));
}

TEST(NetworkCalculatorTest, IdealTransformerTest) {
    //
    //                        Iprim    Isec
    //             prim     1   ->     <-   3      sec
    //     ┌────────────────o─────┐   ┌─────o─────────────┐
    //     │                     o│n:1│o                  │
    //     │                      /   /                   │
    //  ┌──┼──┐ |                 \   \                 ┌─┴─┐
    //  │  │  │ | Us              /   /                 │ R │
    //  │  │  │ |                 \   \                 │   │
    //  └──┼──┘ v                 │   │                 └─┬─┘
    //     │              gnd1    │   │    gnd2           │
    //     └────────────────o─────┘   └─────o─────────────┘
    //                      2               4
    zcalc::Network network {};
    network.add_node ("gnd1");
    network.add_node ("gnd2");
    network.add_node ("prim");
    network.add_node ("sec");
    const auto Us = network.add_voltage_source ("Us", 5.0, zcalc::math::Frequency::create_dc(), "prim", "gnd1"); // 5Vdc
    network.add_ideal_transformer("T", "prim", "gnd1", "sec", "gnd2", 2.0); // 2:1 -> V_sec = 2.5V
    const auto R = network.add_resistor("R", 100.0, "sec", "gnd2"); // 100ohm

    // 2:1 -> V_sec = 2.5V -> I_R = 25mA -> Isec = -25mA -> Iprim = 12.5mA -> I_Us = -12.5mA

    auto results = zcalc::NetworkCalculator::compute(network);
    ASSERT_EQ(results.at(R->voltage()).size(), 1);
    ASSERT_EQ(results.at(R->voltage())[0].to_complex(), zcalc::math::Complex(2.5, 0.0)); // 2.5V
    ASSERT_EQ(results.at(R->voltage())[0].get_frequency().as_hz(), 0.0);
    ASSERT_EQ(results.at(R->current()).size(), 1);
    ASSERT_EQ(results.at(R->current())[0].to_complex(), zcalc::math::Complex(0.025, 0.0)); // 25mA
    ASSERT_EQ(results.at(R->current())[0].get_frequency().as_hz(), 0.0);
    ASSERT_EQ(results.at(Us->current()).size(), 1);
    ASSERT_EQ(results.at(Us->current())[0].to_complex(), zcalc::math::Complex(-0.0125, 0.0)); // -12.5mA
    ASSERT_EQ(results.at(Us->current())[0].get_frequency().as_hz(), 0.0);
}

TEST(NetworkCalculatorTest, IdealInvertingAmplifierTestTest) {
    zcalc::Network network {};
    network.add_node ("gnd");
    network.add_node ("A");
    network.add_node ("B");
    network.add_node ("C");
    network.add_voltage_source ("Us", 5.0, zcalc::math::Frequency::create_dc(), "A", "gnd"); // 5Vdc
    network.add_resistor("R1", 1000.0, "A", "B"); // 1000ohm
    network.add_ideal_amplifier("Amp", "B", "gnd", "C", "gnd", 10.0e6);
    network.add_resistor("RF", 2000.0, "B", "C"); // 2000ohm
    const auto RL = network.add_resistor("RL", 1000.0, "C", "gnd"); // 1000ohm

    // U_C = -RF/R1 * U_A = -2 * U_A = -10V

    auto results = zcalc::NetworkCalculator::compute(network);
    ASSERT_EQ(results.at(RL->voltage()).size(), 1);
    ASSERT_EQ(results.at(RL->voltage())[0].to_complex(), zcalc::math::Complex(-10.0, 0.0)); // -10.0V
    ASSERT_EQ(results.at(RL->voltage())[0].get_frequency().as_hz(), 0.0);
}

TEST(NetworkCalculatorTest, IdealNoninvertingAmplifierTestTest) {
    zcalc::Network network {};
    network.add_node ("gnd");
    network.add_node ("A");
    network.add_node ("B");
    network.add_node ("C");
    network.add_voltage_source ("Us", 5.0, zcalc::math::Frequency::create_dc(), "A", "gnd"); // 5Vdc
    network.add_ideal_amplifier("Amp", "B", "A", "C", "gnd", 10.0e6);
    network.add_resistor("R1", 1000.0, "B", "gnd"); // 1000ohm
    network.add_resistor("RF", 2000.0, "B", "C"); // 2000ohm
    const auto RL = network.add_resistor("RL", 1000.0, "C", "gnd"); // 1000ohm

    // U_C = (1 + RF/R1) * U_A = 3 * U_A = 15V

    auto results = zcalc::NetworkCalculator::compute(network);
    ASSERT_EQ(results.at(RL->voltage()).size(), 1);
    ASSERT_EQ(results.at(RL->voltage())[0].to_complex(), zcalc::math::Complex(15.0, 0.0)); // 15.0V
    ASSERT_EQ(results.at(RL->voltage())[0].get_frequency().as_hz(), 0.0);
}

TEST(NetworkCalculatorTest, VoltageFollowerTestTest) {
    zcalc::Network network {};
    network.add_node ("gnd");
    network.add_node ("A");
    network.add_node ("B");
    network.add_node ("C");
    network.add_voltage_source ("Us", 5.0, zcalc::math::Frequency::create_dc(), "A", "gnd"); // 5Vdc
    network.add_resistor("R1", 1000.0, "A", "B"); // 1000ohm
    network.add_ideal_amplifier("Amp", "C", "B", "C", "gnd", 10.0e6);
    const auto RL = network.add_resistor("RL", 1000.0, "C", "gnd"); // 1000ohm

    // U_C = U_A = 5V

    auto results = zcalc::NetworkCalculator::compute(network);
    ASSERT_EQ(results.at(RL->voltage()).size(), 1);
    ASSERT_EQ(results.at(RL->voltage())[0].to_complex(), zcalc::math::Complex(5.0, 0.0)); // 5.0V
    ASSERT_EQ(results.at(RL->voltage())[0].get_frequency().as_hz(), 0.0);
}

TEST(NetworkCalculatorTest, CoupledInductorTest) {
    zcalc::Network network {};
    network.add_node ("gnd");
    network.add_node ("A");
    network.add_node ("B");
    network.add_node ("C");
    network.add_voltage_source ("Us", 10.0, zcalc::math::Frequency::create_from_rad_per_sec(5000.0), "A", "gnd"); // 10V, 5krad/s
    network.add_coupled_inductor("M", "B", "gnd", "C", "gnd", 0.4, 0.2, 0.2); // w_0*L1 = 2kohm, w_0*L2 = 1kohm, w_0*M = 1kohm
    network.add_resistor("R1", 1000.0, "A", "B");
    const auto R = network.add_resistor("R2", 2000.0, "B", "C");

    auto results = zcalc::NetworkCalculator::compute(network);
    ASSERT_EQ(results.at(R->current()).size(), 1);
    auto res = results.at(R->current())[0].to_complex();
    res.set_print_format(zcalc::math::Complex::print_format::euler_deg);
    ASSERT_EQ(res, zcalc::math::Complex(0.00192308, 0.000384615));
    ASSERT_EQ(results.at(R->current())[0].get_frequency().as_rad_per_sec(), 5000.0);
}

*/