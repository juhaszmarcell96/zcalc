#pragma once

#include <zcalc/node.hpp>
#include <zcalc/component.hpp>

#include <memory>
#include <vector>
#include <cstdint>
#include <algorithm>
#include <iostream>

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

struct NodeNeighbors {
    Node* node_ptr_0 = nullptr;
    Node* node_ptr_1 = nullptr;
};

class Cycle {
private:
    std::shared_ptr<CycleNode> m_root = nullptr;

    std::vector<std::uintptr_t> to_ptr_vec () const {
        std::vector<std::uintptr_t> vec;
        if (m_root == nullptr) return std::move(vec);
        CycleNode* current_node = m_root.get();
        CycleComponent* current_component = nullptr;
        while (true) {
            if (current_node == nullptr) break;
            vec.push_back(reinterpret_cast<std::uintptr_t>(current_node->node_ptr));
            current_component = current_node->next_ptr.get();
            if (current_component == nullptr) break;
            vec.push_back(reinterpret_cast<std::uintptr_t>(current_component->component_ptr));
            current_node = current_component->next_ptr.get();
        }
        return std::move(vec);
    }
public:
    Cycle() = default;
    ~Cycle() = default;

    bool add_node (Node* node_ptr) {
        if (node_ptr == nullptr) return false;
        if (m_root == nullptr) {
            m_root = std::make_shared<CycleNode>();
            m_root->node_ptr = node_ptr;
            m_root->next_ptr = nullptr;
            return true;
        }

        if (m_root->next_ptr == nullptr) return false; /* cannot append node to node */
        if (m_root->node_ptr == node_ptr) return false; /* cannot append the same node twice */
        CycleComponent* current_component = m_root->next_ptr.get();
        while (current_component->next_ptr != nullptr) {
            CycleNode* current_node = current_component->next_ptr.get();
            if (current_node->next_ptr == nullptr) return false; /* the last element is a node, cannot append a node */
            if (current_node->node_ptr == node_ptr) return false; /* detect infinite loops */
            current_component = current_node->next_ptr.get();
        }
        std::shared_ptr<CycleNode> new_node = std::make_shared<CycleNode>();
        new_node->node_ptr = node_ptr;
        new_node->next_ptr = nullptr;
        current_component->next_ptr = new_node;
        return true;
    }

    bool add_component (Component* component_ptr) {
        if (component_ptr == nullptr) return false;
        if (m_root == nullptr) return false; /* cycle cannot start with a component */
        CycleNode* current_node = m_root.get();
        while (current_node->next_ptr != nullptr) {
            CycleComponent* current_component = current_node->next_ptr.get();
            if (current_component->next_ptr == nullptr) return false; /* the last element is a component, cannot append a component */
            if (current_component->component_ptr == component_ptr) return false; /* detect infinite loops */
            current_node = current_component->next_ptr.get();
        }
        std::shared_ptr<CycleComponent> new_component = std::make_shared<CycleComponent>();
        new_component->component_ptr = component_ptr;
        new_component->next_ptr = nullptr;
        current_node->next_ptr = new_component;
        return true;
    }

    void print() const {
        if (m_root == nullptr) return;
        CycleNode* current_node = m_root.get();
        CycleComponent* current_component = nullptr;
        while (true) {
            if (current_node == nullptr) return;
            std::cout << " -> " << current_node->node_ptr->name;
            current_component = current_node->next_ptr.get();
            if (current_component == nullptr) return;
            std::cout << " -> " << current_component->component_ptr->get_designator();
            current_node = current_component->next_ptr.get();
        }
    }

    friend bool operator==(const Cycle& cycle_1, const Cycle& cycle_2) {
        /* make a vector of strings out of them, sort them and compare them */
        std::vector<std::uintptr_t> vec_1 = cycle_1.to_ptr_vec();
        std::vector<std::uintptr_t> vec_2 = cycle_2.to_ptr_vec();
        if (vec_1.size() != vec_2.size()) return false;
        std::sort(vec_1.begin(), vec_1.end());
        std::sort(vec_2.begin(), vec_2.end());
        for (std::size_t i = 0; i < vec_1.size(); ++i) {
            if (vec_1[i] != vec_2[i]) return false;
        }
        return true;
    }

    friend bool operator!=(const Cycle& cycle_1, const Cycle& cycle_2) {
        return !(cycle_1 == cycle_2);
    }

    std::shared_ptr<CycleNode> get_root () { return m_root; }

    std::vector<NodeNeighbors> get_neighboring_nodes () const {
        std::vector<NodeNeighbors> vec;
        if (m_root == nullptr) return std::move(vec);
        CycleNode* current_node = m_root.get();
        CycleComponent* current_component = nullptr;
        while (true) {
            NodeNeighbors neighbors;
            if (current_node == nullptr) break;
            neighbors.node_ptr_0 = current_node->node_ptr;
            current_component = current_node->next_ptr.get();
            if (current_component == nullptr) break;
            CycleNode* next_current_node = current_component->next_ptr.get();
            if (next_current_node == nullptr) break;
            current_node = next_current_node;
            neighbors.node_ptr_1 = current_node->node_ptr;
            vec.push_back(neighbors);
        }
        if (current_node != m_root.get()) {
            NodeNeighbors neighbors;
            neighbors.node_ptr_0 = current_node->node_ptr;
            neighbors.node_ptr_1 = m_root->node_ptr;
        }
        return std::move(vec);
    }
};

} /* namespace zcalc */