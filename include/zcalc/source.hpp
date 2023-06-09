#pragma once

#include <zcalc/internal/node.hpp>
#include <zcalc/internal/component.hpp>
#include <zcalc/internal/complex.hpp>

#include <string>
#include <memory>

namespace zcalc {

class Source : public Component {
protected:
    Complex m_voltage;
public:
    Source () = delete;
    Source (const std::string& designator, Complex voltage, Node* node_0, Node* node_1, std::size_t id) : Component(designator, id), m_voltage(voltage) {
        std::unique_ptr<Gate> gate_0 = std::make_unique<Gate>();
        gate_0->designator = "0";
        gate_0->node = node_0;
        m_gates.push_back(std::move(gate_0));

        std::unique_ptr<Gate> gate_1 = std::make_unique<Gate>();
        gate_1->designator = "1";
        gate_1->node = node_1;
        m_gates.push_back(std::move(gate_1));
    }
    ~Source () = default;

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
        /* U = m_voltage */
        equ[2 * get_id() + equ_current_offset] = Complex { 0.0, 0.0 };
        equ[2 * get_id() + equ_voltage_offset] = Complex { 1.0, 0.0 };
        equ.set_result(m_voltage);
    }

/*
    void kvl(const Node* node, LinearEquation<Complex>& equ) const override {
        Complex coeff { 0.0, 0.0 };
        if (m_gates[0]->node == node) coeff = m_voltage;
        else if (m_gates[0]->node == node) coeff = m_voltage * Complex { -1.0, 0.0 };

        equ[2 * get_id() + equ_current_offset] = coeff;
        equ[2 * get_id() + equ_voltage_offset] = Complex{0.0, 0.0};
    }
*/
};

} /* namespace zcalc */