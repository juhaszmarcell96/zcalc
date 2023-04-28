#pragma once

#include <include/node.hpp>
#include <include/component.hpp>

#include <memory>

namespace zcalc {

/* a cycle starts in a node and ends in a component */

struct CycleComponent;

struct CycleNode {
    Node* node_ptr = nullptr;
    std::shared_ptr<CycleComponent> next_ptr = nullptr;
};

struct CycleComponent {
    Component* component_ptr = nullptr;
    std::shared_ptr<CycleNode> next_ptr = nullptr;
};

class Cycle {
private:
    std::shared_ptr<CycleNode> m_root = nullptr;
public:
    Cycle() = default;
    ~Cycle() = default;

    bool add_node (Node* node_ptr);
    bool add_component (Component* component_ptr);

    friend bool operator==(const Cycle& cycle_1, const Cycle& cycle_2);
    friend bool operator!=(const Cycle& cycle_1, const Cycle& cycle_2);
};

} /* namespace zcalc */