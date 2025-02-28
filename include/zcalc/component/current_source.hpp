#pragma once

#include <zcalc/component/source.hpp>

namespace zcalc {
namespace component {

class CurrentSource : public Source {
public:
    CurrentSource () = delete;
    CurrentSource (math::Complex current, Node node_0, Node node_1, std::size_t id) : Source(current, node_0, node_1, id) {}
    CurrentSource (math::Complex current, frequency_t frequency, Node node_0, Node node_1, std::size_t id) : Source(current, frequency, node_0, node_1, id) {}
    ~CurrentSource () = default;

    // normal operation -> 1*I + 0*U = current
    // eliminated       -> 1*I + 0*U = 0
    math::Complex own_i () const override {
        return math::Complex{ 1.0, 0.0 };
    }
    math::Complex own_u () const override {
        return math::Complex { 0.0, 0.0 };
    }
    math::Complex own_r () const override {
        if (m_open) { return math::Complex{ 0.0, 0.0 }; }
        return m_value.to_complex();
    }

    void eliminate () override { m_open = true; }

    void reactivate () override { m_open = false; }
};

} /* namespace component */
} /* namespace zcalc */