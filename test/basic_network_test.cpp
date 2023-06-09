#include <gtest/gtest.h>

#include <zcalc/common.hpp>
#include <zcalc/network.hpp>
#include <zcalc/resistor.hpp>
#include <zcalc/capacitor.hpp>
#include <zcalc/inductor.hpp>

TEST(BasicNetworkTest, Test) {
    zcalc::Network test_network { 50.0e3 };
    test_network.add_node("gnd");
    test_network.add_node("in");
    test_network.add_node("out");
    test_network.add_source("U1", 5, "in", "gnd");
    test_network.add_resistor("R1", 10, "in", "out");
    test_network.add_resistor("R2", 10, "out", "gnd");
    std::vector<zcalc::Complex> result = test_network.compute();

    ASSERT_EQ(result[0], zcalc::Complex(-0.25, 0.0));
    ASSERT_EQ(result[1], zcalc::Complex(5.0, 0.0));
    ASSERT_EQ(result[2], zcalc::Complex(0.25, 0.0));
    ASSERT_EQ(result[3], zcalc::Complex(2.5, 0.0));
    ASSERT_EQ(result[4], zcalc::Complex(0.25, 0.0));
    ASSERT_EQ(result[5], zcalc::Complex(2.5, 0.0));
}