#include <gtest/gtest.h>

#include <zcalc/common.hpp>
#include <zcalc/network.hpp>
#include <zcalc/component/resistor.hpp>
#include <zcalc/component/capacitor.hpp>
#include <zcalc/component/inductor.hpp>

TEST(BasicNetworkTest, Test) {
    zcalc::Network test_network {};
    test_network.add_resistor("R1", 10, "in", "out");
    test_network.add_resistor("R2", 10, "out", "gnd");
    
    auto g = test_network.to_graph();
    std::cerr << g << std::endl;
}