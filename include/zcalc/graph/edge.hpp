#pragma once

#include "zcalc/graph/vertex.hpp"

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

} /* namespace graph */
} /* namespace zcalc */