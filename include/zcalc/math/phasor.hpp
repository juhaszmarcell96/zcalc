#pragma once

#include <zcalc/common.hpp>
#include <zcalc/math/complex.hpp>
#include <stdexcept>

namespace zcalc {
namespace math {

class Phasor {
private:
    magnitude_t m_magnitude { 0.0 }; // magnitude
    phase_t     m_phase     { 0.0 }; // phase
    frequency_t m_frequency { 0.0 }; // frequency in Hz
public:
    Phasor () = delete;
    Phasor(magnitude_t magnitude, phase_t phase, frequency_t frequency) : m_magnitude(magnitude), m_phase(phase), m_frequency(frequency) {}
    ~Phasor () = default;

    magnitude_t get_magnitude () const { return m_magnitude; }
    phase_t     get_phase     () const { return m_phase;     }
    frequency_t get_frequency () const { return m_frequency; }

    void set_magnitude (magnitude_t magnitude) { m_magnitude = magnitude; }
    void set_phase     (phase_t     phase    ) { m_phase     = phase;     }
    void set_frequency (frequency_t frequency) { m_frequency = frequency; }

    Complex to_complex () const {
        return std::polar(m_magnitude, m_phase);
    }

    static Phasor from_complex(Complex c, frequency_t frequency = 0.0) {
        return Phasor(c.abs(), c.arg(), frequency);
    }
};

} /* namespace component */
} /* namespace zcalc */