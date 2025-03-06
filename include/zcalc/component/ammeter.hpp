#pragma once

#include <zcalc/component/two_pole.hpp>
#include <zcalc/math/phasor.hpp>

namespace zcalc {
namespace component {

class Ammeter : public TwoPoleComponent {
public:
    Ammeter () = delete;
    Ammeter (Node node_0, Node node_1, std::size_t id) : TwoPoleComponent(node_0, node_1, id) {
        m_short = true; // short circuit
    }

    const math::Frequency& get_frequency () const override {
        throw std::runtime_error("why do you want the frequency of a ammeter?");
    }

    void set_frequency (const math::Frequency& frequency) override {}

    // ideal ampere meter -> no voltage drom -> 0*I + 1*U = 0
    math::Complex own_i () const override {
        return math::Complex { 0.0, 0.0 };
    }
    math::Complex own_u () const override {
        return math::Complex{ 1.0, 0.0 };
    }
    math::Complex own_r () const override {
        return math::Complex{ 0.0, 0.0 };
    }

    bool is_source () const override { return false; }

    void eliminate () override {
        throw std::runtime_error("cannot eliminate an ammeter");
    }

    void reactivate () override {
        throw std::runtime_error("cannot reactivate an ammeter");
    }
};

} /* namespace component */
} /* namespace zcalc */