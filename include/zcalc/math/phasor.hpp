#pragma once

#include <zcalc/common.hpp>
#include <zcalc/math/complex.hpp>
#include <zcalc/math/phase.hpp>
#include <zcalc/math/frequency.hpp>
#include <stdexcept>

namespace zcalc {
namespace math {

class Phasor {
private:
    magnitude_t m_magnitude { 0.0 };
    Phase       m_phase     {};
    Frequency   m_frequency {};
public:
    Phasor () = delete;
    Phasor(magnitude_t magnitude, const Phase& phase, const Frequency& frequency) : m_magnitude(magnitude), m_phase(phase), m_frequency(frequency) {}
    Phasor(const Complex& value, const Frequency& frequency) :
        m_magnitude(value.abs()), m_phase(Phase::create_from_radians(value.arg())), m_frequency(frequency) {}
    ~Phasor () = default;

    magnitude_t      get_magnitude () const { return m_magnitude; }
    const Phase&     get_phase     () const { return m_phase;     }
    const Frequency& get_frequency () const { return m_frequency; }

    void set_magnitude (magnitude_t      magnitude) { m_magnitude = magnitude; }
    void set_phase     (const Phase&     phase    ) { m_phase     = phase;     }
    void set_frequency (const Frequency& frequency) { m_frequency = frequency; }

    Complex to_complex () const {
        return std::polar(m_magnitude, m_phase.as_radians());
    }

    static Phasor from_complex(Complex c, const Frequency& frequency = Frequency{}) {
        return Phasor { c.abs(), Phase::create_from_radians(c.arg()), frequency };
    }

    friend std::ostream& operator<<(std::ostream& os, const Phasor& phasor) {
        os << phasor.m_magnitude << "cos(" << phasor.m_frequency << "t+" << phasor.m_phase << ")" << std::endl;
        return os;
    }
};

} /* namespace component */
} /* namespace zcalc */