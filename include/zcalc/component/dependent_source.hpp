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

#include <zcalc/component/two_pole.hpp>

namespace zcalc {
namespace component {

class DependentSource : public TwoPoleComponent {
protected:
    const IComponent* m_dependency { nullptr };
public:
    DependentSource () = delete;
    DependentSource (Node node_0, Node node_1, std::size_t id, const std::string& designator, const IComponent* dependency)
        : TwoPoleComponent(node_0, node_1, id, designator), m_dependency(dependency) {}

    const math::Frequency& get_frequency () const override {
        throw std::runtime_error("why do you want the frequency of a dependent source?");
    }

    void set_frequency (const math::Frequency& frequency) override {}

    bool is_source () const override { return false; } // not really a source

    void eliminate () override {
        throw std::runtime_error("cannot eliminate a dependent source");
    }

    void reactivate () override {
        throw std::runtime_error("cannot reactivate a dependent source");
    }
};

} /* namespace component */
} /* namespace zcalc */