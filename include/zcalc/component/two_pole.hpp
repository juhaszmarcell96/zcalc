#pragma once

#include <zcalc/component/component.hpp>

namespace zcalc {
namespace component {

class TwoPoleComponent : public ComponentBase {
protected:
    bool m_short { false };
    bool m_open { false };
public:
    TwoPoleComponent () = delete;
    TwoPoleComponent (Node node_0, Node node_1, id_t id) : ComponentBase(id) {
        m_gates.push_back(node_0);
        m_gates.push_back(node_1);
    }
    ~TwoPoleComponent() = default;

    std::size_t get_num_variables () const override { return 2; }

    math::Complex kcl (Node node) const override {
        if (m_open) { return math::Complex { 0.0, 0.0 }; } // open circuit -> no current
        if (m_gates[0] == node) { return math::Complex { -1.0, 0.0 }; }
        else if (m_gates[1] == node) { return math::Complex { 1.0, 0.0 }; }
        else { return math::Complex { 0.0, 0.0 }; }
    }

    math::Complex kvl (Node node) const override {
        if (m_short) { return math::Complex{ 0.0, 0.0 }; } // short circuit -> no voltage
        if (m_gates[0] == node) { return math::Complex { 1.0, 0.0 }; }
        else if (m_gates[1] == node) { return math::Complex { -1.0, 0.0 }; }
        else { return math::Complex { 0.0, 0.0 }; }
    }
};

} /* namespace component */
} /* namespace zcalc */
