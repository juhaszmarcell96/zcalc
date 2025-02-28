#pragma once

#include <zcalc/component/two_pole.hpp>
#include <zcalc/math/phasor.hpp>

namespace zcalc {
namespace component {

class Source : public TwoPoleComponent {
protected:
    math::Phasor m_value { 1.0, 0.0, 0.0 };
public:
    Source () = delete;
    Source (math::Complex value, Node node_0, Node node_1, std::size_t id) : TwoPoleComponent(node_0, node_1, id) {
        m_value = math::Phasor::from_complex(value);
    }
    Source (math::Complex value, frequency_t frequency, Node node_0, Node node_1, std::size_t id) : TwoPoleComponent(node_0, node_1, id) {
        m_value = math::Phasor::from_complex(value, frequency);
    }

    void set_frequency (frequency_t frequency) override {
        m_value.set_frequency(frequency);
    }

    frequency_t get_frequency () const override {
        return m_value.get_frequency();
    }

    bool is_source () const override { return true; }
};

} /* namespace component */
} /* namespace zcalc */