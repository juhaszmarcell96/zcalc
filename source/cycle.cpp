#include <include/cycle.hpp>

namespace zcalc {

bool Cycle::add_node (Node* node_ptr) {
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

bool Cycle::add_component (Component* component_ptr) {
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

bool operator==(const Cycle& cycle_1, const Cycle& cycle_2) {
    /* make a vector of strings out of them, sort them and compare them */
}

bool operator!=(const Cycle& cycle_1, const Cycle& cycle_2) {

}

} /* namespace zcalc */