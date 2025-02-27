#include <gtest/gtest.h>

#include <zcalc/graph/path.hpp>

using namespace zcalc::graph;

TEST(PathTest, BuildPathTest) {
    Path<int> p { 0 };

    Edge<int> e1 { 0, 1, 100, edge_direction::bidirectional };
    Edge<int> e2 { 1, 2, 101, edge_direction::bidirectional };
    Edge<int> e3 { 2, 3, 102, edge_direction::bidirectional };

    // must start at start...
    EXPECT_THROW(p.push_back(e2), std::invalid_argument);
    p.push_back(e1);
    // must be continuous
    EXPECT_THROW(p.push_back(e3), std::invalid_argument);
    p.push_back(e2);
    p.push_back(e3);
}

TEST(PathTest, BidirectionalContainsTest) {
    Path<int> p { 0 };

    Edge<int> e1 { 0, 1, 100, edge_direction::bidirectional };
    p.push_back(e1);

    ASSERT_TRUE(p.contains(0, 1, 100, edge_direction::bidirectional));
    ASSERT_TRUE(p.contains(1, 0, 100, edge_direction::bidirectional)); // contained in both directions
    ASSERT_FALSE(p.contains(2, 1, 100, edge_direction::bidirectional)); // invalid v0
    ASSERT_FALSE(p.contains(0, 2, 100, edge_direction::bidirectional)); // invalid v1
    ASSERT_FALSE(p.contains(0, 1, 101, edge_direction::bidirectional)); // invalid weight
    ASSERT_FALSE(p.contains(0, 1, 100, edge_direction::forward)); // invalid direction
}

TEST(PathTest, DirectedContainsTest) {
    Path<int> p { 0 };

    Edge<int> e1 { 0, 1, 100, edge_direction::forward };
    p.push_back(e1);

    ASSERT_TRUE(p.contains(0, 1, 100, edge_direction::forward));
    ASSERT_TRUE(p.contains(1, 0, 100, edge_direction::reverse)); // contained in both directions
    ASSERT_FALSE(p.contains(2, 1, 100, edge_direction::forward)); // invalid v0
    ASSERT_FALSE(p.contains(0, 2, 100, edge_direction::forward)); // invalid v1
    ASSERT_FALSE(p.contains(0, 1, 101, edge_direction::forward)); // invalid weight
    ASSERT_FALSE(p.contains(0, 1, 100, edge_direction::bidirectional)); // invalid direction
}

TEST(PathTest, EdgeFitsPathTest) {
    Path<int> p { 0 };

    Edge<int> e1 { 0, 1, 100, edge_direction::bidirectional };
    Edge<int> e2 { 1, 2, 101, edge_direction::bidirectional };
    Edge<int> e3 { 3, 2, 102, edge_direction::reverse };
    Edge<int> e4 { 0, 1, 102, edge_direction::reverse };

    ASSERT_TRUE(p.fits(e1));
    ASSERT_FALSE(p.fits(e2));
    ASSERT_FALSE(p.fits(e3));
    ASSERT_FALSE(p.fits(e4)); // starts at 0, edge 0 <- 1 is not a fit
    p.push_back(e1);
    ASSERT_TRUE(p.fits(e1)); // goes back to the start on the same edge, TODO : should this be allowed?
    ASSERT_TRUE(p.fits(e2));
    ASSERT_FALSE(p.fits(e3));
    ASSERT_TRUE(p.fits(e4));
}

TEST(PathTest, EndTest) {
    Path<int> p { 0 };

    Edge<int> e1 { 0, 1, 100, edge_direction::bidirectional };
    Edge<int> e2 { 1, 2, 101, edge_direction::bidirectional };
    Edge<int> e3 { 3, 2, 102, edge_direction::reverse };

    ASSERT_EQ(p.get_end(), 0);
    p.push_back(e1);
    ASSERT_EQ(p.get_end(), 1);
    p.push_back(e2);
    ASSERT_EQ(p.get_end(), 2);
    p.push_back(e3);
    ASSERT_EQ(p.get_end(), 3);
}