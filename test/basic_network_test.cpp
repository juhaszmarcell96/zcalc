#include <gtest/gtest.h>

#include <zcalc/common.hpp>
#include <zcalc/network.hpp>
#include <zcalc/component/resistor.hpp>
#include <zcalc/component/capacitor.hpp>
#include <zcalc/component/inductor.hpp>
#include <zcalc/network_calculator.hpp>

TEST(BasicNetworkTest, VoltageDivider) {
    zcalc::Network test_network {};
    test_network.add_node ("gnd");
    test_network.add_node ("in");
    test_network.add_node ("out");
    const auto us_id = test_network.add_voltage_source ("Us", 1.0, 0.0, "in", "gnd");
    const auto r1_id = test_network.add_resistor("R1", 10, "in", "out");
    const auto r2_id = test_network.add_resistor("R2", 10, "out", "gnd");

    const auto results = zcalc::NetworkCalculator::compute(test_network);
    ASSERT_EQ(results.size(), 3);
    ASSERT_EQ(results.at(us_id).current, zcalc::math::Complex(-0.05, 0.0));
    ASSERT_EQ(results.at(us_id).voltage, zcalc::math::Complex(1.0, 0.0));
    ASSERT_EQ(results.at(r1_id).current, zcalc::math::Complex(0.05, 0.0));
    ASSERT_EQ(results.at(r1_id).voltage, zcalc::math::Complex(0.5, 0.0));
    ASSERT_EQ(results.at(r2_id).current, zcalc::math::Complex(0.05, 0.0));
    ASSERT_EQ(results.at(r2_id).voltage, zcalc::math::Complex(0.5, 0.0));
}

TEST(BasicNetworkTest, VoltageResponse) {
    zcalc::Network network {};
    network.add_node ("gnd");
    network.add_node ("in");
    network.add_node ("out");
    network.add_node ("A");
    const auto us_id = network.add_voltage_source ("Us", 10.0, 795.8, "in", "gnd"); // 10V, 5krad/s (5/(2pi))
    const auto c1_id = network.add_capacitor("C1", 2.0e-6, "in", "out"); // 2uF
    const auto c2_id = network.add_capacitor("C2", 1.0e-6, "out", "gnd"); // 1uF
    const auto r_id = network.add_resistor("R", 40, "out", "A"); // 40ohm
    const auto l_id = network.add_inductor("L", 8.0e-3, "A", "gnd"); // 8mH
    const auto osci_id = network.add_resistor("osci", 10e9, "out", "gnd");

    const auto results = zcalc::NetworkCalculator::compute(network);
    ASSERT_EQ(results.at(osci_id).voltage, zcalc::math::Complex(1.53888, 7.69266));
}

TEST(BasicNetworkTest, VoltageAndCurrentResponse) {
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
    ASSERT_EQ(results.at(c_id).voltage, zcalc::math::Complex(0.830672, -2.89235));
    ASSERT_EQ(results.at(r_id).current, zcalc::math::Complex(0.0122884, -0.00168902));
}