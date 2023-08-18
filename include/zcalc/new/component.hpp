#pragma once

#include <vector>
#include <string>
#include <complex>
#include <stdexcept>

#include "zcalc/common.hpp"

namespace zcalc {

typedef std::complex<double> impedance_t;

struct Gate {
    std::string component_id;
    std::size_t gate_id { 0 };
};

struct Node {
    std::vector<Gate> gates;

    bool visited { false };
};

enum class component_type {
    resistor,
    capacitor,
    inductor
};

class Component {
protected:
    component_type m_type;
    std::string m_node_0;
    std::string m_node_1;
public:
    Component () = delete;
    Component (component_type type) : m_type(type) {}

    virtual impedance_t get_impedance (double frequency) const = 0;

    void connect (const std::string& node_0, const std::string& node_1) {
        m_node_0 = node_0;
        m_node_1 = node_1;
    }

    const std::string& get_node_0 () const { return m_node_0; }
    const std::string& get_node_1 () const { return m_node_1; }

    bool visited { false };
};

class Resistor : public Component {
private:
    double m_resistance { 0.0 };
public:
    Resistor () = delete;
    Resistor (double resistance, unit_prefix prefix = unit_prefix::base) : Component(component_type::resistor) {
        m_resistance = get_prefixed_unit_value(resistance, prefix);
    }

    impedance_t get_impedance (double frequency) const override {
        return impedance_t {m_resistance, 0.0};
    }
};

class Capacitor : public Component {
private:
    double m_capacitance { 0.0 };
public:
    Capacitor () = delete;
    Capacitor (double capacitance, unit_prefix prefix = unit_prefix::base) : Component(component_type::capacitor) {
        m_capacitance = get_prefixed_unit_value(capacitance, prefix);
    }

    impedance_t get_impedance (double frequency) const override {
        return std::polar(1.0 / (2.0 * pi * frequency * m_capacitance), -pi / 2.0);
    }
};

class Inductor : public Component {
private:
    double m_inductance { 0.0 };
public:
    Inductor () = delete;
    Inductor (double inductance, unit_prefix prefix = unit_prefix::base) : Component(component_type::capacitor) {
        m_inductance = get_prefixed_unit_value(inductance, prefix);
    }

    impedance_t get_impedance (double frequency) const override {
        return std::polar(2.0 * pi * frequency * m_inductance, pi / 2.0);
    }
};

} /* namespace zcalc */