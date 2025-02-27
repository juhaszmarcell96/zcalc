#include <gtest/gtest.h>

#include <zcalc/graph/path.hpp>

using namespace zcalc::graph;

TEST(EdgeTest, ConstructorInitializesCorrectly) {
    Edge<int> edge(1, 2, 10, edge_direction::forward);
    EXPECT_EQ(edge.get_v0(), 1);
    EXPECT_EQ(edge.get_v1(), 2);
    EXPECT_EQ(edge.get_weight(), 10);
    EXPECT_EQ(edge.get_direction(), edge_direction::forward);
}

TEST(EdgeTest, TraversalFunctions) {
    Edge<int> edge(1, 2, 5);
    EXPECT_FALSE(edge.was_traversed());
    edge.traverse();
    EXPECT_TRUE(edge.was_traversed());
    edge.reset();
    EXPECT_FALSE(edge.was_traversed());
}

TEST(EdgeTest, FlipFunction) {
    Edge<int> edge(1, 2, 5, edge_direction::forward);
    edge.flip();
    EXPECT_EQ(edge.get_v0(), 2);
    EXPECT_EQ(edge.get_v1(), 1);
    EXPECT_EQ(edge.get_direction(), edge_direction::reverse);
}

TEST(EdgeTest, EqualityOperator) {
    Edge<int> edge1(1, 2, 5, edge_direction::forward);
    Edge<int> edge2(1, 2, 5, edge_direction::forward);
    Edge<int> edge3(2, 1, 5, edge_direction::reverse);
    Edge<int> edge4(1, 2, 5, edge_direction::bidirectional);
    
    EXPECT_TRUE(edge1 == edge2);
    EXPECT_TRUE(edge1 == edge3);
    EXPECT_FALSE(edge1 == edge4);
}

TEST(EdgeTest, OutputStreamOperator) {
    Edge<int> edge(1, 2, 5, edge_direction::forward);
    std::ostringstream os;
    os << edge;
    EXPECT_EQ(os.str(), "1 --(5)-> 2");
}