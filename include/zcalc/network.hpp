#pragma once

#include <zcalc/component/component.hpp>
#include <zcalc/component/impedance.hpp>
#include <zcalc/component/resistor.hpp>
#include <zcalc/component/capacitor.hpp>
#include <zcalc/component/inductor.hpp>
#include <zcalc/component/source.hpp>

#include <zcalc/math/complex.hpp>
#include <zcalc/math/linear_equation_system.hpp>

#include <zcalc/graph/graph.hpp>

#include <vector>
#include <map>
#include <string>
#include <memory>
#include <iostream>
#include <iomanip>
#include <stdexcept>

namespace zcalc {

class Network {
private:
    component::Node m_node_index { 0 };
    std::map<std::string, component::Node> m_nodes;
    std::map<std::string, std::shared_ptr<component::Component>> m_components;

    std::unique_ptr<math::LinearEquationSystem> m_lin_equ_system;

    double m_frequency { 1.0 };
    std::size_t m_num_variables;

    component::Node get_node (const std::string& designator) const {
        auto node = m_nodes.find(designator);
        if (node == m_nodes.end()) { throw std::invalid_argument("node " + designator + " does not exists"); }
        return node->second;
    }

    // void compute_equations () {
    //     if (m_nodes.size() == 0) return;
    //     if (m_components.size() == 0) return;

    //     std::size_t row_index = 0;
    //     /* Kirchhoff's current law */
    //     for (const auto& node : m_nodes) {
    //         LinearEquation<Complex> equ { m_num_variables };
    //         for (const auto& component : m_components) {
    //             equ.set_result(Complex{0.0, 0.0});
    //             component->kcl(node.get(), equ);
    //         }
    //         m_lin_equ_system->append_equation(equ);
    //     }
 
    //     /* equation for every impedance */
    //     for (const auto& component : m_components) {
    //         LinearEquation<Complex> equ { m_num_variables };
    //         component->own_equ(equ);
    //         m_lin_equ_system->append_equation(equ);
    //     }

    //     /* Kirchhoff's voltage law */
    //     LoopFinder::find_loops(m_nodes[0].get(), m_num_variables);
    //     for (LoopMessage& message : LoopFinder::get_loops()) {
    //         message.equ.set_result(Complex{0.0, 0.0});
    //         m_lin_equ_system->append_equation(message.equ);
    //     }
    // }

    /* add a source to the network */
    void add_source (const std::string& designator, double voltage, const std::string& node_0_des, const std::string& node_1_des) {
        if (m_components.contains(designator)) { throw std::invalid_argument("component " + designator + " already exists"); }
        m_components[designator] = std::make_unique<component::Source>(voltage, m_frequency, get_node(node_0_des), get_node(node_1_des), m_components.size());
    }

public:
    Network () {
        add_node ("in");
        add_node ("out");
        add_node ("gnd");
        /* important that RL_pseudo must have index 0 */
        /* the pseudo load resistor serves as a measurement resistor that insignificantly influences the measurement accuracy (like a multimeter) */
        add_resistor("RL_pseudo", 10e9, "out", "gnd");
        add_source ("U", 1.0, "in", "gnd");
    }
    ~Network () = default;
    
    /* add a node to the graph */
    void add_node (const std::string& designator) {
        if (m_nodes.contains(designator)) { throw std::invalid_argument("node " + designator + " already exists"); }
        m_nodes[designator] = m_node_index++;
    }

    /* add a resistor to the network */
    void add_resistor (const std::string& designator, double resistance, const std::string& node_0_des, const std::string& node_1_des) {
        if (m_components.contains(designator)) { throw std::invalid_argument("component " + designator + " already exists"); }
        m_components[designator] = std::make_unique<component::Resistor>(resistance, get_node(node_0_des), get_node(node_1_des), m_components.size());
    }

    /* add an inductor to the network */
    void add_inductor (const std::string& designator, double inductance, const std::string& node_0_des, const std::string& node_1_des) {
        if (m_components.contains(designator)) { throw std::invalid_argument("component " + designator + " already exists"); }
        m_components[designator] = std::make_unique<component::Inductor>(inductance, m_frequency, get_node(node_0_des), get_node(node_1_des), m_components.size());
    }

    /* add a capacitor to the network */
    void add_capacitor (const std::string& designator, double capacitance, const std::string& node_0_des, const std::string& node_1_des) {
        if (m_components.contains(designator)) { throw std::invalid_argument("component " + designator + " already exists"); }
        m_components[designator] = std::make_unique<component::Capacitor>(capacitance, m_frequency, get_node(node_0_des), get_node(node_1_des), m_components.size());
    }

    // Vertex v0, Vertex v1, edge_direction direction = edge_direction::bidirectional, float weight = 1.0f
    graph::Graph to_graph () const {
        // nodes are the vertices, compnents are the edges
        graph::Graph g { m_nodes.size() };
        for (auto const& [des, val] : m_components) {
            g.add_edge(val->get_gate(0), val->get_gate(1));
        }
        return g;
    }

    // std::vector<math::Complex> compute () {
    //     m_num_variables = 0;
    //     for (auto const& [des, val] : m_components) {
    //         m_num_variables += val->get_num_variables();
    //     }
    //     m_lin_equ_system = std::make_unique<math::LinearEquationSystem>(m_num_variables);
    //     compute_equations();
    //     std::vector<math::Complex> solution;
    //     bool success = m_lin_equ_system->solve(solution);
    //     if (!success) {
    //         throw std::runtime_error("could not solve equation system");
    //     }
    //     //for (const auto& c : solution) {
    //     //    std::cout << c << " ";
    //     //}
    //     //std::cout << std::endl;
    //     return solution;
    // }

    // math::Complex compute_response () {
    //     return compute()[0 + equ_voltage_offset];
    // }

    void print () {
        std::cout << "frequency : " << m_frequency << std::endl;
        std::cout << "nodes" << std::endl;
        for (auto const& [des, val] : m_nodes) {
            std::cout << "    " << des << " : " << val << std::endl;
        }
        std::cout << "components" << std::endl;
        for (auto const& [des, val] : m_components) {
            std::cout << "    " << des << " : " << val << std::endl;
        }
    }

    void print_equations () {
        std::cout << std::fixed << std::setprecision(2);
        std::cout << (*m_lin_equ_system) << std::endl;
    }

    void set_frequency (double frequency) {
        m_frequency = frequency;
        for (const auto& component : m_components) {
            component.second->set_frequency(frequency);
        }
    }
};

} /* namespace zcalc */