#pragma once

#include "zcalc/graph/vertex.hpp"

#include <cstdint>
#include <vector>
#include <algorithm>
#include <stdexcept>

namespace zcalc {
namespace graph {

enum class edge_direction {
    bidirectional, // 0 <-> 1
    forward,       // 0 -> 1
    reverse        // 0 <- 1
};

template<typename T>
struct Edge {
    Vertex v0 { 0 };
    Vertex v1 { 0 };
    edge_direction direction { edge_direction::bidirectional };
    T weight;
    mutable bool traversed { false };

    Edge () = default;
    Edge (Vertex u0, Vertex u1, T w, edge_direction dir = edge_direction::bidirectional) :
        v0(u0), v1(u1), direction(dir), weight(w) {};
};

// TODO : redundant storage, vertices are contained in the edge structures
template<typename T>
class Path {
private:
    std::vector<Vertex> m_v;
    std::vector<const Edge<T>*> m_e;
public:
    Path () = default;
    ~Path () = default;

    void clear () {
        m_v.clear();
        m_e.clear();
    }

    void push_back_v (Vertex v) {
        if (m_v.size() != m_e.size()) { throw std::invalid_argument("unexpected vertex"); }
        m_v.push_back(v);
    }

    void push_back_e (const Edge<T>* e) {
        if (m_v.size() <= m_e.size()) { throw std::invalid_argument("unexpected edge"); }
        if (!e) { throw std::invalid_argument("edge cannot be null"); }
        m_e.push_back(e);
    }

    void pop_back_v () {
        if (!m_v.empty()) {
            m_v.pop_back();
        }
    }

    void pop_back_e () {
        if (!m_e.empty()) {
            m_e.pop_back();
        }
    }

    const std::vector<const Edge<T>*>& get_edges () const { return m_e; }

    friend bool operator==(const Path<T>& p1, const Path<T>& p2) {
        if (p1.m_v.size() != p2.m_v.size()) { return false; }
        if (p1.m_e.size() != p2.m_e.size()) { return false; }
        for (const auto v : p1.m_v) {
            if (std::find(p2.m_v.begin(), p2.m_v.end(), v) == p2.m_v.end()) {
                return false;
            }
        }
        for (const auto e : p1.m_e) {
            if (std::find(p2.m_e.begin(), p2.m_e.end(), e) == p2.m_e.end()) {
                return false;
            }
        }
        return true;
    }

    friend std::ostream& operator<<(std::ostream& os, const Path<T>& p) {
        for (std::size_t i = 0; i < p.m_e.size(); ++i) {
            Vertex v = p.m_v[i];
            const auto& e = *(p.m_e[i]);
            os << v;
            if (e.v0 == v) {
                if (e.direction == edge_direction::bidirectional) {
                    os << " --(" << e.weight << ")-- ";
                }
                else if (e.direction == edge_direction::forward) {
                    os << " --(" << e.weight << ")-> ";
                }
                else { // reverse
                    os << " <-(" << e.weight << ")-- ";
                }
            }
            else {
                if (e.direction == edge_direction::bidirectional) {
                    os << " --(" << e.weight << ")-- ";
                }
                else if (e.direction == edge_direction::forward) {
                    os << " <-(" << e.weight << ")-- ";
                }
                else { // reverse
                    os << " --(" << e.weight << ")-> ";
                }
            }
        }
        os << p.m_v.back();
        return os;
    }
};

} /* namespace graph */
} /* namespace zcalc */