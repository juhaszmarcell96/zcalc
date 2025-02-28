#pragma once

#include <vector>

#include <zcalc/math/complex.hpp>

namespace zcalc {
namespace component {

typedef std::uint32_t Node;
typedef std::uint32_t id_t;

class IComponent {
public:
    virtual ~IComponent() = default;

    virtual void set_frequency (frequency_t frequency) = 0;
    virtual frequency_t get_frequency () const = 0;

    virtual id_t get_id () const = 0;
    virtual Node get_gate (std::size_t index) const = 0;

    virtual math::Complex kcl (Node node) const = 0;
    virtual math::Complex kvl (Node node) const = 0;
    virtual math::Complex own_i () const = 0;
    virtual math::Complex own_u () const = 0;
    virtual math::Complex own_r () const = 0;

    virtual std::size_t get_num_variables () const = 0;

    virtual bool is_source () const = 0;
    virtual void eliminate () = 0;
    virtual void reactivate () = 0;
};

class ComponentBase : public IComponent {
private:
    id_t m_id;
protected:
    std::vector<Node> m_gates;
public:
    ComponentBase () = delete;
    ComponentBase (id_t id) : m_id(id) {}
    virtual ~ComponentBase() = default;

    id_t get_id () const override { return m_id; }

    Node get_gate (std::size_t index) const override {
        return m_gates[index];
    }
};

} /* namespace component */
} /* namespace zcalc */