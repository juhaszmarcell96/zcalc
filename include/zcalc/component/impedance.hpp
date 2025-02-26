#pragma once

#include <zcalc/common.hpp>
#include <zcalc/component/component.hpp>
#include <zcalc/math/complex.hpp>

#include <complex>
#include <memory>

namespace zcalc {
namespace component {

class Impedance : public Component {
protected:
    math::Complex m_value { 0.0, 0.0 };
    bool m_short { false };
    bool m_open { false };
public:
    Impedance () = delete;
    Impedance (math::Complex value, Node node_0, Node node_1, id_t id) : Component(id), m_value(value) {
        m_gates.push_back(node_0);
        m_gates.push_back(node_1);
    }
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

    std::size_t get_num_variables () const override {
        return 2;
    }

    frequency_t get_frequency () const override {
        throw std::runtime_error("why do you want the frequency of an impedance?");
    }

    math::Complex kcl (Node node) const override {
        if (m_open) { return math::Complex { 0.0, 0.0 }; } // open circuit -> no current
        if (m_gates[0] == node) { return math::Complex { -1.0, 0.0 }; }
        else if (m_gates[1] == node) { return math::Complex { 1.0, 0.0 }; }
        else { return math::Complex { 0.0, 0.0 }; }
    }

    math::Complex kvl (Node node) const override {
        if (m_short) { return math::Complex{ 0.0, 0.0 }; } // short circuit -> no voltage
        if (m_gates[0] == node) { return math::Complex { 1.0, 0.0 }; }
        else if (m_gates[1] == node) { return math::Complex { -1.0, 0.0 }; }
        else { return math::Complex { 0.0, 0.0 }; }
    }

    // U = Z * I -> 1 * U - Z * I = 0
    // open or short -> no own equation -> 0 + 0 = 0
    math::Complex own_i () const override {
        if (m_open || m_short) { return math::Complex{ 0.0, 0.0 }; }
        return m_value * math::Complex{ -1.0, 0.0 };
    }
    math::Complex own_u () const override {
        if (m_open || m_short) { return math::Complex{ 0.0, 0.0 }; }
        return math::Complex { 1.0, 0.0 };
    }
    math::Complex own_r () const override {
        if (m_open || m_short) { return math::Complex{ 0.0, 0.0 }; }
        return math::Complex { 0.0, 0.0 };
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
