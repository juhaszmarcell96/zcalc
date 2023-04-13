#pragma once

#include <include/impedance.hpp>

#include <vector>
#include <string>
#include <memory>

namespace zcalc {

class Network {
private:
    double m_frequency;
    std::vector<std::shared_ptr<Impedance>> m_components;
    std::string m_ref_node;
public:
    Network() = delete;
    ~Network() = default;
    Network(double frequency, const std::string& ref_node);

    void add_resistor (double resistance, const std::string& endpoint_0, const std::string& endpoint_1);
    void add_capacitor (double capacitance, const std::string& endpoint_0, const std::string& endpoint_1);
    void add_inductor (double inductance, const std::string& endpoint_0, const std::string& endpoint_1);

    void clear ();

    Impedance calculate_impedance (const std::string& input_node, const std::string& output_node, const Impedance& termination);
};

} /* namespace zcalc */