#include <gtest/gtest.h>

#include <zcalc/graph/graph.hpp>

TEST(GraphTest, UndirectedGraphTest) {
    zcalc::graph::Graph<float> g(5);
    g.add_edge(0, 1, 1.0f);
    g.add_edge(1, 2, 1.0f);
    g.add_edge(2, 0, 1.0f);
    g.add_edge(2, 3, 1.0f);
    g.add_edge(3, 4, 1.0f);
    g.add_edge(4, 2, 1.0f);

    std::cerr << g << std::endl;

    std::cerr << "Cycles in the graph:\n";
    auto cycles = g.find_cycles();
    for (const auto &cycle : cycles) {
        std::cerr << cycle << std::endl;
    }

    // ASSERT_TRUE(cycles.contains({0, 1, 2}));
    // ASSERT_TRUE(cycles.contains({0, 2, 1}));
    // ASSERT_TRUE(cycles.contains({1, 0, 2}));
    // ASSERT_TRUE(cycles.contains({1, 2, 0}));
    // ASSERT_TRUE(cycles.contains({2, 0, 1}));
    // ASSERT_TRUE(cycles.contains({2, 1, 0}));
    // ASSERT_TRUE(cycles.contains({2, 3, 4}));
    // ASSERT_TRUE(cycles.contains({2, 4, 3}));
    // ASSERT_TRUE(cycles.contains({3, 2, 4}));
    // ASSERT_TRUE(cycles.contains({3, 4, 2}));
    // ASSERT_TRUE(cycles.contains({4, 2, 3}));
    // ASSERT_TRUE(cycles.contains({4, 3, 2}));
}

TEST(GraphTest, DirectedGraphTest) {
    zcalc::graph::Graph<float> g(4);
    g.add_edge(0, 1, 1.0f, zcalc::graph::edge_direction::bidirectional);
    g.add_edge(1, 2, 1.0f, zcalc::graph::edge_direction::bidirectional);
    g.add_edge(2, 0, 1.0f, zcalc::graph::edge_direction::forward);
    g.add_edge(2, 3, 1.0f, zcalc::graph::edge_direction::bidirectional);
    g.add_edge(3, 1, 1.0f, zcalc::graph::edge_direction::reverse);

    std::cerr << g << std::endl;

    std::cerr << "Cycles in the graph:\n";
    auto cycles = g.find_cycles();
    for (const auto &cycle : cycles) {
        std::cerr << cycle << std::endl;
    }
    
    // ASSERT_TRUE(cycles.contains({0, 1, 2}));
    // ASSERT_TRUE(cycles.contains({0, 1, 3, 2}));
    // ASSERT_TRUE(cycles.contains({1, 2, 0}));
    // ASSERT_TRUE(cycles.contains({1, 3, 2}));
    // ASSERT_TRUE(cycles.contains({1, 3, 2, 0}));
    // ASSERT_TRUE(cycles.contains({2, 0, 1}));
    // ASSERT_TRUE(cycles.contains({2, 0, 1, 3}));
    // ASSERT_TRUE(cycles.contains({2, 1, 3}));
    // ASSERT_TRUE(cycles.contains({3, 2, 0, 1}));
    // ASSERT_TRUE(cycles.contains({3, 2, 1}));

}