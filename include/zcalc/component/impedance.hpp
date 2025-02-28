#pragma once

#include <zcalc/component/two_pole.hpp>

namespace zcalc {
namespace component {

class Impedance : public TwoPoleComponent {
protected:
    math::Complex m_value { 0.0, 0.0 };
public:
    Impedance () = delete;
    Impedance (math::Complex value, Node node_0, Node node_1, id_t id) : TwoPoleComponent(node_0, node_1, id), m_value(value) {}
    ~Impedance() = default;

    void set_rectangular (double resistance, double reactance) { m_value = math::Complex {resistance, reactance}; }
    void set_polar (double modulus, double argument) { m_value = math::Complex {std::polar(modulus, argument)}; }

    math::Complex get_impedance () const { return m_value; }
    double get_modulus () const { return std::abs(m_value.get()); }
    double get_argument () const { return std::arg(m_value.get()); }
    double get_resistance () const { return std::real(m_value.get()); }
    double get_reactance () const { return std::imag(m_value.get()); }

    friend std::ostream& operator<<(std::ostream& os, const Impedance& z) {
        os << "[(" << z.get_resistance() << ") + j(" << z.get_reactance() << ")] ohm     / " << z.get_modulus() << "<" << z.get_argument() * 180.0 / pi << "° /";
        return os;
    }

    // U = Z*I -> 1*U - Z*I = 0
    // open    -> 0*U + 1*I = 0
    // short   -> 1*U + 0*I = 0
    math::Complex own_i () const override {
        if (m_open) { return math::Complex{ 1.0, 0.0 }; }
        if (m_short) { return math::Complex{ 0.0, 0.0 }; }
        return m_value * math::Complex{ -1.0, 0.0 };
    }
    math::Complex own_u () const override {
        if (m_open) { return math::Complex{ 0.0, 0.0 }; }
        if (m_short) { return math::Complex{ 1.0, 0.0 }; }
        return math::Complex { 1.0, 0.0 };
    }
    math::Complex own_r () const override {
        return math::Complex { 0.0, 0.0 };
    }

    frequency_t get_frequency () const override {
        throw std::runtime_error("why do you want the frequency of an impedance?");
    }

    void set_frequency (frequency_t frequency) override {
        throw std::runtime_error("impedance does not have an inherent frequency");
    }

    bool is_source () const override { return false; }

    void eliminate () override {
        throw std::runtime_error("cannot eliminate an impedance");
    }

    void reactivate () override {
        throw std::runtime_error("cannot reactivate an impedance");
    }
};

} /* namespace component */
} /* namespace zcalc */
