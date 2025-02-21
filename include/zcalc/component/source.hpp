#pragma once

#include <zcalc/common.hpp>
#include <zcalc/component/component.hpp>
#include <zcalc/math/complex.hpp>
#include <zcalc/math/phasor.hpp>

#include <string>
#include <memory>

namespace zcalc {
namespace component {

class Source : public Component {
protected:
    math::Phasor m_voltage { 1.0, 0.0, 0.0 };
public:
    Source () = delete;
    Source (Complex voltage, Node node_0, Node node_1, std::size_t id) : Component(id) {
        m_gates.push_back(node_0);
        m_gates.push_back(node_1);
        m_voltage = math::Phasor::from_complex(voltage);
    }
    Source (Complex voltage, frequency_t frequency, Node node_0, Node node_1, std::size_t id) : Component(id) {
        m_gates.push_back(node_0);
        m_gates.push_back(node_1);
        m_voltage = math::Phasor::from_complex(voltage, frequency);
    }
    ~Source () = default;

    std::size_t get_num_variables () const override {
        return 2;
    }

    Complex kcl (Node node) const override {
        if (m_gates[0] == node) { return Complex { -1.0, 0.0 }; }
        else if (m_gates[1] == node) { return Complex { 1.0, 0.0 }; }
        else { return Complex { 0.0, 0.0 }; }
    }

    Complex kvl (Node node) const override {
        if (m_gates[0] == node) { return Complex { 1.0, 0.0 }; }
        else if (m_gates[1] == node) { return Complex { -1.0, 0.0 }; }
        else { return Complex { 0.0, 0.0 }; }
    }

    // 0*I + 1*U = m_voltage
    Complex own_i () const override {
        return Complex{ 0.0, 0.0 };
    }
    Complex own_u () const override {
        return Complex { 1.0, 0.0 };
    }
    Complex own_r () const override {
        return m_voltage.to_complex();
    }

    void set_frequency (frequency_t frequency) override {
        m_voltage.set_frequency(frequency);
    }
};

} /* namespace component */
} /* namespace zcalc */