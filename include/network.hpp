#pragma once

#include <include/impedance.hpp>
#include <include/source.hpp>
#include <include/complex.hpp>
#include <include/linear_equation_system.hpp>
#include <include/node.hpp>
#include <include/component.hpp>
#include <include/cycle.hpp>

#include <vector>
#include <string>
#include <memory>

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

    void compute_cycles ();
    void compute_equations ();
    void node_cycle (node_ptr_t node, Cycle cycle);

    bool edge_exists (const std::string& designator) const;

    double m_frequency;
public:
    Network (double frequency);
    Network () = delete;
    ~Network () = default;
    void add_node (const std::string& node_name);
    void add_resistor (const std::string& designator, double resistance, const std::string& node_0_name, const std::string& node_1_name);
    void add_inductor (const std::string& designator, double inductance, const std::string& node_0_name, const std::string& node_1_name);
    void add_capacitor (const std::string& designator, double capacitance, const std::string& node_0_name, const std::string& node_1_name);
    void add_source (const std::string& designator, double voltage, const std::string& node_0_name, const std::string& node_1_name);
    void compute ();
    void print ();
    void print_cycles ();
    void print_equations ();
};

} /* namespace zcalc */