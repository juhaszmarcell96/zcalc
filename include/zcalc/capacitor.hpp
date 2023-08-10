#pragma once

#include <zcalc/impedance.hpp>

namespace zcalc {

class Capacitor : public Impedance {
private:
    double m_capacitance { 0.0 };
public:
    Capacitor () = delete;
    Capacitor (const std::string& designator, double capacitance, double frequency, Node* node_0, Node* node_1, std::size_t id) : Impedance(designator, Complex{0.0, 0.0}, node_0, node_1, id) {
        m_value = std::polar(1.0 / (2.0 * pi * frequency * capacitance), -pi / 2.0);
        m_capacitance = capacitance;
    }
    ~Capacitor () = default;

    void set_frequency (double frequency) override {
        m_value = std::polar(1.0 / (2.0 * pi * frequency * m_capacitance), -pi / 2.0);
    }
};

} /* namespace zcalc */