#pragma once

#include <numbers>
#include <cmath>
#include <iostream>

namespace zcalc {
namespace math {

// f = w/(2pi)   <->   w = 2pif

class Frequency {
public:
    using frequency_t = double;
private:
    frequency_t m_frequency { 0.0 }; // rad/s
public:
    Frequency () = default;
    Frequency (double rad_per_sec) : m_frequency(rad_per_sec) {}
    ~Frequency () = default;

    frequency_t as_hz () const { return m_frequency / (2.0 * std::numbers::pi); }
    frequency_t as_rad_per_sec () const { return m_frequency; }

    void from_hz (frequency_t hz) { m_frequency = 2.0 * std::numbers::pi * hz; }
    void from_rad_per_sec (frequency_t rad_per_sec) { m_frequency = rad_per_sec; }

    friend std::ostream& operator<<(std::ostream& os, const Frequency& freq) {
        os << freq.m_frequency << "rad/s";
        return os;
    }
};

} /* namespace component */
} /* namespace zcalc */