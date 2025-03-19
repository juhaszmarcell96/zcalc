/*
 * Copyright (C) 2025 Marcell Juhasz
 *
 * This software is licensed under a non-commercial license.
 * Non-commercial use (personal, academic, research) is allowed for free.
 * Commercial use requires a paid license.
 * Hosting as a service is prohibited without explicit permission.
 *
 * See LICENSE for details or contact marcell.juhasz96@gmail.com.
 */

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
#include <zcalc/component/voltage_controlled_voltage_source.hpp>
#include <zcalc/component/current_controlled_current_source.hpp>
#include <zcalc/component/current_controlled_voltage_source.hpp>
#include <zcalc/component/ideal_transformer_half.hpp>
#include <zcalc/component/gyrator_half.hpp>
#include <zcalc/component/open_circuit.hpp>
#include <zcalc/component/short_circuit.hpp>
#include <zcalc/component/coupled_inductor_half.hpp>

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

    void component_must_not_exist (const std::string& designator) const {
        if (m_components.contains(designator)) { throw std::invalid_argument("component " + designator + " already exists"); }
    }
public:
    Network () = default;
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
    component::IComponent* add_voltage_source (const std::string& designator, double voltage, const math::Frequency& frequency, const std::string& node_0, const std::string& node_1) {
        component_must_not_exist(designator);
        const auto id = m_components.size();
        auto component = std::make_shared<component::VoltageSource>(voltage, frequency, get_node(node_0), get_node(node_1), id, designator);
        m_components[designator] = component;
        return component.get();
    }

    /* add a current source to the network */
    component::IComponent* add_current_source (const std::string& designator, double current, const math::Frequency& frequency, const std::string& node_0, const std::string& node_1) {
        component_must_not_exist(designator);
        const auto id = m_components.size();
        auto component = std::make_shared<component::CurrentSource>(current, frequency, get_node(node_0), get_node(node_1), id, designator);
        m_components[designator] = component;
        return component.get();
    }
    
    /* add a node to the graph */
    component::Node add_node (const std::string& designator) {
        if (m_nodes.contains(designator)) { throw std::invalid_argument("node " + designator + " already exists"); }
        const auto node = m_nodes.size();
        m_nodes[designator] = node;
        return node;
    }

    /* add a resistor to the network */
    component::IComponent* add_resistor (const std::string& designator, double resistance, const std::string& node_0, const std::string& node_1) {
        component_must_not_exist(designator);
        const auto id = m_components.size();
        auto component = std::make_shared<component::Resistor>(resistance, get_node(node_0), get_node(node_1), id, designator);
        m_components[designator] = component;
        return component.get();
    }

    /* add an inductor to the network */
    component::IComponent* add_inductor (const std::string& designator, double inductance, const std::string& node_0, const std::string& node_1) {
        component_must_not_exist(designator);
        const auto id = m_components.size();
        auto component = std::make_shared<component::Inductor>(inductance, get_node(node_0), get_node(node_1), id, designator);
        m_components[designator] = component;
        return component.get();
    }

    /* add a capacitor to the network */
    component::IComponent* add_capacitor (const std::string& designator, double capacitance, const std::string& node_0, const std::string& node_1) {
        component_must_not_exist(designator);
        const auto id = m_components.size();
        auto component = std::make_shared<component::Capacitor>(capacitance, get_node(node_0), get_node(node_1), id, designator);
        m_components[designator] = component;
        return component.get();
    }

    /* add a voltmeter to the network */
    component::IComponent* add_voltmeter (const std::string& designator, const std::string& node_0, const std::string& node_1) {
        component_must_not_exist(designator);
        const auto id = m_components.size();
        auto component = std::make_shared<component::Voltmeter>(get_node(node_0), get_node(node_1), id, designator);
        m_components[designator] = component;
        return component.get();
    }

    /* add an ammeter to the network */
    component::IComponent* add_ammeter (const std::string& designator, const std::string& node_0, const std::string& node_1) {
        component_must_not_exist(designator);
        const auto id = m_components.size();
        auto component = std::make_shared<component::Ammeter>(get_node(node_0), get_node(node_1), id, designator);
        m_components[designator] = component;
        return component.get();
    }

    /* voltage-controlled voltage source */
    component::IComponent* add_voltage_controlled_voltage_source (const std::string& designator, const std::string& node_0, const std::string& node_1, const component::IComponent* dependency, double voltage_gain) {
        component_must_not_exist(designator);
        const auto id = m_components.size();
        auto component = std::make_shared<component::VoltageControlledVoltageSource>(get_node(node_0), get_node(node_1), id, designator, dependency, voltage_gain);
        m_components[designator] = component;
        return component.get();
    }

    /* voltage-controlled current source */
    component::IComponent* add_voltage_controlled_current_source (const std::string& designator, const std::string& node_0, const std::string& node_1, const component::IComponent* dependency, double transconductance) {
        component_must_not_exist(designator);
        const auto id = m_components.size();
        auto component = std::make_shared<component::VoltageControlledCurrentSource>(get_node(node_0), get_node(node_1), id, designator, dependency, transconductance);
        m_components[designator] = component;
        return component.get();
    }

    /* current-controlled voltage source */
    component::IComponent* add_current_controlled_voltage_source (const std::string& designator, const std::string& node_0, const std::string& node_1, const component::IComponent* dependency, double transresistance) {
        component_must_not_exist(designator);
        const auto id = m_components.size();
        auto component = std::make_shared<component::CurrentControlledVoltageSource>(get_node(node_0), get_node(node_1), id, designator, dependency, transresistance);
        m_components[designator] = component;
        return component.get();
    }

    /* current-controlled current source */
    component::IComponent* add_current_controlled_current_source (const std::string& designator, const std::string& node_0, const std::string& node_1, const component::IComponent* dependency, double current_gain) {
        component_must_not_exist(designator);
        const auto id = m_components.size();
        auto component = std::make_shared<component::CurrentControlledCurrentSource>(get_node(node_0), get_node(node_1), id, designator, dependency, current_gain);
        m_components[designator] = component;
        return component.get();
    }

    /* ideal transformer */
    void add_ideal_transformer (const std::string& designator, const std::string& node_0, const std::string& node_1, const std::string& node_2, const std::string& node_3, double transfer_value) {
        const std::string first_half_des = designator + "_1";
        const std::string second_half_des = designator + "_2";
        component_must_not_exist(first_half_des);
        component_must_not_exist(second_half_des);
        const auto id_1 = m_components.size();
        auto first_half = std::make_shared<component::IdealTransformerHalf>(get_node(node_0), get_node(node_1), id_1, first_half_des, transfer_value, true);
        m_components[first_half_des] = first_half;
        const auto id_2 = m_components.size();
        auto second_half = std::make_shared<component::IdealTransformerHalf>(get_node(node_2), get_node(node_3), id_2, second_half_des, transfer_value, false);
        m_components[second_half_des] = second_half;
        first_half->set_other_half(second_half.get());
        second_half->set_other_half(first_half.get());
    }

    /* gyrator */
    void add_gyrator (const std::string& designator, const std::string& node_0, const std::string& node_1, const std::string& node_2, const std::string& node_3, double gyration_resistance) {
        const std::string first_half_des = designator + "_1";
        const std::string second_half_des = designator + "_2";
        component_must_not_exist(first_half_des);
        component_must_not_exist(second_half_des);
        const auto id_1 = m_components.size();
        auto first_half = std::make_shared<component::GyratorHalf>(get_node(node_0), get_node(node_1), id_1, first_half_des, gyration_resistance, true);
        m_components[first_half_des] = first_half;
        const auto id_2 = m_components.size();
        auto second_half = std::make_shared<component::GyratorHalf>(get_node(node_2), get_node(node_3), id_2, second_half_des, gyration_resistance, false);
        m_components[second_half_des] = second_half;
        first_half->set_other_half(second_half.get());
        second_half->set_other_half(first_half.get());
    }

    /* ideal amplifier */
    void add_ideal_amplifier (const std::string& designator, const std::string& node_0, const std::string& node_1, const std::string& node_2, const std::string& node_3, double gain) {
        const std::string open_circuit_des = designator + "_1";
        const std::string dependent_source_des = designator + "_2";
        component_must_not_exist(open_circuit_des);
        component_must_not_exist(dependent_source_des);
        const auto id = m_components.size();
        auto open_circuit = std::make_shared<component::OpenCircuit>(get_node(node_0), get_node(node_1), id, open_circuit_des);
        m_components[open_circuit_des] = open_circuit;
        add_voltage_controlled_voltage_source(dependent_source_des, node_2, node_3, open_circuit.get(), gain);
    }

    /* coupled inductor */
    void add_coupled_inductor (const std::string& designator, const std::string& node_0, const std::string& node_1, const std::string& node_2, const std::string& node_3, double self_inductance_1, double self_inductance_2, double mutual_inductance) {
        const std::string first_half_des = designator + "_1";
        const std::string second_half_des = designator + "_2";
        component_must_not_exist(first_half_des);
        component_must_not_exist(second_half_des);
        const auto id_1 = m_components.size();
        auto first_half = std::make_shared<component::CoupledInductorHalf>(get_node(node_0), get_node(node_1), id_1, first_half_des, self_inductance_1, mutual_inductance);
        m_components[first_half_des] = first_half;
        const auto id_2 = m_components.size();
        auto second_half = std::make_shared<component::CoupledInductorHalf>(get_node(node_2), get_node(node_3), id_2, second_half_des, self_inductance_2, mutual_inductance);
        m_components[second_half_des] = second_half;
        first_half->set_other_half(second_half.get());
        second_half->set_other_half(first_half.get());
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
};

} /* namespace zcalc */