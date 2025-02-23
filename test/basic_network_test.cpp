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
    const auto us_id = test_network.add_source ("Us", 1.0, "in", "gnd");
    const auto r1_id = test_network.add_resistor("R1", 10, "in", "out");
    const auto r2_id = test_network.add_resistor("R2", 10, "out", "gnd");

    const auto results = zcalc::NetworkCalculator::compute(test_network);
    ASSERT_EQ(results.size(), 3);
    bool us_found = false;
    bool r1_found = false;
    bool r2_found = false;

    for (const auto& res : results) {
        if (res.component_id == us_id) {
            us_found = true;
            ASSERT_EQ(res.current, zcalc::math::Complex(-0.05, 0.0));
            ASSERT_EQ(res.voltage, zcalc::math::Complex(1.0, 0.0));
        }
        else if (res.component_id == r1_id) {
            r1_found = true;
            ASSERT_EQ(res.current, zcalc::math::Complex(0.05, 0.0));
            ASSERT_EQ(res.voltage, zcalc::math::Complex(0.5, 0.0));
        }
        else if (res.component_id == r2_id) {
            r2_found = true;
            ASSERT_EQ(res.current, zcalc::math::Complex(0.05, 0.0));
            ASSERT_EQ(res.voltage, zcalc::math::Complex(0.5, 0.0));
        }
        else {
            ASSERT_TRUE(false);
        }
    }

    ASSERT_TRUE(us_found);
    ASSERT_TRUE(r1_found);
    ASSERT_TRUE(r2_found);
}

TEST(BasicNetworkTest, VoltageResponse) {
    zcalc::Network network {};
    network.set_frequency(795.8);
    network.add_node ("gnd");
    network.add_node ("in");
    network.add_node ("out");
    network.add_node ("A");
    const auto us_id = network.add_source ("Us", 10.0, "in", "gnd");
    const auto c1_id = network.add_capacitor("C1", 2.0e-6, "in", "out");
    const auto c2_id = network.add_capacitor("C2", 1.0e-6, "out", "gnd");
    const auto r_id = network.add_resistor("R", 40, "out", "A");
    const auto l_id = network.add_inductor("L", 8.0e-3, "A", "gnd");
    const auto osci_id = network.add_resistor("osci", 10e9, "out", "gnd");

    const auto results = zcalc::NetworkCalculator::compute(network);
    bool osci_found = false;
    for (const auto& res : results) {
        if (res.component_id == osci_id) {
            osci_found = true;
            ASSERT_EQ(res.voltage, zcalc::math::Complex(1.53888, 7.69266));
        }
    }
    ASSERT_TRUE(osci_found);
}