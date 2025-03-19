/*
 * Copyright (C) 2025 Marcell Juhasz
 *
 * This software is licensed under a non-commercial license.
 * Non-commercial use (personal, academic, research) is allowed for free.
 * Commercial use requires a paid license.
 * Hosting as a service is prohibited without explicit permission.
 *
 * See LICENSE for details or contact marcell.juhasz96@gmail.com.
 */

#pragma once

#include <numbers>

#include <zcalc/component/two_pole.hpp>

namespace zcalc {
namespace component {

class Impedance : public TwoPoleComponent {
protected:
    math::Complex m_value { 0.0, 0.0 };
public:
    Impedance () = delete;
    Impedance (math::Complex value, Node node_0, Node node_1, id_t id, const std::string& designator) : TwoPoleComponent(node_0, node_1, id, designator), m_value(value) {}
    ~Impedance() = default;

    void set_rectangular (double resistance, double reactance) { m_value = math::Complex {resistance, reactance}; }
    void set_polar (double modulus, double argument) { m_value = math::Complex {std::polar(modulus, argument)}; }

    math::Complex get_impedance () const { return m_value; }
    double get_modulus () const { return std::abs(m_value.get()); }
    double get_argument () const { return std::arg(m_value.get()); }
    double get_resistance () const { return std::real(m_value.get()); }
    double get_reactance () const { return std::imag(m_value.get()); }

    friend std::ostream& operator<<(std::ostream& os, const Impedance& z) {
        os << "[(" << z.get_resistance() << ") + j(" << z.get_reactance() << ")] ohm     / " << z.get_modulus() << "<" << z.get_argument() * 180.0 / std::numbers::pi << "° /";
        return os;
    }

    // U = Z*I -> 1*U - Z*I = 0
    // open    -> 0*U + 1*I = 0
    // short   -> 1*U + 0*I = 0
    math::SymbolicLinearEquation<math::Complex> own () const override {
        const std::string current_var = current();
        const std::string voltage_var = voltage();
        math::SymbolicLinearEquation<math::Complex> equation { get_designator() };
        if (m_open) {
            equation.add_term(current_var, math::Complex { 1.0, 0.0 });
            equation.add_term(voltage_var, math::Complex { 0.0, 0.0 });
        }
        else if (m_short) {
            equation.add_term(current_var, math::Complex { 0.0, 0.0 });
            equation.add_term(voltage_var, math::Complex { 1.0, 0.0 });
        }
        else {
            equation.add_term(current_var, m_value * math::Complex{ -1.0, 0.0 });
            equation.add_term(voltage_var, math::Complex { 1.0, 0.0 });
        }
        equation.set_result(math::Complex { 0.0, 0.0 });
        return equation;
    }

    const math::Frequency& get_frequency () const override {
        throw std::runtime_error("why do you want the frequency of an impedance?");
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
