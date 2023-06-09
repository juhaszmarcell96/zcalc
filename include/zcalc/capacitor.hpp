#pragma once

#include <zcalc/impedance.hpp>

namespace zcalc {

class Capacitor : public Impedance {
public:
    Capacitor () = delete;
    Capacitor (const std::string& designator, double capacitance, double frequency, Node* node_0, Node* node_1, std::size_t id) : Impedance(designator, Complex{0.0, 0.0}, node_0, node_1, id) {
        m_value = std::polar(1.0 / (2.0 * pi * frequency * capacitance), -pi / 2.0);
    }
    ~Capacitor () = default;
};

} /* namespace zcalc */