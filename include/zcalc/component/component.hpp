#pragma once

#include <vector>
#include <string>
#include <memory>

#include <zcalc/math/complex.hpp>

namespace zcalc {
namespace component {

typedef std::uint32_t Node;
typedef std::uint32_t id_t;

class Component {
private:
    id_t m_id;
protected:
    std::vector<Node> m_gates;
public:
    Component () = delete;
    Component (id_t id) : m_id(id) {}
    virtual ~Component() = default;

    virtual void set_frequency (frequency_t frequency) = 0;
    virtual frequency_t get_frequency () const = 0;

    id_t get_id () const { return m_id; }

    Node get_gate (std::size_t index) const {
        return m_gates[index];
    }

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

} /* namespace component */
} /* namespace zcalc */