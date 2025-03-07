#pragma once

#include <zcalc/component/component.hpp>
#include <zcalc/component/impedance.hpp>
#include <zcalc/component/resistor.hpp>
#include <zcalc/component/capacitor.hpp>
#include <zcalc/component/inductor.hpp>
#include <zcalc/component/voltage_source.hpp>
#include <zcalc/component/current_source.hpp>
#include <zcalc/component/voltmeter.hpp>
#include <zcalc/component/ammeter.hpp>
#include <zcalc/component/voltage_controlled_current_source.hpp>

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
    std::map<std::string, std::shared_ptr<component::IComponent>> m_components;
public:
    Network () {}
    ~Network () = default;

    component::Node get_node (const std::string& designator) const {
        auto node = m_nodes.find(designator);
        if (node == m_nodes.end()) { throw std::invalid_argument("node " + designator + " does not exists"); }
        return node->second;
    }

    id_t get_component_id (std::string designator) const {
        if (!m_components.contains(designator)) { throw std::invalid_argument("component " + designator + " does not exists"); }
        return m_components.at(designator)->get_id();
    }

    std::shared_ptr<component::IComponent> get_component (const std::string& designator) {
        if (!m_components.contains(designator)) { throw std::invalid_argument("component " + designator + " does not exists"); }
        return m_components.at(designator);
    }

    const std::shared_ptr<component::IComponent> get_component (id_t id) const {
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

    /* add a voltage source to the network */
    id_t add_voltage_source (const std::string& designator, double voltage, const math::Frequency& frequency, const std::string& node_0_des, const std::string& node_1_des) {
        if (m_components.contains(designator)) { throw std::invalid_argument("component " + designator + " already exists"); }
        const auto id = m_components.size();
        m_components[designator] = std::make_shared<component::VoltageSource>(voltage, frequency, get_node(node_0_des), get_node(node_1_des), id, designator);
        return id;
    }

    /* add a current source to the network */
    id_t add_current_source (const std::string& designator, double current, const math::Frequency& frequency, const std::string& node_0_des, const std::string& node_1_des) {
        if (m_components.contains(designator)) { throw std::invalid_argument("component " + designator + " already exists"); }
        const auto id = m_components.size();
        m_components[designator] = std::make_shared<component::CurrentSource>(current, frequency, get_node(node_0_des), get_node(node_1_des), id, designator);
        return id;
    }
    
    /* add a node to the graph */
    component::Node add_node (const std::string& designator) {
        if (m_nodes.contains(designator)) { throw std::invalid_argument("node " + designator + " already exists"); }
        const auto node = m_nodes.size();
        m_nodes[designator] = node;
        return node;
    }

    /* add a resistor to the network */
    id_t add_resistor (const std::string& designator, double resistance, const std::string& node_0_des, const std::string& node_1_des) {
        if (m_components.contains(designator)) { throw std::invalid_argument("component " + designator + " already exists"); }
        const auto id = m_components.size();
        m_components[designator] = std::make_shared<component::Resistor>(resistance, get_node(node_0_des), get_node(node_1_des), id, designator);
        return id;
    }

    /* add an inductor to the network */
    id_t add_inductor (const std::string& designator, double inductance, const std::string& node_0_des, const std::string& node_1_des) {
        if (m_components.contains(designator)) { throw std::invalid_argument("component " + designator + " already exists"); }
        const auto id = m_components.size();
        m_components[designator] = std::make_shared<component::Inductor>(inductance, get_node(node_0_des), get_node(node_1_des), id, designator);
        return id;
    }

    /* add a capacitor to the network */
    id_t add_capacitor (const std::string& designator, double capacitance, const std::string& node_0_des, const std::string& node_1_des) {
        if (m_components.contains(designator)) { throw std::invalid_argument("component " + designator + " already exists"); }
        const auto id = m_components.size();
        m_components[designator] = std::make_shared<component::Capacitor>(capacitance, get_node(node_0_des), get_node(node_1_des), id, designator);
        return id;
    }

    /* add a voltmeter to the network */
    id_t add_voltmeter (const std::string& designator, const std::string& node_0_des, const std::string& node_1_des) {
        if (m_components.contains(designator)) { throw std::invalid_argument("component " + designator + " already exists"); }
        const auto id = m_components.size();
        m_components[designator] = std::make_shared<component::Voltmeter>(get_node(node_0_des), get_node(node_1_des), id, designator);
        return id;
    }

    /* add an ammeter to the network */
    id_t add_ammeter (const std::string& designator, const std::string& node_0_des, const std::string& node_1_des) {
        if (m_components.contains(designator)) { throw std::invalid_argument("component " + designator + " already exists"); }
        const auto id = m_components.size();
        m_components[designator] = std::make_shared<component::Ammeter>(get_node(node_0_des), get_node(node_1_des), id, designator);
        return id;
    }

    /* voltage controlled current source */
    id_t add_voltage_controlled_current_source (const std::string& designator, const std::string& node_0_des, const std::string& node_1_des, const std::string& dependency, double transconductance) {
        if (m_components.contains(designator)) { throw std::invalid_argument("component " + designator + " already exists"); }
        const auto id = m_components.size();
        m_components[designator] = std::make_shared<component::VoltageControlledCurrentSource>(get_node(node_0_des), get_node(node_1_des), id, designator, dependency, transconductance);
        return id;
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

    graph::Graph<component::IComponent*> to_graph_pointers () const {
        // nodes are the vertices, compnents are the edges
        const auto num_nodes = m_nodes.size();
        if (num_nodes > std::numeric_limits<graph::Vertex>::max()) {
            throw std::invalid_argument("too many nodes in the graph");
        }
        graph::Graph<component::IComponent*> g { static_cast<graph::Vertex>(num_nodes) };
        for (const auto& [des, val] : m_components) {
            val->add_to_graph(g);
        }
        return g;
    }

    void print () const {
        std::cout << "nodes" << std::endl;
        for (const auto& [des, val] : m_nodes) {
            std::cout << "    " << des << " : " << val << std::endl;
        }
        std::cout << "components" << std::endl;
        for (const auto& [des, val] : m_components) {
            std::cout << "    " << des << " : " << val << std::endl;
        }
    }

    // void set_frequency (double frequency) {
    //     m_frequency = frequency;
    //     for (const auto& component : m_components) {
    //         component.second->set_frequency(frequency);
    //     }
    // }
};

} /* namespace zcalc */