#include <gtest/gtest.h>

#include <zcalc/graph/graph.hpp>

TEST(GraphTest, UndirectedGraphTest) {
    zcalc::graph::Graph g(5);
    g.add_edge(0, 1);
    g.add_edge(1, 2);
    g.add_edge(2, 0);
    g.add_edge(2, 3);
    g.add_edge(3, 4);
    g.add_edge(4, 2);

    std::cerr << "Cycles in the graph:\n";
    auto cycles = g.find_cycles();
    for (const auto &cycle : cycles) {
        for (zcalc::graph::Vertex node : cycle) {
            std::cerr << node << " ";
        }
        std::cerr << std::endl;
    }

    ASSERT_TRUE(cycles.contains({0, 1, 2}));
    ASSERT_TRUE(cycles.contains({0, 2, 1}));
    ASSERT_TRUE(cycles.contains({1, 0, 2}));
    ASSERT_TRUE(cycles.contains({1, 2, 0}));
    ASSERT_TRUE(cycles.contains({2, 0, 1}));
    ASSERT_TRUE(cycles.contains({2, 1, 0}));
    ASSERT_TRUE(cycles.contains({2, 3, 4}));
    ASSERT_TRUE(cycles.contains({2, 4, 3}));
    ASSERT_TRUE(cycles.contains({3, 2, 4}));
    ASSERT_TRUE(cycles.contains({3, 4, 2}));
    ASSERT_TRUE(cycles.contains({4, 2, 3}));
    ASSERT_TRUE(cycles.contains({4, 3, 2}));
}

TEST(GraphTest, DirectedGraphTest) {
    zcalc::graph::Graph g(4);
    g.add_edge(0, 1, zcalc::graph::edge_direction::bidirectional);
    g.add_edge(1, 2, zcalc::graph::edge_direction::bidirectional);
    g.add_edge(2, 0, zcalc::graph::edge_direction::forward);
    g.add_edge(2, 3, zcalc::graph::edge_direction::bidirectional);
    g.add_edge(3, 1, zcalc::graph::edge_direction::reverse);

    std::cerr << "Cycles in the graph:\n";
    auto cycles = g.find_cycles();
    for (const auto &cycle : cycles) {
        for (zcalc::graph::Vertex node : cycle) {
            std::cerr << node << " ";
        }
        std::cerr << std::endl;
    }
    ASSERT_TRUE(cycles.contains({0, 1, 2}));
    ASSERT_TRUE(cycles.contains({0, 1, 3, 2}));
    ASSERT_TRUE(cycles.contains({1, 2, 0}));
    ASSERT_TRUE(cycles.contains({1, 3, 2}));
    ASSERT_TRUE(cycles.contains({1, 3, 2, 0}));
    ASSERT_TRUE(cycles.contains({2, 0, 1}));
    ASSERT_TRUE(cycles.contains({2, 0, 1, 3}));
    ASSERT_TRUE(cycles.contains({2, 1, 3}));
    ASSERT_TRUE(cycles.contains({3, 2, 0, 1}));
    ASSERT_TRUE(cycles.contains({3, 2, 1}));

}