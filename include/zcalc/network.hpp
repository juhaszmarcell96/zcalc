#pragma once

#include <zcalc/internal/component.hpp>
#include <zcalc/internal/complex.hpp>
#include <zcalc/internal/linear_equation_system.hpp>

#include <zcalc/impedance.hpp>
#include <zcalc/resistor.hpp>
#include <zcalc/capacitor.hpp>
#include <zcalc/inductor.hpp>
#include <zcalc/source.hpp>

#include <vector>
#include <string>
#include <memory>
#include <iostream>
#include <iomanip>
#include <stdexcept>

namespace zcalc {

class Network {
private:
    std::vector<std::unique_ptr<Node>> m_nodes;
    std::vector<std::unique_ptr<Component>> m_components;

    std::unique_ptr<LinearEquationSystem> m_lin_equ_system;

    double m_frequency;
    std::size_t m_num_variables;


    bool component_exists (const std::string& designator) const {
        for (const auto& component : m_components) {
            if (designator.compare(component->get_designator()) == 0) return true;
        }
        return false;
    }

    Node* get_node (const std::string& designator) const {
        for (const auto& node : m_nodes) {
            if (designator.compare(node->designator) == 0) return node.get();
        }
        throw std::invalid_argument("node " + designator + " doesn't exist");
    }

    void compute_equations () {
        if (m_nodes.size() == 0) return;
        if (m_components.size() == 0) return;

        std::size_t row_index = 0;
        /* Kirchhoff's current law */
        for (const auto& node : m_nodes) {
            LinearEquation<Complex> equ { m_num_variables };
            for (const auto& component : m_components) {
                equ.set_result(Complex{0.0, 0.0});
                component->kcl(node.get(), equ);
            }
            m_lin_equ_system->append_equation(equ);
        }
 
        /* equation for every impedance */
        for (const auto& component : m_components) {
            LinearEquation<Complex> equ { m_num_variables };
            component->own_equ(equ);
            m_lin_equ_system->append_equation(equ);
        }

        /* Kirchhoff's voltage law */
        LoopMessage::find_loops(m_nodes[0].get(), m_num_variables);
        for (LoopMessage& message : LoopMessage::get_loops()) {
            message.equ.set_result(Complex{0.0, 0.0});
            m_lin_equ_system->append_equation(message.equ);
        }
    }

public:
    Network (double frequency) : m_frequency(frequency) {}
    Network () = delete;
    ~Network () = default;
    
    /* add a node to the graph */
    void add_node (const std::string& designator) {
        for (const auto& node : m_nodes) {
            if (designator.compare(node->designator) == 0) {
                throw std::invalid_argument("node " + designator + " already exists");
            }
        }
        std::unique_ptr<Node> new_node = std::make_unique<Node>();
        new_node->designator = designator;
        m_nodes.push_back(std::move(new_node));
    }

    /* add a resistor to the network */
    void add_resistor (const std::string& designator, double resistance, const std::string& node_0_des, const std::string& node_1_des) {
        if (component_exists(designator)) throw std::invalid_argument("component " + designator + " already exists");
        Node* node_0 = get_node(node_0_des);
        Node* node_1 = get_node(node_1_des);
        std::unique_ptr<Resistor> new_component = std::make_unique<Resistor>(designator, resistance, node_0, node_1, m_components.size());
        m_components.push_back(std::move(new_component));
    }

    /* add an inductor to the network */
    void add_inductor (const std::string& designator, double inductance, const std::string& node_0_des, const std::string& node_1_des) {
        if (component_exists(designator)) throw std::invalid_argument("component " + designator + " already exists");
        Node* node_0 = get_node(node_0_des);
        Node* node_1 = get_node(node_1_des);
        std::unique_ptr<Inductor> new_component = std::make_unique<Inductor>(designator, inductance, m_frequency, node_0, node_1, m_components.size());
        m_components.push_back(std::move(new_component));
    }

    /* add a capacitor to the network */
    void add_capacitor (const std::string& designator, double capacitance, const std::string& node_0_des, const std::string& node_1_des) {
        if (component_exists(designator)) throw std::invalid_argument("component " + designator + " already exists");
        Node* node_0 = get_node(node_0_des);
        Node* node_1 = get_node(node_1_des);
        std::unique_ptr<Capacitor> new_component = std::make_unique<Capacitor>(designator, capacitance, m_frequency, node_0, node_1, m_components.size());
        m_components.push_back(std::move(new_component));
    }

    /* add a source to the network */
    void add_source (const std::string& designator, double voltage, const std::string& node_0_des, const std::string& node_1_des) {
        /* TODO : only one source can be added? */
        if (component_exists(designator)) throw std::invalid_argument("component " + designator + " already exists");
        Node* node_0 = get_node(node_0_des);
        Node* node_1 = get_node(node_1_des);
        /* TODO : the source should send out signals of such frequencies and calculate impedance on the go */
        std::unique_ptr<Source> new_component = std::make_unique<Source>(designator, voltage, node_0, node_1, m_components.size());
        m_components.push_back(std::move(new_component));
    }

    void compute () {
        m_num_variables = 0;
        for (const auto& component : m_components) {
            m_num_variables += component->get_num_variables();
        }
        m_lin_equ_system = std::make_unique<LinearEquationSystem>(m_num_variables);
        compute_equations();
        std::vector<Complex> solution;
        bool success = m_lin_equ_system->solve(solution);
        for (const auto& c : solution) {
            std::cout << c << " ";
        }
        std::cout << std::endl;
    }

    void print () {
        std::cout << "frequency : " << m_frequency << std::endl;
        std::cout << "nodes" << std::endl;
        for (const auto& node : m_nodes) {
            std::cout << "    " << node->designator << std::endl;
        }
        std::cout << "components" << std::endl;
        for (const auto& component : m_components) {
            std::cout << "    " << component->get_designator() << std::endl;
        }
    }

    void print_equations () {
        std::cout << std::fixed << std::setprecision(2);
        std::cout << (*m_lin_equ_system) << std::endl;
    }
};

} /* namespace zcalc */