#pragma once

#include <zcalc/component/two_pole.hpp>
#include <zcalc/math/phasor.hpp>

namespace zcalc {
namespace component {

class Source : public TwoPoleComponent {
protected:
    math::Phasor m_value { 1.0, math::Phase::create_from_degrees(0.0), math::Frequency::create_from_hz(0.0) };
public:
    Source () = delete;
    Source (math::Complex value, Node node_0, Node node_1, std::size_t id, const std::string& designator) : TwoPoleComponent(node_0, node_1, id, designator) {
        m_value = math::Phasor::from_complex(value);
    }
    Source (math::Complex value, const math::Frequency& frequency, Node node_0, Node node_1, std::size_t id, const std::string& designator) : TwoPoleComponent(node_0, node_1, id, designator) {
        m_value = math::Phasor::from_complex(value, frequency);
    }

    void set_frequency (const math::Frequency& frequency) override {
        m_value.set_frequency(frequency);
    }

    const math::Frequency& get_frequency () const override {
        return m_value.get_frequency();
    }

    bool is_source () const override { return true; }
};

} /* namespace component */
} /* namespace zcalc */