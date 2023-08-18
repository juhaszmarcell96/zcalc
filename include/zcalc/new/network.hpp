#pragma once

#include <vector>
#include <string>
#include <memory>
#include <complex>
#include <map>
#include <stdexcept>
#include <iostream>

#include "zcalc/common.hpp"
#include "zcalc/new/component.hpp"

namespace zcalc {

class Network {
private:
    const std::string input_node = "input";
    const std::string output_node = "output";
    const std::string ground_node = "ground";
    const std::string r_measure = "r_measure";

    std::map<std::string, Node> m_nodes;
    std::map<std::string, std::shared_ptr<Component>> m_components;

    typedef std::vector<std::string> loop_t;
    std::vector<loop_t> m_loops;

    void find_loop (const std::string& last_node, loop_t loop) {
        loop.push_back(last_node);
        if (m_nodes[last_node].visited) {
            return;
        }
        if (last_node.compare(ground_node) == 0) {
            m_loops.push_back(loop);
            return;
        }
        m_nodes[last_node].visited = true;
        for (const Gate& gate : m_nodes[last_node].gates) {
            if (m_components[gate.component_id]->visited) continue;
            m_components[gate.component_id]->visited = true;
            loop_t new_loop = loop;
            new_loop.push_back(std::to_string(gate.gate_id));
            new_loop.push_back(gate.component_id);
            if (gate.gate_id == 0) {
                new_loop.push_back("1");
                find_loop(m_components[gate.component_id]->get_node_1(), new_loop);
            }
            else {
                new_loop.push_back("0");
                find_loop(m_components[gate.component_id]->get_node_0(), new_loop);
            }
            m_components[gate.component_id]->visited = false;
        }
        m_nodes[last_node].visited = false;
        return;
    }

    void find_loops () {
        m_loops.clear();
        loop_t loop;
        find_loop(input_node, loop);
    }
public:
    Network () {
        m_nodes[input_node] = Node {};
        m_nodes[output_node] = Node {};
        m_nodes[ground_node] = Node {};
        std::shared_ptr<Resistor> measurement_resistor = std::make_shared<Resistor>(10, unit_prefix::giga);
        measurement_resistor->connect(output_node, ground_node);
        m_components[r_measure] = measurement_resistor;
        m_nodes[output_node].gates.push_back(Gate{.component_id=r_measure, .gate_id=0});
        m_nodes[ground_node].gates.push_back(Gate{.component_id=r_measure, .gate_id=1});
    }
    ~Network () = default;

    void add_node (const std::string& name) {
        if (m_nodes.count(name) != 0) throw std::invalid_argument("node '" + name + "' already exists");
        m_nodes[name] = Node {};
    }

    void add_resistor (const std::string& designator, const std::string& node_0, const std::string& node_1, double resistance, unit_prefix prefix = unit_prefix::base) {
        if (node_0.compare(node_1) == 0) return;
        if (m_nodes.count(node_0) == 0) throw std::invalid_argument("node '" + node_0 + "' does not exist");
        if (m_nodes.count(node_1) == 0) throw std::invalid_argument("node '" + node_1 + "' does not exist");
        if (m_components.count(designator) != 0) throw std::invalid_argument("node '" + designator + "' already exists");
        std::shared_ptr<Resistor> resistor = std::make_shared<Resistor>(resistance, prefix);
        resistor->connect(node_0, node_1);
        m_components[designator] = resistor;
        m_nodes[node_0].gates.push_back(Gate{.component_id=designator, .gate_id=0});
        m_nodes[node_1].gates.push_back(Gate{.component_id=designator, .gate_id=1});
    }

    void add_capacitor (const std::string& designator, const std::string& node_0, const std::string& node_1, double capacitance, unit_prefix prefix = unit_prefix::base) {
        if (node_0.compare(node_1) == 0) return;
        if (m_nodes.count(node_0) == 0) throw std::invalid_argument("node '" + node_0 + "' does not exist");
        if (m_nodes.count(node_1) == 0) throw std::invalid_argument("node '" + node_1 + "' does not exist");
        if (m_components.count(designator) != 0) throw std::invalid_argument("node '" + designator + "' already exists");
        std::shared_ptr<Capacitor> capacitor = std::make_shared<Capacitor>(capacitance, prefix);
        capacitor->connect(node_0, node_1);
        m_components[designator] = capacitor;
        m_nodes[node_0].gates.push_back(Gate{.component_id=designator, .gate_id=0});
        m_nodes[node_1].gates.push_back(Gate{.component_id=designator, .gate_id=1});
    }

    void add_inductor (const std::string& designator, const std::string& node_0, const std::string& node_1, double inductance, unit_prefix prefix = unit_prefix::base) {
        if (node_0.compare(node_1) == 0) return;
        if (m_nodes.count(node_0) == 0) throw std::invalid_argument("node '" + node_0 + "' does not exist");
        if (m_nodes.count(node_1) == 0) throw std::invalid_argument("node '" + node_1 + "' does not exist");
        if (m_components.count(designator) != 0) throw std::invalid_argument("node '" + designator + "' already exists");
        std::shared_ptr<Resistor> inductor = std::make_shared<Resistor>(inductance, prefix);
        inductor->connect(node_0, node_1);
        m_components[designator] = inductor;
        m_nodes[node_0].gates.push_back(Gate{.component_id=designator, .gate_id=0});
        m_nodes[node_1].gates.push_back(Gate{.component_id=designator, .gate_id=1});
    }

    std::complex<double> hjw (double frequency) {
        /* TODO : remove components that are not connected to the main circuit */
        /* TODO : there must be a path between "input" and "output" */
        find_loops();
        std::cout << "loops : " << std::endl;
        for (const auto& loop : m_loops) {
            for (const std::string& elem : loop) {
                std::cout << elem << " ";
            }
            std::cout << std::endl;
        }
    }
};

} /* namespace zcalc */