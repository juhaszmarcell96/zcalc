#pragma once

#include <include/impedance.hpp>

#include <vector>
#include <string>
#include <memory>

namespace zcalc {


struct Node {
    std::string name;
    bool visited = false;
    bool start = false;
};

struct Edge {
    std::string designator;
    std::size_t node_0_index;
    std::size_t node_1_index;
    bool visited = false;
};

enum class cycle_unit_type {
    node,
    edge
};

struct CycleUnit {
    cycle_unit_type type;
    union {
        Node* node_ptr;
        Edge* edge_ptr;
    };
    std::string name;
};

typedef std::vector<CycleUnit> Cycle;

class Network {
private:
    std::vector<Node> m_nodes;
    std::vector<Edge> m_edges;

    std::vector<Cycle> m_cycles;
    std::vector<std::vector<std::string>> m_matrix;

    void node_cycle (std::size_t node_index, Cycle cycle);
    bool are_cycles_same (Cycle cycle_0, Cycle cycle_1);
public:
    void add_node (const std::string& node_name);
    void add_edge (const std::string& designator, const std::string& node_0_name, const std::string& node_1_name);
    void print ();
    void compute_cycles ();
    void print_cycles ();
    void compute_equations ();
    void print_equations ();
};

} /* namespace zcalc */