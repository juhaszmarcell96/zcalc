#pragma once

#include <zcalc/component/component.hpp>
#include <zcalc/component/impedance.hpp>
#include <zcalc/component/resistor.hpp>
#include <zcalc/component/capacitor.hpp>
#include <zcalc/component/inductor.hpp>
#include <zcalc/component/source.hpp>

#include <zcalc/math/complex.hpp>

#include <zcalc/graph/graph.hpp>

#include <vector>
#include <map>
#include <string>
#include <memory>
#include <iostream>
#include <stdexcept>
#include <optional>
#include <limits>

namespace zcalc {

class Network {
private:
    std::map<std::string, component::Node> m_nodes;
    std::map<std::string, std::shared_ptr<component::Component>> m_components;

    double m_frequency { 1.0 };

public:
    Network () {}
    ~Network () = default;

    component::Node get_node (const std::string& designator) const {
        auto node = m_nodes.find(designator);
        if (node == m_nodes.end()) { throw std::invalid_argument("node " + designator + " does not exists"); }
        return node->second;
    }

    const std::shared_ptr<component::Component> get_component (id_t id) const {
        for (const auto& [des, val] : m_components) {
            if (val->get_id() == id) {
                return val;
            }
        }
        return nullptr;
    }

    std::optional<std::string> get_designator_of_component (id_t id) const {
        for (auto& [des, val] : m_components) {
            if (val->get_id() == id) {
                return des;
            }
        }
        return std::nullopt;
    }

    /* add a source to the network */
    void add_source (const std::string& designator, double voltage, const std::string& node_0_des, const std::string& node_1_des) {
        if (m_components.contains(designator)) { throw std::invalid_argument("component " + designator + " already exists"); }
        m_components[designator] = std::make_unique<component::Source>(voltage, m_frequency, get_node(node_0_des), get_node(node_1_des), m_components.size());
    }
    
    /* add a node to the graph */
    void add_node (const std::string& designator) {
        if (m_nodes.contains(designator)) { throw std::invalid_argument("node " + designator + " already exists"); }
        m_nodes[designator] = m_nodes.size();
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

    std::size_t get_num_nodes () const {
        return m_nodes.size();
    }

    graph::Graph<id_t> to_graph () const {
        // nodes are the vertices, compnents are the edges
        const auto num_nodes = m_nodes.size();
        if (num_nodes > std::numeric_limits<graph::Vertex>::max()) {
            throw std::invalid_argument("too many nodes in the graph");
        }
        graph::Graph<id_t> g { static_cast<graph::Vertex>(num_nodes) };
        for (const auto& [des, val] : m_components) {
            g.add_edge(val->get_gate(0), val->get_gate(1), val->get_id());
        }
        return g;
    }

    graph::Graph<std::shared_ptr<component::Component>> to_graph_pointers () const {
        // nodes are the vertices, compnents are the edges
        const auto num_nodes = m_nodes.size();
        if (num_nodes > std::numeric_limits<graph::Vertex>::max()) {
            throw std::invalid_argument("too many nodes in the graph");
        }
        graph::Graph<std::shared_ptr<component::Component>> g { static_cast<graph::Vertex>(num_nodes) };
        for (const auto& [des, val] : m_components) {
            g.add_edge(val->get_gate(0), val->get_gate(1), val);
        }
        return g;
    }

    void print () {
        std::cout << "frequency : " << m_frequency << std::endl;
        std::cout << "nodes" << std::endl;
        for (const auto& [des, val] : m_nodes) {
            std::cout << "    " << des << " : " << val << std::endl;
        }
        std::cout << "components" << std::endl;
        for (const auto& [des, val] : m_components) {
            std::cout << "    " << des << " : " << val << std::endl;
        }
    }

    void set_frequency (double frequency) {
        m_frequency = frequency;
        for (const auto& component : m_components) {
            component.second->set_frequency(frequency);
        }
    }
};

} /* namespace zcalc */