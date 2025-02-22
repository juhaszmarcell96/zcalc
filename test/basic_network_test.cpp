#include <gtest/gtest.h>

#include <zcalc/common.hpp>
#include <zcalc/network.hpp>
#include <zcalc/component/resistor.hpp>
#include <zcalc/component/capacitor.hpp>
#include <zcalc/component/inductor.hpp>
#include <zcalc/network_calculator.hpp>

TEST(BasicNetworkTest, Test) {
    zcalc::Network test_network {};
    test_network.add_node ("gnd");
    test_network.add_node ("in");
    test_network.add_node ("out");
    test_network.add_source ("Us", 1.0, "in", "gnd");
    test_network.add_resistor("R1", 10, "in", "out");
    test_network.add_resistor("R2", 10, "out", "gnd");
    
    auto g = test_network.to_graph();
    auto cycles = g.find_cycles();
    for (const auto& c : cycles) {
        const auto& edges = c.get_edges();
        for (const auto e : edges) {
            std::cerr << e->v0;
            if (e->direction == zcalc::graph::edge_direction::bidirectional) {
                std::cerr << " --(" << test_network.get_designator_of_component(e->weight).value() << ")-- ";
            }
            else if (e->direction == zcalc::graph::edge_direction::forward) {
                std::cerr << " --(" << test_network.get_designator_of_component(e->weight).value() << ")-> ";
            }
            else { // reverse
                std::cerr << " <-(" << test_network.get_designator_of_component(e->weight).value() << ")-- ";
            }
            std::cerr << e->v1 << "|";
        }
        std::cerr << std::endl;
    }

    zcalc::NetworkCalculator::compute(test_network);
}