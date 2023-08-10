#pragma once

#include <zcalc/impedance.hpp>

namespace zcalc {

class Inductor : public Impedance {
private:
    double m_inductance { 0.0 };
public:
    Inductor () = delete;
    Inductor (const std::string& designator, double inductance, double frequency, Node* node_0, Node* node_1, std::size_t id) : Impedance(designator, Complex{0.0, 0.0}, node_0, node_1, id) {
        m_value = std::polar(2.0 * pi * frequency * inductance, pi / 2.0);
    }
    ~Inductor () = default;

    void set_frequency (double frequency) override {
        m_value = std::polar(2.0 * pi * frequency * m_inductance, pi / 2.0);
    }
};

} /* namespace zcalc */