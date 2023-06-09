#pragma once

#include <zcalc/internal/component.hpp>
#include <zcalc/internal/node.hpp>
#include <zcalc/internal/complex.hpp>
#include <zcalc/internal/loop_message.hpp>

#include <complex>
#include <memory>
#include <exception>

namespace zcalc {

class Impedance : public Component {
protected:
    Complex m_value;
public:
    Impedance () = default;
    Impedance (const std::string& designator, Complex value, Node* node_0, Node* node_1, std::size_t id) : Component(designator, id), m_value(value) {
        std::unique_ptr<Gate> gate_0 = std::make_unique<Gate>();
        gate_0->designator = "0";
        gate_0->node = node_0;
        gate_0->component = this;
        m_gates.push_back(std::move(gate_0));

        std::unique_ptr<Gate> gate_1 = std::make_unique<Gate>();
        gate_1->designator = "1";
        gate_1->node = node_1;
        gate_1->component = this;
        m_gates.push_back(std::move(gate_1));
    }
    Impedance (Complex value) : Component("", 0), m_value(value) {}
    ~Impedance() = default;

    void set_rectangular (double resistance, double reactance) { m_value = Complex {resistance, reactance}; }
    void set_polar (double modulus, double argument) { m_value = Complex {std::polar(modulus, argument)}; }

    Complex get_impedance () const { return m_value; }
    double get_modulus () const { return std::abs(m_value.get()); }
    double get_argument () const { return std::arg(m_value.get()); }
    double get_resistance () const { return std::real(m_value.get()); }
    double get_reactance () const { return std::imag(m_value.get()); }

    friend std::ostream& operator<<(std::ostream& os, const Impedance& z) {
        os << "[(" << z.get_resistance() << ") + j(" << z.get_reactance() << ")] ohm     / " << z.get_modulus() << "<" << z.get_argument() * 180.0 / pi << "° /";
        return os;
    }

    static Impedance series (const Impedance& z1, const Impedance& z2) { return z1.m_value + z2.m_value; }
    static Impedance parallel (const Impedance& z1, const Impedance& z2) {
        /* Z1 || Z2 = (Z1*Z2) / (Z1+Z2) */
        return (z1.m_value * z2.m_value) / (z1.m_value + z2.m_value);
    }

    std::size_t get_num_variables () const override {
        return 2;
    }

    void kcl(const Node* node, LinearEquation<Complex>& equ) const override {
        /* current direction is assumed to be from node_0 to node_1 */
        Complex coeff { 0.0, 0.0 };
        if (m_gates[0]->node == node) coeff = Complex { -1.0, 0.0 };
        else if (m_gates[1]->node == node) coeff = Complex { 1.0, 0.0 };

        equ[2 * get_id() + equ_current_offset] = coeff;
        equ[2 * get_id() + equ_voltage_offset] = Complex{0.0, 0.0};
    }

    void own_equ(LinearEquation<Complex>& equ) const override {
        /* U = Z * I -> U - ZI = 0 */
        equ[2 * get_id() + equ_current_offset] = m_value * Complex{-1.0, 0.0};
        equ[2 * get_id() + equ_voltage_offset] = Complex { 1.0, 0.0 };
        equ.set_result(Complex { 0.0, 0.0 });
    }

    void propagate (LoopMessage message, const Gate* source_gate) const override {
        /* voltage direction points from gate 0 to gate 1 */
        if (m_gates[0].get() == source_gate) {
            /* loop points in the same direction */
            message.equ[2 * get_id() + equ_current_offset] = Complex{ 0.0, 0.0 };
            message.equ[2 * get_id() + equ_voltage_offset] = Complex { 1.0, 0.0 };
            m_gates[1]->node->propagate(message, source_gate);
        }
        else if (m_gates[1].get() == source_gate) {
            /* loop points in the opposite direction */
            message.equ[2 * get_id() + equ_current_offset] = Complex{ 0.0, 0.0 };
            message.equ[2 * get_id() + equ_voltage_offset] = Complex { -1.0, 0.0 };
            m_gates[0]->node->propagate(message, source_gate);
        }
        else {
            throw std::invalid_argument("gate does not belong to component");
        }
    }
};

} /* namespace zcalc */
