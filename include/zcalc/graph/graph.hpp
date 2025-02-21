#pragma once

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

typedef std::uint32_t Vertex;

struct Edge {
    Vertex v0 { 0 };
    Vertex v1 { 0 };
    edge_direction direction { edge_direction::bidirectional };
    float weight { 1.0f };
    mutable bool traversed { false };

    Edge () = default;
    Edge (Vertex u0, Vertex u1, edge_direction dir = edge_direction::bidirectional, float w = 1.0f) :
        v0(u0), v1(u1), direction(dir), weight(w) {};
};

// TODO : redundant storage, vertices are contained in the edge structures
class Path {
private:
    std::vector<Vertex> m_v;
    std::vector<const Edge*> m_e;
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

    void push_back_e (const Edge* e) {
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

    friend bool operator==(const Path& p1, const Path& p2) {
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

    friend std::ostream& operator<<(std::ostream& os, const Path& p) {
        for (std::size_t i = 0; i < p.m_e.size(); ++i) {
            Vertex v = p.m_v[i];
            const Edge& e = *(p.m_e[i]);
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

class Graph {
private:
    Vertex m_v { 0 };
    std::vector<Edge> m_e;

    void dfs (Vertex node, Vertex start, std::vector<bool>& visited, Path& path, std::vector<Path>& cycles) {
        visited[node] = true;
        path.push_back_v(node);

        for (const Edge& edge : m_e) {
            if (edge.traversed) { continue; }
            edge.traversed = true;
            path.push_back_e(&edge);
            if ((edge.v0 == node) && ((edge.direction == edge_direction::forward) || (edge.direction == edge_direction::bidirectional))) {
                if (edge.v1 == start) { // Cycle detected
                    path.push_back_v(start);
                    bool found = false;
                    for (const auto& p : cycles) {
                        if (p == path) {
                            found = true;
                            break;
                        }
                    }
                    if (!found) {
                        cycles.push_back(path);
                    }
                    path.pop_back_v();
                }
                else if (!visited[edge.v1]) {
                    dfs(edge.v1, start, visited, path, cycles);
                }
            }
            else if ((edge.v1 == node) && ((edge.direction == edge_direction::reverse) || (edge.direction == edge_direction::bidirectional))) {
                if (edge.v0 == start) { // Cycle detected
                    path.push_back_v(start);
                    bool found = false;
                    for (const auto& p : cycles) {
                        if (p == path) {
                            found = true;
                            break;
                        }
                    }
                    if (!found) {
                        cycles.push_back(path);
                    }
                    path.pop_back_v();
                }
                else if (!visited[edge.v0]) {
                    dfs(edge.v0, start, visited, path, cycles);
                }
            }
            path.pop_back_e();
            edge.traversed = false;
        }
        
        path.pop_back_v();
        visited[node] = false;
    }

public:
    Graph () = default;
    Graph (Vertex v) : m_v(v) {};
    ~Graph () = default;

    void add_edge (Vertex v0, Vertex v1, edge_direction direction = edge_direction::bidirectional, float weight = 1.0f) {
        m_e.push_back(Edge{v0, v1, direction, weight});
    }

    std::vector<Path> find_cycles () {
        std::vector<bool> visited ( m_v, false );
        Path path;
        std::vector<Path> cycles;
        for (Vertex i = 0; i < m_v; ++i) {
            std::fill(visited.begin(), visited.end(), false);
            path.clear();
            dfs(i, i, visited, path, cycles);
        }
        return cycles;
    }
};

} /* namespace graph */
} /* namespace zcalc */