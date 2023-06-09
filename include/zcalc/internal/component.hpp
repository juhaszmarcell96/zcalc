#pragma once

#include <vector>
#include <string>
#include <memory>

#include <zcalc/internal/linear_equation.hpp>

namespace zcalc {

/* forward declarations */
class Node;
class Component;
class LoopMessage;

/* gate class, used in components */
/* one gate can connect to one node */
/* each gate has a reference to the component that contains it */
struct Gate {
    std::string designator;
    Node* node;
    Component* component;
};

/* node class, equivalent to a node in an electrical circuit */
/* each node has an array of gates that are connected to it */
struct Node {
    std::string designator;
    std::vector<Gate*> gates;

    void propagate (LoopMessage message, const Gate* source_gate);
};



class LoopMessage {
private:
    std::vector<Node*> m_nodes;
public:
    LoopMessage () = delete;
    LoopMessage (Node* starting_node, std::size_t num_variables) : equ(num_variables) {}
    ~LoopMessage() = default;

    LinearEquation<Complex> equ;

    bool contains (const Node* node) const {
        for (const Node* n : m_nodes) { if (n == node) return true; }
        return false;
    }

    void add_node (Node* node) { m_nodes.push_back(node); }

    bool is_starting_node (const Node* node) const { return node == m_nodes[0]; }

    bool get_num_nodes () const { return m_nodes.size(); }

    void print () {
        for (const Node* node : m_nodes) {
            std::cout << node->designator;
            if (node != m_nodes.back()) std::cout << " -> ";
        }
        std::cout << std::endl;
    }
};


class LoopFinder {
private:
    static inline std::vector<LoopMessage> m_loops;
public:
    LoopFinder () = default;
    ~LoopFinder() = default;

    static inline void find_loops (Node* starting_node, std::size_t num_variables) {
        m_loops.clear();
        LoopMessage message { starting_node, num_variables };
        starting_node->propagate(message, nullptr);
    }

    static inline void append_loop(LoopMessage message) {
        m_loops.push_back(message);
    }

    static inline std::vector<LoopMessage>& get_loops () { return m_loops; }
};




class Component {
private:
    std::size_t m_id;
protected:
    std::vector<std::unique_ptr<Gate>> m_gates;
    std::string m_designator;
public:
    Component () = delete;
    Component (const std::string& designator, std::size_t id) : m_designator(designator), m_id(id) {}
    virtual ~Component() = default;

    const std::string& get_designator () const { return m_designator; }
    std::size_t get_id () const { return m_id; }

    virtual std::size_t get_num_variables () const = 0;
    virtual void kcl(const Node* node, LinearEquation<Complex>& equ) const = 0;
    virtual void own_equ(LinearEquation<Complex>& equ) const = 0;

    virtual void propagate (LoopMessage message, const Gate* gate) const = 0;
};



inline void Node::propagate (LoopMessage message, const Gate* source_gate) {
    if (message.contains(this)) {
        if (message.is_starting_node(this)) {
            /* this is a valid loop -> push it to the stack */
            //message.print();
            LoopFinder::append_loop(std::move(message));
            return;
        }
        else {
            /* this is not a valid loop */
            return;
        }
    }
    message.add_node(this);
    for (Gate* gate : gates) {
        /* pass the message to the connected gates but not the gate it is coming from */
        if (gate != source_gate) gate->component->propagate(message, gate);
    }
}

} /* namespace zcalc */