#include <include/network.hpp>
#include <include/common.hpp>
#include <include/capacitor.hpp>
#include <include/inductor.hpp>
#include <include/resistor.hpp>

#include <algorithm>

namespace zcalc {

Network::Network (double frequency): m_frequency(frequency) {}

void Network::node_cycle (std::size_t node_index, Cycle cycle) {
    /* if this is the starting node but this node was not yet visited by the algorithm -> this is the starting node */
    /* mark this node as visited */
    /* put it in the path */
    /* go through every unvisited edge of this node, set them to visited, add them to the path and call the cycle to their other node */
    if (!m_nodes[node_index].visited) {
        m_nodes[node_index].visited = true;                                     /* set the node to visited */
        CycleUnit node_unit { .type = cycle_unit_type::node,
                                .node_ptr = &m_nodes[node_index],
                                .name = m_nodes[node_index].name };
        cycle.push_back(std::move(node_unit));                                  /* put the node into the path */
        for (Edge& edge : m_edges) {                                            /* go through every unvisited edge */
            if (edge.visited == false) {
                Cycle own_cycle = cycle;                                        /* clone the path */
                edge.visited = true;                                            /* set the edge to visited */
                CycleUnit edge_unit { .type = cycle_unit_type::edge, 
                                        .edge_ptr = &edge,
                                        .name = edge.designator };
                own_cycle.push_back(std::move(edge_unit));                      /* add the edge to the path */
                if (edge.node_0_index == node_index) {                          /* if one end of the edge is connected to this node */
                    node_cycle(edge.node_1_index, own_cycle);                   /* call the node cycle */
                }
                else if (edge.node_1_index == node_index) {
                    node_cycle(edge.node_0_index, own_cycle);
                }
                edge.visited = false;
            }
        }
        m_nodes[node_index].visited = false;
    }
    /* if the node was already visited */
    else {
        if (m_nodes[node_index].start) {                                        /* if it is the starting node -> cycle */
            //path.push_back(m_nodes[node_index].name);
            m_cycles.push_back(cycle);
        }
    }
}

bool Network::are_cycles_same (Cycle cycle_0, Cycle cycle_1) {
    if (cycle_0.size() != cycle_1.size()) return false;
    std::sort(cycle_0.begin(), cycle_0.end(), [](const CycleUnit& a, const CycleUnit& b) -> bool { return a.name > b.name; });
    std::sort(cycle_1.begin(), cycle_1.end(), [](const CycleUnit& a, const CycleUnit& b) -> bool { return a.name > b.name; });
    for (std::size_t i = 0; i < cycle_0.size(); ++i) {
        if (cycle_0[i].name.compare(cycle_1[i].name) != 0) return false;
    }
    return true;
}

void Network::add_node (const std::string& node_name) {
    for (const Node& node : m_nodes) {
        if (node_name.compare(node.name) == 0) {
            std::cout << "ERROR : node already exists" << std::endl;
            return;
        }
    }
    Node n;
    n.name = node_name;
    n.visited = false;
    n.start = false;
    m_nodes.push_back(n);
}

void Network::add_resistor (const std::string& designator, double resistance, const std::string& node_0_name, const std::string& node_1_name) {
    for (const Edge& edge : m_edges) {
        if (designator.compare(edge.designator) == 0) {
            std::cout << "ERROR : edge already exists" << std::endl;
            return;
        }
    }
    Edge e;
    e.designator = designator;
    e.type = edge_type::impedance;
    e.impedance_ptr = std::make_shared<Resistor>(resistance);
    bool node_0_exists = false;
    bool node_1_exists = false;
    for (std::size_t i = 0; i < m_nodes.size(); ++i) {
        if (node_0_name.compare(m_nodes[i].name) == 0) {
            node_0_exists = true;
            e.node_0_index = i;
        }
        if (node_1_name.compare(m_nodes[i].name) == 0) {
            node_1_exists = true;
            e.node_1_index = i;
        }
    }
    if (!node_0_exists || !node_1_exists) {
        std::cout << "ERROR : edge endnode does not exists" << std::endl;
        return;
    }
    m_edges.push_back(std::move(e));
}

void Network::add_inductor (const std::string& designator, double inductance, const std::string& node_0_name, const std::string& node_1_name) {
    for (const Edge& edge : m_edges) {
        if (designator.compare(edge.designator) == 0) {
            std::cout << "ERROR : edge already exists" << std::endl;
            return;
        }
    }
    Edge e;
    e.designator = designator;
    e.type = edge_type::impedance;
    e.impedance_ptr = std::make_shared<Inductor>(inductance, m_frequency);
    bool node_0_exists = false;
    bool node_1_exists = false;
    for (std::size_t i = 0; i < m_nodes.size(); ++i) {
        if (node_0_name.compare(m_nodes[i].name) == 0) {
            node_0_exists = true;
            e.node_0_index = i;
        }
        if (node_1_name.compare(m_nodes[i].name) == 0) {
            node_1_exists = true;
            e.node_1_index = i;
        }
    }
    if (!node_0_exists || !node_1_exists) {
        std::cout << "ERROR : edge endnode does not exists" << std::endl;
        return;
    }
    m_edges.push_back(std::move(e));
}

void Network::add_capacitor (const std::string& designator, double capacitance, const std::string& node_0_name, const std::string& node_1_name) {
    for (const Edge& edge : m_edges) {
        if (designator.compare(edge.designator) == 0) {
            std::cout << "ERROR : edge already exists" << std::endl;
            return;
        }
    }
    Edge e;
    e.designator = designator;
    e.type = edge_type::impedance;
    e.impedance_ptr = std::make_shared<Capacitor>(capacitance, m_frequency);
    bool node_0_exists = false;
    bool node_1_exists = false;
    for (std::size_t i = 0; i < m_nodes.size(); ++i) {
        if (node_0_name.compare(m_nodes[i].name) == 0) {
            node_0_exists = true;
            e.node_0_index = i;
        }
        if (node_1_name.compare(m_nodes[i].name) == 0) {
            node_1_exists = true;
            e.node_1_index = i;
        }
    }
    if (!node_0_exists || !node_1_exists) {
        std::cout << "ERROR : edge endnode does not exists" << std::endl;
        return;
    }
    m_edges.push_back(std::move(e));
}

void Network::add_source (const std::string& designator, double voltage, const std::string& node_0_name, const std::string& node_1_name) {
    for (const Edge& edge : m_edges) {
        if (designator.compare(edge.designator) == 0) {
            std::cout << "ERROR : edge already exists" << std::endl;
            return;
        }
    }
    Edge e;
    e.designator = designator;
    e.type = edge_type::source;
    e.source_ptr = std::make_shared<Source>(voltage);
    bool node_0_exists = false;
    bool node_1_exists = false;
    for (std::size_t i = 0; i < m_nodes.size(); ++i) {
        if (node_0_name.compare(m_nodes[i].name) == 0) {
            node_0_exists = true;
            e.node_0_index = i;
        }
        if (node_1_name.compare(m_nodes[i].name) == 0) {
            node_1_exists = true;
            e.node_1_index = i;
        }
    }
    if (!node_0_exists || !node_1_exists) {
        std::cout << "ERROR : edge endnode does not exists" << std::endl;
        return;
    }
    m_edges.push_back(std::move(e));
}

void Network::print () {
    std::cout << "frequency : " << m_frequency << std::endl;
    std::cout << "nodes" << std::endl;
    for (const Node& node : m_nodes) {
        std::cout << "    " << node.name << std::endl;
    }
    std::cout << "edges" << std::endl;
    for (const Edge& edge : m_edges) {
        std::cout << "    " << m_nodes[edge.node_0_index].name << " - " << edge.designator << " - " << m_nodes[edge.node_1_index].name << std::endl;
    }
}
void Network::compute_cycles () {
    m_cycles.clear();
    for (std::size_t i = 0; i < m_nodes.size(); ++i) {
        Cycle cycle;
        for (Node& node_tmp : m_nodes) {
            node_tmp.start = false;
            node_tmp.visited = false;
        }
        for (Edge& edge_tmp : m_edges) {
            edge_tmp.visited = false;
        }
        m_nodes[i].start = true;
        node_cycle(i, cycle);
    }
    for (std::size_t i = 0; i < m_cycles.size(); ++i) {
        for (std::size_t e = m_cycles.size() - 1; e > i; --e) {
            if (are_cycles_same(m_cycles[i], m_cycles[e])) {
                m_cycles.erase(m_cycles.begin() + e);
            }
        }
    }
}
void Network::print_cycles () {
    for (const Cycle& cycle : m_cycles) {
        for (const CycleUnit& element : cycle) {
            std::cout << element.name << " ";
        }
        std::cout << std::endl;
    }
}
void Network::compute_equations () {
    std::vector<std::string> row;
    for (Edge& edge : m_edges) {
        row.push_back("i{" + edge.designator + "}");
    }
    for (Edge& edge : m_edges) {
        row.push_back("u{" + edge.designator + "}");
    }
    m_matrix.push_back(row);
    for (std::size_t i = 0; i < m_nodes.size(); ++i) {
        row.clear();
        for (const Edge& edge : m_edges) {
            if (edge.node_0_index == i) { /* outgoing current */
                row.push_back(" -1  ");
            }
            else if (edge.node_1_index == i) { /* incoming current */
                row.push_back("  1  ");
            }
            else {
                row.push_back("  0  ");
            }
        }
        for (const Edge& edge : m_edges) {
            row.push_back("  0  ");
        }
        m_matrix.push_back(row);
    }
    for (std::size_t i = 0; i < m_edges.size(); ++i) {
        for (std::string& val : row) {
            val = "  0  ";
        }
        row[i + row.size() / 2] = "  1  ";
        row[i] = "  " + m_edges[i].designator + " ";
        m_matrix.push_back(row);
    }
    for (const Cycle& cycle : m_cycles) {
        for (std::string& val : row) {
            val = "  0  ";
        }
        /* every cycle starts with a node */
        int from_node_id = 0;
        for (const CycleUnit& unit : cycle) {
            if (unit.type == cycle_unit_type::node) {
                for (size_t i = 0; i < m_nodes.size(); ++i) {
                    if (unit.node_ptr->name.compare(m_nodes[i].name) == 0) {
                        from_node_id = i;
                    }
                }
            }
            else {
                Edge* edge_ptr = unit.edge_ptr;
                for (size_t i = 0; i < m_edges.size(); ++i) {
                    if (edge_ptr->designator.compare(m_edges[i].designator) == 0) {
                        if (edge_ptr->node_0_index == from_node_id) row[i] = "  1  ";
                        else row[i] = " -1  ";
                    }
                }
            }
        }
        m_matrix.push_back(row);
    }
}
void Network::print_equations () {
    for (const std::vector<std::string>& row : m_matrix) {
        for (const std::string& val : row) {
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }
}

} /* namespace zcalc */