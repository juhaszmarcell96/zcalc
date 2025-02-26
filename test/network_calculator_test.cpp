#include <gtest/gtest.h>

#include <zcalc/common.hpp>
#include <zcalc/network.hpp>
#include <zcalc/component/resistor.hpp>
#include <zcalc/component/capacitor.hpp>
#include <zcalc/component/inductor.hpp>
#include <zcalc/network_calculator.hpp>

TEST(NetworkCalculatorTest, VoltageDivider) {
    zcalc::Network test_network {};
    test_network.add_node ("gnd");
    test_network.add_node ("in");
    test_network.add_node ("out");
    const auto us_id = test_network.add_voltage_source ("Us", 1.0, 0.0, "in", "gnd");
    const auto r1_id = test_network.add_resistor("R1", 10, "in", "out");
    const auto r2_id = test_network.add_resistor("R2", 10, "out", "gnd");

    const auto results = zcalc::NetworkCalculator::compute(test_network);
    ASSERT_EQ(results.size(), 3);

    ASSERT_EQ(results.at(us_id).currents.size(), 1);
    ASSERT_EQ(results.at(us_id).currents[0].to_complex(), zcalc::math::Complex(-0.05, 0.0));
    ASSERT_EQ(results.at(us_id).currents[0].get_frequency(), 0.0);

    ASSERT_EQ(results.at(us_id).voltages.size(), 1);
    ASSERT_EQ(results.at(us_id).voltages[0].to_complex(), zcalc::math::Complex(1.0, 0.0));
    ASSERT_EQ(results.at(us_id).voltages[0].get_frequency(), 0.0);

    ASSERT_EQ(results.at(r1_id).currents.size(), 1);
    ASSERT_EQ(results.at(r1_id).currents[0].to_complex(), zcalc::math::Complex(0.05, 0.0));
    ASSERT_EQ(results.at(r1_id).currents[0].get_frequency(), 0.0);

    ASSERT_EQ(results.at(r1_id).voltages.size(), 1);
    ASSERT_EQ(results.at(r1_id).voltages[0].to_complex(), zcalc::math::Complex(0.5, 0.0));
    ASSERT_EQ(results.at(r1_id).voltages[0].get_frequency(), 0.0);

    ASSERT_EQ(results.at(r2_id).currents.size(), 1);
    ASSERT_EQ(results.at(r2_id).currents[0].to_complex(), zcalc::math::Complex(0.05, 0.0));
    ASSERT_EQ(results.at(r2_id).currents[0].get_frequency(), 0.0);

    ASSERT_EQ(results.at(r2_id).voltages.size(), 1);
    ASSERT_EQ(results.at(r2_id).voltages[0].to_complex(), zcalc::math::Complex(0.5, 0.0));
    ASSERT_EQ(results.at(r2_id).voltages[0].get_frequency(), 0.0);
}

TEST(NetworkCalculatorTest, VoltageResponse) {
    zcalc::Network network {};
    network.add_node ("gnd");
    network.add_node ("in");
    network.add_node ("out");
    network.add_node ("A");
    network.add_voltage_source ("Us", 10.0, 795.8, "in", "gnd"); // 10V, 5krad/s (5/(2pi))
    network.add_capacitor("C1", 2.0e-6, "in", "out"); // 2uF
    network.add_capacitor("C2", 1.0e-6, "out", "gnd"); // 1uF
    network.add_resistor("R", 40, "out", "A"); // 40ohm
    network.add_inductor("L", 8.0e-3, "A", "gnd"); // 8mH
    const auto osci_id = network.add_resistor("osci", 10e9, "out", "gnd");

    const auto results = zcalc::NetworkCalculator::compute(network);
    ASSERT_EQ(results.at(osci_id).voltages.size(), 1);
    ASSERT_EQ(results.at(osci_id).voltages[0].to_complex(), zcalc::math::Complex(1.53888, 7.69266));
    ASSERT_EQ(results.at(osci_id).voltages[0].get_frequency(), 795.8);
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
    network.add_voltage_source ("Us", 24.0, 5000.0, "in", "gnd"); // 24V, 5kHz
    network.add_resistor("R1", 500, "in", "A"); // 500ohm
    network.add_inductor("L", 10.0e-3, "A", "B"); // 10mH
    network.add_resistor("R2", 1000, "B", "gnd"); // 1kohm
    const auto r_id = network.add_resistor("R3", 800, "B", "out"); // 800ohm
    network.add_resistor("R4", 600, "out", "gnd"); // 600ohm
    const auto c_id = network.add_capacitor("C", 120.0e-9, "out", "gnd"); // 120nF

    const auto results = zcalc::NetworkCalculator::compute(network);
    ASSERT_EQ(results.at(c_id).voltages.size(), 1);
    ASSERT_EQ(results.at(c_id).voltages[0].to_complex(), zcalc::math::Complex(0.830672, -2.89235));
    ASSERT_EQ(results.at(c_id).voltages[0].get_frequency(), 5000.0);

    ASSERT_EQ(results.at(r_id).currents.size(), 1);
    ASSERT_EQ(results.at(r_id).currents[0].to_complex(), zcalc::math::Complex(0.0122884, -0.00168902));
    ASSERT_EQ(results.at(r_id).currents[0].get_frequency(), 5000.0);
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

    network.add_voltage_source ("U1", 4.0, 0.0, "A", "gnd"); // 4VDC
    network.add_voltage_source ("U2", std::sqrt(2.0) * 6.0, 10.0e3 / (2.0 * zcalc::pi), "D", "gnd"); // sqrt(2)* 6V, 10krad/s (1591.5Hz)

    network.add_resistor("R1", 10, "B", "A"); // 10ohm
    const auto r_id = network.add_resistor("R2", 50, "B", "gnd"); // 50ohm
    network.add_resistor("R3", 5, "B", "C"); // 5ohm
    network.add_inductor("L", 1.0e-3, "C", "D"); // 1mH

    const auto results = zcalc::NetworkCalculator::compute(network);
    ASSERT_EQ(results.at(r_id).currents.size(), 2);
    ASSERT_EQ(results.at(r_id).currents[0].to_complex(), zcalc::math::Complex(0.025, 0.0));
    ASSERT_EQ(results.at(r_id).currents[0].get_frequency(), 0.0);
    ASSERT_NEAR(results.at(r_id).currents[1].to_complex().real(), 0.0678555, 0.0001);
    ASSERT_NEAR(results.at(r_id).currents[1].to_complex().imag(), -0.0509473, 0.0001);
    ASSERT_EQ(results.at(r_id).currents[1].get_frequency(), 10.0e3 / (2.0 * zcalc::pi));
}