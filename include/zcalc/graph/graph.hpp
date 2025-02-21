#pragma once

#include <cstdint>
#include <vector>
#include <set>
#include <algorithm>

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

class Graph {
private:
    Vertex m_v { 0 };
    std::vector<Edge> m_e;

    void dfs (Vertex node, Vertex start, std::vector<bool>& visited, std::vector<Vertex>& path, std::set<std::vector<Vertex>>& cycles) {
        visited[node] = true;
        path.push_back(node);

        for (const Edge& edge : m_e) {
            if (edge.traversed) { continue; }
            edge.traversed = true;
            if ((edge.v0 == node) && ((edge.direction == edge_direction::forward) || (edge.direction == edge_direction::bidirectional))) {
                if (edge.v1 == start) { // Cycle detected
                    //path.push_back(start);
                    cycles.insert(std::vector<Vertex>(path.begin(), path.end()));
                    //path.pop_back();
                }
                else if (!visited[edge.v1]) {
                    dfs(edge.v1, start, visited, path, cycles);
                }
            }
            else if ((edge.v1 == node) && ((edge.direction == edge_direction::reverse) || (edge.direction == edge_direction::bidirectional))) {
                if (edge.v0 == start) { // Cycle detected
                    //path.push_back(start);
                    cycles.insert(std::vector<Vertex>(path.begin(), path.end()));
                    //path.pop_back();
                }
                else if (!visited[edge.v0]) {
                    dfs(edge.v0, start, visited, path, cycles);
                }
            }
            edge.traversed = false;
        }
        
        path.pop_back();
        visited[node] = false;
    }

public:
    Graph () = default;
    Graph (Vertex v) : m_v(v) {};
    ~Graph () = default;

    void add_edge (Vertex v0, Vertex v1, edge_direction direction = edge_direction::bidirectional, float weight = 1.0f) {
        m_e.push_back(Edge{v0, v1, direction, weight});
    }

    std::set<std::vector<Vertex>> find_cycles () {
        std::vector<bool> visited ( m_v, false );
        std::vector<Vertex> path;
        std::set<std::vector<Vertex>> cycles;
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