#pragma once

#include <zcalc/component/source.hpp>

namespace zcalc {
namespace component {

class VoltageSource : public Source {
public:
    VoltageSource () = delete;
    VoltageSource (math::Complex voltage, Node node_0, Node node_1, std::size_t id) : Source(voltage, node_0, node_1, id) {}
    VoltageSource (math::Complex voltage, frequency_t frequency, Node node_0, Node node_1, std::size_t id) : Source(voltage, frequency, node_0, node_1, id) {}
    ~VoltageSource () = default;

    // normal operation -> 0*I + 1*U = voltage
    // eliminated       -> 0*I + 1*U = 0
    math::Complex own_i () const override {
        return math::Complex{ 0.0, 0.0 };
    }
    math::Complex own_u () const override {
        return math::Complex { 1.0, 0.0 };
    }
    math::Complex own_r () const override {
        if (m_short) { return math::Complex{ 0.0, 0.0 }; }
        return m_value.to_complex();
    }

    void eliminate () override { m_short = true; }

    void reactivate () override { m_short = false; }
};

} /* namespace component */
} /* namespace zcalc */