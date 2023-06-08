#pragma once

#include <zcalc/impedance.hpp>
#include <zcalc/resistor.hpp>
#include <zcalc/capacitor.hpp>
#include <zcalc/inductor.hpp>
#include <zcalc/source.hpp>
#include <zcalc/complex.hpp>
#include <zcalc/linear_equation_system.hpp>
#include <zcalc/node.hpp>
#include <zcalc/component.hpp>
#include <zcalc/cycle.hpp>

#include <vector>
#include <string>
#include <memory>
#include <iostream>
#include <iomanip>

namespace zcalc {

//struct GraphEdge {
//    std::string designator;
//    std::size_t node_0_index;
//    std::size_t node_1_index;
//    bool visited = false;
//    edge_type type;
//    std::shared_ptr<Impedance> impedance_ptr = nullptr;
//    std::shared_ptr<Source> source_ptr = nullptr;
//    std::size_t voltage_index = 0; /* index of its voltage variable in the matrix's row */
//    std::size_t current_index = 0; /* index of its current variable in the matrix's row */
//};

class Network {
private:
    std::vector<node_ptr_t> m_nodes;
    std::vector<component_ptr_t> m_edges;

    std::vector<Cycle> m_cycles;
    std::unique_ptr<LinearEquationSystem> m_lin_equ_system;

    void compute_cycles () {
        m_cycles.clear();
        for (auto& node : m_nodes) {
            Cycle cycle;
            for (auto& node_tmp : m_nodes) {
                node_tmp->start = false;
                node_tmp->visited = false;
            }
            for (auto& edge_tmp : m_edges) {
                edge_tmp->visited = false;
            }
            node->start = true;
            node_cycle(node, cycle);
        }
        for (std::size_t i = 0; i < m_cycles.size(); ++i) {
            for (std::size_t e = m_cycles.size() - 1; e > i; --e) {
                if (m_cycles[i] == m_cycles[e]) {
                    m_cycles.erase(m_cycles.begin() + e);
                }
            }
        }
    }
    void compute_equations () {
        std::size_t row_index = 0;
        /* Kirchhoff's current law */
        for (const auto& node : m_nodes) {
            LinearEquation<Complex> equ {m_edges.size() * 2};
            for (std::size_t i = 0; i < m_edges.size(); ++i) {
                equ[2 * i + 0] = m_edges[i]->get_i_coeff(node.get());
                equ[2 * i + 1] = Complex{0.0, 0.0};
                equ.set_result(Complex{0.0, 0.0});
            }
            m_lin_equ_system->append_equation(equ);
        }

        /* equation for every impedance */
        for (std::size_t i = 0; i < m_edges.size(); ++i) {
            LinearEquation<Complex> equ {m_edges.size() * 2};
            equ[2 * i + 0] = m_edges[i]->get_own_i_coeff();
            equ[2 * i + 1] = m_edges[i]->get_own_u_coeff();
            equ.set_result(m_edges[i]->get_own_result());
            m_lin_equ_system->append_equation(equ);
        }

        /* Kirchhoff's voltage law */
        for (const Cycle& cycle : m_cycles) {
            LinearEquation<Complex> equ {m_edges.size() * 2};
            for (const auto& neighbor : cycle.get_neighboring_nodes()) {
                for (std::size_t i = 0; i < m_edges.size(); ++i) {
                    equ[2 * i + 0] = Complex{0.0, 0.0};
                    equ[2 * i + 1] = m_edges[i]->get_u_coeff(neighbor.node_ptr_0, neighbor.node_ptr_1);
                    equ.set_result(Complex{0.0, 0.0});
                }
            }
            m_lin_equ_system->append_equation(equ);
        }
    }
    void node_cycle (node_ptr_t node, Cycle cycle) {
        /* if this is the starting node but this node was not yet visited by the algorithm -> this is the starting node */
        /* mark this node as visited */
        /* put it in the path */
        /* go through every unvisited edge of this node, set them to visited, add them to the path and call the cycle to their other node */
        if (!node->visited) {
            node->visited = true;                                               /* set the node to visited */
            cycle.add_node(node.get());                                         /* put the node into the path */
            for (auto& edge : node->components) {                               /* go through every unvisited edge */
                if (edge->visited) continue;
                Cycle own_cycle = cycle;                                        /* clone the path */
                edge->visited = true;                                           /* set the edge to visited */
                own_cycle.add_component(edge.get());                            /* add the edge to the path */
                if (edge->get_node_0() == node) {                               /* if one end of the edge is connected to this node */
                    node_cycle(edge->get_node_1(), own_cycle);                  /* call the node cycle */
                }
                else if (edge->get_node_1() == node) {
                    node_cycle(edge->get_node_0(), own_cycle);
                }
                edge->visited = false;
            }
            node->visited = false;
        }
        /* if the node was already visited */
        else {
            if (node->start) {                                        /* if it is the starting node -> cycle */
                //path.push_back(m_nodes[node_index].name);
                m_cycles.push_back(cycle);
            }
        }
    }

    bool edge_exists (const std::string& designator) const {
        for (const auto& edge : m_edges) {
            if (designator.compare(edge->get_designator()) == 0) {
                std::cout << "ERROR : edge already exists" << std::endl;
                return false;
            }
        }
        return true;
    }

    double m_frequency;
public:
    Network (double frequency) : m_frequency(frequency) {}
    Network () = delete;
    ~Network () = default;
    void add_node (const std::string& node_name) {
        for (const auto& node : m_nodes) {
            if (node_name.compare(node->name) == 0) {
                std::cout << "ERROR : node already exists" << std::endl;
                return;
            }
        }
        std::shared_ptr<Node> new_node = std::make_shared<Node>();
        new_node->name = node_name;
        new_node->start = false;
        new_node->visited = false;
        m_nodes.push_back(new_node);
    }
    void add_resistor (const std::string& designator, double resistance, const std::string& node_0_name, const std::string& node_1_name) {
        if (!edge_exists(designator)) return;
        std::shared_ptr<Resistor> new_component = std::make_shared<Resistor>(designator, resistance);
        bool node_0_exists = false;
        bool node_1_exists = false;
        for (auto& node : m_nodes) {
            if (node_0_name.compare(node->name) == 0) {
                node_0_exists = true;
                new_component->set_node_0(node);
                node->components.push_back(new_component);
            }
            if (node_1_name.compare(node->name) == 0) {
                node_1_exists = true;
                new_component->set_node_1(node);
                node->components.push_back(new_component);
            }
        }
        if (!node_0_exists || !node_1_exists) {
            std::cout << "ERROR : edge endnode does not exists" << std::endl;
            return;
        }
        m_edges.push_back(new_component);
    }
    void add_inductor (const std::string& designator, double inductance, const std::string& node_0_name, const std::string& node_1_name) {
        if (!edge_exists(designator)) return;
        std::shared_ptr<Inductor> new_component = std::make_shared<Inductor>(designator, inductance, m_frequency);
        bool node_0_exists = false;
        bool node_1_exists = false;
        for (auto& node : m_nodes) {
            if (node_0_name.compare(node->name) == 0) {
                node_0_exists = true;
                new_component->set_node_0(node);
                node->components.push_back(new_component);
            }
            if (node_1_name.compare(node->name) == 0) {
                node_1_exists = true;
                new_component->set_node_1(node);
                node->components.push_back(new_component);
            }
        }
        if (!node_0_exists || !node_1_exists) {
            std::cout << "ERROR : edge endnode does not exists" << std::endl;
            return;
        }
        m_edges.push_back(new_component);
    }
    void add_capacitor (const std::string& designator, double capacitance, const std::string& node_0_name, const std::string& node_1_name) {
        if (!edge_exists(designator)) return;
        std::shared_ptr<Capacitor> new_component = std::make_shared<Capacitor>(designator, capacitance, m_frequency);
        bool node_0_exists = false;
        bool node_1_exists = false;
        for (auto& node : m_nodes) {
            if (node_0_name.compare(node->name) == 0) {
                node_0_exists = true;
                new_component->set_node_0(node);
                node->components.push_back(new_component);
            }
            if (node_1_name.compare(node->name) == 0) {
                node_1_exists = true;
                new_component->set_node_1(node);
                node->components.push_back(new_component);
            }
        }
        if (!node_0_exists || !node_1_exists) {
            std::cout << "ERROR : edge endnode does not exists" << std::endl;
            return;
        }
        m_edges.push_back(new_component);
    }
    void add_source (const std::string& designator, double voltage, const std::string& node_0_name, const std::string& node_1_name) {
        /* TODO : only one source can be added? */
        if (!edge_exists(designator)) return;
        std::shared_ptr<Source> new_component = std::make_shared<Source>(designator, voltage);
        bool node_0_exists = false;
        bool node_1_exists = false;
        for (auto& node : m_nodes) {
            if (node_0_name.compare(node->name) == 0) {
                node_0_exists = true;
                new_component->set_node_0(node);
                node->components.push_back(new_component);
            }
            if (node_1_name.compare(node->name) == 0) {
                node_1_exists = true;
                new_component->set_node_1(node);
                node->components.push_back(new_component);
            }
        }
        if (!node_0_exists || !node_1_exists) {
            std::cout << "ERROR : edge endnode does not exists" << std::endl;
            return;
        }
        m_edges.push_back(new_component);
    }
    void compute () {
        /* one equation for every node, two variables for every component */
        m_lin_equ_system = std::make_unique<LinearEquationSystem>(m_edges.size() * 2);
        compute_cycles();
        compute_equations();
    }
    void print () {
        std::cout << "frequency : " << m_frequency << std::endl;
        std::cout << "nodes" << std::endl;
        for (const auto& node : m_nodes) {
            std::cout << "    " << node->name << std::endl;
        }
        std::cout << "edges" << std::endl;
        for (const auto& edge : m_edges) {
            std::cout << "    " << edge->get_node_0()->name << " - " << edge->get_designator() << " - " << edge->get_node_1()->name << std::endl;
        }
    }
    void print_cycles () {
        for (const Cycle& cycle : m_cycles) {
            cycle.print();
            std::cout << std::endl;
        }
    }
    void print_equations () {
        std::cout << std::fixed << std::setprecision(2);
        std::cout << (*m_lin_equ_system) << std::endl;
    }
};

} /* namespace zcalc */