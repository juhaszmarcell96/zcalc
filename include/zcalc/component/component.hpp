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

#include <vector>
#include <cstdint>
#include <string>

#include <zcalc/math/complex.hpp>
#include <zcalc/math/symbolic_linear_equation.hpp>
#include <zcalc/math/frequency.hpp>
#include <zcalc/graph/graph.hpp>

namespace zcalc {
namespace component {

typedef std::uint32_t Node;
typedef std::uint32_t id_t;

class IComponent {
public:
    virtual ~IComponent() = default;

    virtual void set_frequency (const math::Frequency& frequency) = 0;
    virtual const math::Frequency& get_frequency () const = 0;

    virtual id_t get_id () const = 0;
    virtual const std::string& get_designator () const = 0;
    virtual Node get_gate (std::size_t index) const = 0;

    virtual math::SymbolicLinearEquation<math::Complex> kcl (Node node) const = 0;
    virtual math::SymbolicLinearEquation<math::Complex> kvl (Node node) const = 0;
    virtual math::SymbolicLinearEquation<math::Complex> own () const = 0;

    virtual std::size_t get_num_variables () const = 0;

    virtual bool is_source () const = 0;
    virtual void eliminate () = 0;
    virtual void reactivate () = 0;

    virtual void add_to_graph (graph::Graph<component::IComponent*>& graph) = 0;

    virtual std::string voltage () const = 0;
    virtual std::string current () const = 0;
};

class ComponentBase : public IComponent {
private:
    id_t m_id;
    std::string m_designator;
protected:
    std::vector<Node> m_gates;
public:
    ComponentBase () = delete;
    ComponentBase (id_t id, const std::string& designator) : m_id(id), m_designator(designator) {}
    virtual ~ComponentBase() = default;

    id_t get_id () const override { return m_id; }
    const std::string& get_designator () const override { return m_designator; }

    Node get_gate (std::size_t index) const override {
        return m_gates[index];
    }

    std::string voltage () const override {
        return m_designator + "_u";
    }
    std::string current () const override {
        return m_designator + "_i";
    }
};

} /* namespace component */
} /* namespace zcalc */