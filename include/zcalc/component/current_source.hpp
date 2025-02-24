#pragma once

#include <zcalc/common.hpp>
#include <zcalc/component/component.hpp>
#include <zcalc/math/complex.hpp>
#include <zcalc/math/phasor.hpp>

#include <string>
#include <memory>

namespace zcalc {
namespace component {

class CurrentSource : public Component {
protected:
    math::Phasor m_current { 1.0, 0.0, 0.0 };
public:
    CurrentSource () = delete;
    CurrentSource (math::Complex current, Node node_0, Node node_1, std::size_t id) : Component(id) {
        m_gates.push_back(node_0);
        m_gates.push_back(node_1);
        m_current = math::Phasor::from_complex(current);
    }
    CurrentSource (math::Complex current, frequency_t frequency, Node node_0, Node node_1, std::size_t id) : Component(id) {
        m_gates.push_back(node_0);
        m_gates.push_back(node_1);
        m_current = math::Phasor::from_complex(current, frequency);
    }
    ~CurrentSource () = default;

    std::size_t get_num_variables () const override {
        return 2;
    }

    math::Complex kcl (Node node) const override {
        if (m_gates[0] == node) { return math::Complex { -1.0, 0.0 }; }
        else if (m_gates[1] == node) { return math::Complex { 1.0, 0.0 }; }
        else { return math::Complex { 0.0, 0.0 }; }
    }

    math::Complex kvl (Node node) const override {
        if (m_gates[0] == node) { return math::Complex { 1.0, 0.0 }; }
        else if (m_gates[1] == node) { return math::Complex { -1.0, 0.0 }; }
        else { return math::Complex { 0.0, 0.0 }; }
    }

    // 0*I + 1*U = m_voltage
    math::Complex own_i () const override {
        return math::Complex{ 1.0, 0.0 };
    }
    math::Complex own_u () const override {
        return math::Complex { 0.0, 0.0 };
    }
    math::Complex own_r () const override {
        return m_current.to_complex();
    }

    void set_frequency (frequency_t frequency) override {
        m_current.set_frequency(frequency);
    }
};

} /* namespace component */
} /* namespace zcalc */