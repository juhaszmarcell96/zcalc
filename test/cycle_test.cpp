#include <gtest/gtest.h>

#include <include/cycle.hpp>
#include <include/node.hpp>
#include <include/component.hpp>
#include <include/resistor.hpp>

TEST(CycleTest, NullptrTest) {
    zcalc::Cycle cycle;

    bool success = false;

    /* cannot append nullptr */

    success = cycle.add_node(nullptr);
    ASSERT_EQ(success, false);

    success = cycle.add_component(nullptr);
    ASSERT_EQ(success, false);
}

TEST(CycleTest, AppendTest) {
    zcalc::Cycle cycle;

    bool success = false;

    /* cycle cannot start with a component */
    zcalc::Resistor resistor_0 { 5.0 };
    success = cycle.add_component(&resistor_0);
    ASSERT_EQ(success, false);

    /* cycle can only start with a node */
    zcalc::Node node_0;
    success = cycle.add_node(&node_0);
    ASSERT_EQ(success, true);

    /* node cannot be appended to a cycle ending in a node */
    zcalc::Node node_1;
    success = cycle.add_node(&node_1);
    ASSERT_EQ(success, false);

    /* a component can be appended to the cycle ending in a node */
    success = cycle.add_component(&resistor_0);
    ASSERT_EQ(success, true);

    /* component cannot be appended to a cycle ending in a component */
    zcalc::Resistor resistor_1 { 5.0 };
    success = cycle.add_component(&resistor_1);
    ASSERT_EQ(success, false);

    /* the same node cannot be added twice */
    success = cycle.add_node(&node_0);
    ASSERT_EQ(success, false);

    /* a new node can be appended to a cycle ending in a component */
    success = cycle.add_node(&node_1);
    ASSERT_EQ(success, true);

    /* the same component cannot be appended twice */
    success = cycle.add_component(&resistor_0);
    ASSERT_EQ(success, false);

    /* a new component can be appended */
    success = cycle.add_component(&resistor_1);
    ASSERT_EQ(success, true);
}