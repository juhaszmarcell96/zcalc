#pragma once

#include <zcalc/internal/node.hpp>

#include <zcalc/impedance.hpp>

namespace zcalc {

class Inductor : public Impedance {
public:
    Inductor () = delete;
    Inductor (const std::string& designator, double inductance, double frequency, Node* node_0, Node* node_1, std::size_t id) : Impedance(designator, Complex{0.0, 0.0}, node_0, node_1, id) {
        m_value = std::polar(2.0 * pi * frequency * inductance, pi / 2.0);
    }
    ~Inductor () = default;
};

} /* namespace zcalc */