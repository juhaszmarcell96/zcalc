#pragma once

#include <numbers>
#include <cmath>
#include <iostream>

namespace zcalc {
namespace math {

// 360deg      2pi
//
// radians = pi/180 * degrees
// degrees = 180/pi * radians

class Phase {
public:
    using phase_t = double;
private:
    phase_t m_phase { 0.0 }; // rad
    explicit Phase (double rad) : m_phase(rad) {}
public:
    Phase () = default;
    ~Phase () = default;

    void from_degrees (phase_t deg) { m_phase = (std::numbers::pi / 180.0) * deg; }
    void from_radians (phase_t rad) { m_phase = rad; }
    
    phase_t as_degrees () const { return (180.0 / std::numbers::pi) * m_phase; }
    phase_t as_radians () const { return m_phase; }

    static Phase create_from_degrees (phase_t deg) { return Phase{(std::numbers::pi / 180.0) * deg}; }
    static Phase create_from_radians (phase_t rad) { return Phase{rad}; }

    friend std::ostream& operator<<(std::ostream& os, const Phase& phase) {
        os << phase.m_phase;
        return os;
    }
};

} /* namespace component */
} /* namespace zcalc */