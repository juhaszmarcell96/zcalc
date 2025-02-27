#pragma once

#include "zcalc/graph/edge.hpp"

#include <cstdint>
#include <vector>
#include <algorithm>
#include <stdexcept>

namespace zcalc {
namespace graph {

template<typename T>
class Path {
private:
    Vertex m_start;
    std::vector<Edge<T>> m_e;
public:
    Path () = delete;
    Path (Vertex start) : m_start(start) {}
    ~Path () = default;

    void clear () {
        m_e.clear();
    }

    bool fits (const Edge<T>& e) {
        Vertex start;
        if (m_e.empty()) { start = m_start; }
        else { start = m_e.back().get_v1(); }

        if (e.get_v0() == start) { return true; }
        else if (e.get_v1() == start) { return true; }
        return false;
    }

    void push_back (const Edge<T>& e) {
        Vertex start;
        if (m_e.empty()) { start = m_start; }
        else { start = m_e.back().get_v1(); }

        if (e.get_v0() == start) {
            m_e.push_back(e);
        }
        else if (e.get_v1() == start) {
            Edge<T> new_e = e;
            new_e.flip();
            m_e.push_back(std::move(new_e));
        }
        else {
            throw std::invalid_argument("edge does not start where it should");
        }
    }

    void pop_back () {
        if (!m_e.empty()) {
            m_e.pop_back();
        }
    }

    const std::vector<Edge<T>>& get_edges () const { return m_e; }

    bool contains (Vertex v0, Vertex v1, T weight, edge_direction direction) const {
        Edge<T> e0 { v0, v1, weight, direction };
        for (const auto& e1 : m_e) {
            if (e0 == e1) { return true; }
        }
        return false;
    }

    bool contains (const Edge<T>& e0) const {
        for (const auto& e1 : m_e) {
            if (e0 == e1) { return true; }
        }
        return false;
    }

    friend bool operator==(const Path<T>& p1, const Path<T>& p2) {
        if (p1.m_e.size() != p2.m_e.size()) { return false; }
        for (const auto& e1 : p1.m_e) {
            if (!p2.contains(e1)) { return false; }
        }
        return true;
    }

    friend std::ostream& operator<<(std::ostream& os, const Path<T>& p) {
        for (const auto& e : p.m_e) {
            os << e << " ";
        }
        return os;
    }
};

} /* namespace graph */
} /* namespace zcalc */