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