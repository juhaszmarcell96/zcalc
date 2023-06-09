#pragma once

#include <zcalc/internal/node.hpp>
#include <zcalc/internal/gate.hpp>
#include <zcalc/internal/component.hpp>
#include <zcalc/internal/linear_equation.hpp>

namespace zcalc {

class LoopMessage {
private:
    static inline std::vector<LoopMessage> m_loops;
    std::vector<Node*> m_nodes;
    LoopMessage (Node* starting_node, std::size_t num_variables) : equ(num_variables) {
        m_nodes.push_back(starting_node);
    }
public:
    LoopMessage () = delete;
    ~LoopMessage() = default;

    LinearEquation<Complex> equ;

    bool contains (const Node* node) const {
        for (const Node* n : m_nodes) {
            if (n == node) return true;
        }
        return false;
    }

    bool is_starting_node (const Node* node) const {
        return node == m_nodes[0];
    }

    bool get_num_nodes () const { return m_nodes.size(); }

    static inline void find_loops (Node* starting_node, std::size_t num_variables) {
        m_loops.clear();
        LoopMessage message { starting_node, num_variables };
        starting_node->propagate(message, nullptr);
    }

    static inline void append_loop(LoopMessage message) {
        m_loops.push_back(message);
    }
};

} /* namespace zcalc */
