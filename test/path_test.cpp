#include <gtest/gtest.h>

#include <zcalc/graph/path.hpp>

using namespace zcalc::graph;

TEST(PathTest, BuildPathTest) {
    Path<int> p;

    Edge<int> e1 { 0, 1, 100, edge_direction::bidirectional };

    // cannot start with an edge
    EXPECT_THROW(p.push_back_e(&e1), std::invalid_argument);
    // start with a vertex
    p.push_back_v(0);
    // cannot push a nullptr
    EXPECT_THROW(p.push_back_e(nullptr), std::invalid_argument);
    // push e1
    p.push_back_e(&e1);
    p.push_back_v(1);
}

TEST(PathTest, BidirectionalContainsTest) {
    Path<int> p;

    Edge<int> e1 { 0, 1, 100, edge_direction::bidirectional };
    p.push_back_v(0);
    p.push_back_e(&e1);
    p.push_back_v(1);

    ASSERT_TRUE(p.contains(0, 1, 100, edge_direction::bidirectional));
    ASSERT_TRUE(p.contains(1, 0, 100, edge_direction::bidirectional)); // contained in both directions
    ASSERT_FALSE(p.contains(2, 1, 100, edge_direction::bidirectional)); // invalid v0
    ASSERT_FALSE(p.contains(0, 2, 100, edge_direction::bidirectional)); // invalid v1
    ASSERT_FALSE(p.contains(0, 1, 101, edge_direction::bidirectional)); // invalid weight
    ASSERT_FALSE(p.contains(0, 1, 100, edge_direction::forward)); // invalid direction
}

TEST(PathTest, DirectedContainsTest) {
    Path<int> p;

    Edge<int> e1 { 0, 1, 100, edge_direction::forward };
    p.push_back_v(0);
    p.push_back_e(&e1);
    p.push_back_v(1);

    ASSERT_TRUE(p.contains(0, 1, 100, edge_direction::forward));
    ASSERT_TRUE(p.contains(1, 0, 100, edge_direction::reverse)); // contained in both directions
    ASSERT_FALSE(p.contains(2, 1, 100, edge_direction::forward)); // invalid v0
    ASSERT_FALSE(p.contains(0, 2, 100, edge_direction::forward)); // invalid v1
    ASSERT_FALSE(p.contains(0, 1, 101, edge_direction::forward)); // invalid weight
    ASSERT_FALSE(p.contains(0, 1, 100, edge_direction::bidirectional)); // invalid direction
}