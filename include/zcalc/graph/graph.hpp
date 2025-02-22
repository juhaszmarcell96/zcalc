#pragma once

#include "zcalc/graph/vertex.hpp"
#include "zcalc/graph/edge.hpp"

#include <cstdint>
#include <vector>
#include <algorithm>
#include <stdexcept>

namespace zcalc {
namespace graph {

template<typename T>
class Graph {
private:
    Vertex m_v { 0 };
    std::vector<Edge<T>> m_e;

    void dfs (Vertex node, Vertex start, std::vector<bool>& visited, Path<T>& path, std::vector<Path<T>>& cycles) const {
        visited[node] = true;
        path.push_back_v(node);

        for (const auto& edge : m_e) {
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

    void add_edge (Vertex v0, Vertex v1, T weight, edge_direction direction = edge_direction::bidirectional) {
        m_e.push_back(Edge<T>{v0, v1, weight, direction});
    }

    const std::vector<Edge<T>> get_edges () const { return m_e; }
    Vertex get_vertices () const { return m_v; }

    std::vector<Path<T>> find_cycles () const {
        std::vector<bool> visited ( m_v, false );
        Path<T> path;
        std::vector<Path<T>> cycles;
        for (Vertex i = 0; i < m_v; ++i) {
            std::fill(visited.begin(), visited.end(), false);
            path.clear();
            dfs(i, i, visited, path, cycles);
        }
        return cycles;
    }

    friend std::ostream& operator<<(std::ostream& os, const Graph& g) {
        os << "number of vertices : " << g.m_v << std::endl;
        for (const auto& e : g.m_e) {
            if (e.direction == edge_direction::bidirectional) {
                os << e.v0 << " --(" << e.weight << ")-- " << e.v1 << std::endl;
            }
            else if (e.direction == edge_direction::forward) {
                os << e.v0 << " --(" << e.weight << ")-> " << e.v1 << std::endl;
            }
            else { // reverse
                os << e.v0 << " <-(" << e.weight << ")-- " << e.v1 << std::endl;
            }
        }
        return os;
    }
};

} /* namespace graph */
} /* namespace zcalc */