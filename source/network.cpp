#include <include/network.hpp>
#include <include/common.hpp>
#include <include/capacitor.hpp>
#include <include/inductor.hpp>
#include <include/resistor.hpp>

#include <algorithm>
#include <iostream>
#include <iomanip>

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
        for (GraphEdge& edge : m_edges) {                                       /* go through every unvisited edge */
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
    for (const GraphEdge& edge : m_edges) {
        if (designator.compare(edge.designator) == 0) {
            std::cout << "ERROR : edge already exists" << std::endl;
            return;
        }
    }
    GraphEdge e;
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
    for (const GraphEdge& edge : m_edges) {
        if (designator.compare(edge.designator) == 0) {
            std::cout << "ERROR : edge already exists" << std::endl;
            return;
        }
    }
    GraphEdge e;
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
    for (const GraphEdge& edge : m_edges) {
        if (designator.compare(edge.designator) == 0) {
            std::cout << "ERROR : edge already exists" << std::endl;
            return;
        }
    }
    GraphEdge e;
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
    for (const GraphEdge& edge : m_edges) {
        if (designator.compare(edge.designator) == 0) {
            std::cout << "ERROR : edge already exists" << std::endl;
            return;
        }
        if (edge.type == edge_type::source) {
            std::cout << "ERROR : only one source can be added" << std::endl;
            return;
        }
    }
    GraphEdge e;
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

void Network::compute () {
    bool source_found = false;
    for (const GraphEdge& edge : m_edges) {
        if (edge.type == edge_type::source) {
            source_found = true;
            break;
        }
    }
    if (!source_found) {
        std::cout << "ERROR : source not found" << std::endl;
        return;
    }
    /* assign the matrix indexes and allocate the matrix */
    /* source voltage has the last index */
    std::size_t index = 0;
    for (GraphEdge& edge : m_edges) {
        if (edge.type == edge_type::impedance) {
            edge.current_index = index;
            edge.voltage_index = index + m_edges.size();
            ++index;
        }
        else {
            edge.current_index = m_edges.size() - 1;
            edge.voltage_index = m_edges.size() * 2 - 1;

        }
    }
    compute_cycles();
    
    /* one equation for every node, two variables for every component */
    //std::size_t num_equations = 0;
    //num_equations += m_nodes.size();
    //num_equations += m_cycles.size();
    //num_equations += m_edges.size() - 1;
    m_lin_equ_system = std::make_unique<LinearEquationSystem>(m_edges.size() * 2);
    compute_equations();
}

void Network::print () {
    std::cout << "frequency : " << m_frequency << std::endl;
    std::cout << "nodes" << std::endl;
    for (const Node& node : m_nodes) {
        std::cout << "    " << node.name << std::endl;
    }
    std::cout << "edges" << std::endl;
    for (const GraphEdge& edge : m_edges) {
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
        for (GraphEdge& edge_tmp : m_edges) {
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
    std::size_t row_index = 0;
    /* Kirchhoff's current law */
    for (std::size_t i = 0; i < m_nodes.size(); ++i) {
        LinearEquation<Complex> equ {m_edges.size() * 2};
        for (const GraphEdge& edge : m_edges) {
            if (edge.node_0_index == i) {
                /* outgoing current */
                equ[edge.current_index] = Complex{-1.0, 0.0};
            }
            else if (edge.node_1_index == i) {
                /* incoming current */
                equ[edge.current_index] = Complex{1.0, 0.0};
            }
            else {
                /* is not connected to the node */
                equ[edge.current_index] = Complex{0.0, 0.0};
            }
            /* voltage coefficients are 0 when writing the equations for the current law */
            equ[edge.voltage_index] = Complex{0.0, 0.0};
        }
        m_lin_equ_system->append_equation(equ);
    }

    /* equation for every impedance */
    for (const GraphEdge& edge : m_edges) {
        LinearEquation<Complex> equ {m_edges.size() * 2};
        if (edge.type == edge_type::impedance) {
            equ[edge.current_index] = edge.impedance_ptr->get_impedance() * Complex{-1.0, 0.0};
            equ[edge.voltage_index] = Complex{1.0, 0.0};
        }
        else {
            continue;
        }
        m_lin_equ_system->append_equation(equ);
    }

    /* Kirchhoff's voltage law */
    for (const Cycle& cycle : m_cycles) {
        LinearEquation<Complex> equ {m_edges.size() * 2};
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
                GraphEdge* edge_ptr = unit.edge_ptr;
                if (edge_ptr->type == edge_type::impedance) {
                    if (edge_ptr->node_0_index == from_node_id) equ[edge_ptr->voltage_index] = Complex{1.0, 0.0};
                    else equ[edge_ptr->voltage_index] = Complex{-1.0, 0.0};
                }
                else {
                    if (edge_ptr->node_0_index == from_node_id) equ.set_result(edge_ptr->source_ptr->get_voltage());
                    else equ.set_result(-edge_ptr->source_ptr->get_voltage());
                }
            }
        }
        m_lin_equ_system->append_equation(equ);
    }
}
void Network::print_equations () {
    std::cout << std::fixed << std::setprecision(2);
    std::cout << (*m_lin_equ_system) << std::endl;
}

} /* namespace zcalc */