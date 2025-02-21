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

    id_t get_id () const { return m_id; }

    virtual Complex kcl (Node node) const = 0;
    virtual Complex kvl (Node node) const = 0;
    virtual Complex own_i () const = 0;
    virtual Complex own_u () const = 0;
    virtual Complex own_r () const = 0;

    virtual std::size_t get_num_variables () const = 0;
};

} /* namespace component */
} /* namespace zcalc */