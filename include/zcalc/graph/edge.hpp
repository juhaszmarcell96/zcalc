#pragma once

#include <algorithm>

#include "zcalc/graph/vertex.hpp"

namespace zcalc {
namespace graph {

enum class edge_direction {
    bidirectional, // 0 <-> 1
    forward,       // 0 -> 1
    reverse        // 0 <- 1
};

template<typename T>
class Edge {
private:
    Vertex m_v0 { 0 };
    Vertex m_v1 { 0 };
    edge_direction m_direction { edge_direction::bidirectional };
    T m_weight;
    mutable bool m_traversed { false };
public:
    Edge () = default;
    Edge (Vertex u0, Vertex u1, T w, edge_direction dir = edge_direction::bidirectional) :
        m_v0(u0), m_v1(u1), m_direction(dir), m_weight(w) {};
    ~Edge () = default;

    Vertex get_v0 () const { return m_v0; }
    Vertex get_v1 () const { return m_v1; }
    edge_direction get_direction () const { return m_direction; }
    T get_weight () const { return m_weight; }

    void traverse () const { m_traversed = true; }
    bool was_traversed () const { return m_traversed; }
    void reset () const { m_traversed = false; }
    
    void flip () {
        std::swap(m_v0, m_v1);
        if (m_direction == edge_direction::forward) { m_direction = edge_direction::reverse; }
        else if (m_direction == edge_direction::reverse) { m_direction = edge_direction::forward; }
    }

    friend bool operator==(const Edge<T>& e1, const Edge<T>& e2) {
        if (e1.m_weight != e2.m_weight) { return false; }
        if (e1.m_v0 == e2.m_v0) {
            if (e1.m_v1 != e2.m_v1) { return false; }
            if (e1.m_direction != e2.m_direction) { return false; }
            return true;
        }
        else if (e1.m_v0 == e2.m_v1) {
            if (e1.m_v1 != e2.m_v0) { return false; }
            if (e1.m_direction == edge_direction::bidirectional) {
                if (e2.m_direction != edge_direction::bidirectional) { return false; }
            }
            else if (e1.m_direction == edge_direction::forward) {
                if (e2.m_direction != edge_direction::reverse) { return false; }
            }
            else {
                if (e2.m_direction != edge_direction::forward) { return false; }
            }
            return true;
        }
        return false;
    }

    friend std::ostream& operator<<(std::ostream& os, const Edge<T>& e) {
        if (e.m_direction == edge_direction::bidirectional) {
            os << e.m_v0 << " --(" << e.m_weight << ")-- " << e.m_v1;
        }
        else if (e.m_direction == edge_direction::forward) {
            os << e.m_v0 << " --(" << e.m_weight << ")-> " << e.m_v1;
        }
        else { // reverse
            os << e.m_v0 << " <-(" << e.m_weight << ")-- " << e.m_v1;
        }
        return os;
    }
};

} /* namespace graph */
} /* namespace zcalc */