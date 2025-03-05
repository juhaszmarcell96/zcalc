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
    explicit Frequency (double rad_per_sec) : m_frequency(rad_per_sec) {}
public:
    Frequency () = default;
    ~Frequency () = default;

    frequency_t as_hz () const { return m_frequency / (2.0 * std::numbers::pi); }
    frequency_t as_rad_per_sec () const { return m_frequency; }

    void from_hz (frequency_t hz) { m_frequency = 2.0 * std::numbers::pi * hz; }
    void from_rad_per_sec (frequency_t rad_per_sec) { m_frequency = rad_per_sec; }

    static Frequency create_from_hz (frequency_t hz) { return Frequency{ 2.0 * std::numbers::pi * hz }; }
    static Frequency create_from_rad_per_sec (frequency_t rad_per_sec) { return Frequency{rad_per_sec}; }
    static Frequency create_dc () { return Frequency{}; }

    bool is_dc () const {
        return m_frequency == 0.0;
    }

    double decade () const {
        return std::log10(as_hz());
    }

    Frequency& operator*=(double value) {
        m_frequency *= value;
        return *this;
    }

    friend bool operator==(const Frequency& freq_1, const Frequency& freq_2) { return freq_1.m_frequency == freq_2.m_frequency; }
    friend bool operator!=(const Frequency& freq_1, const Frequency& freq_2) { return freq_1.m_frequency != freq_2.m_frequency; }
    friend bool operator<(const Frequency& freq_1, const Frequency& freq_2) { return freq_1.m_frequency < freq_2.m_frequency; }
    friend bool operator>(const Frequency& freq_1, const Frequency& freq_2) { return freq_1.m_frequency < freq_2.m_frequency; }
    friend bool operator<=(const Frequency& freq_1, const Frequency& freq_2) { return freq_1.m_frequency <= freq_2.m_frequency; }
    friend bool operator>=(const Frequency& freq_1, const Frequency& freq_2) { return freq_1.m_frequency <= freq_2.m_frequency; }

    Frequency operator*(const Frequency& freq) const {
        return Frequency::create_from_rad_per_sec(m_frequency * freq.m_frequency);
    }
    Frequency operator*(double mult) const {
        return Frequency::create_from_rad_per_sec(m_frequency * mult);
    }
    friend Frequency operator*(double mult, const Frequency& freq) {
        return Frequency::create_from_rad_per_sec(freq.m_frequency * mult);
    }
    Frequency operator+(const Frequency& freq) const {
        return Frequency::create_from_rad_per_sec(m_frequency + freq.m_frequency);
    }
    Frequency operator-(const Frequency& freq) const {
        return Frequency::create_from_rad_per_sec(m_frequency - freq.m_frequency);
    }

    friend std::ostream& operator<<(std::ostream& os, const Frequency& freq) {
        os << freq.m_frequency;
        //os << freq.m_frequency << "rad/s";
        return os;
    }
};

} /* namespace component */
} /* namespace zcalc */