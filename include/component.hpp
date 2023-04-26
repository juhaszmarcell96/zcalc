#pragma once

#include <memory>

#include <include/node.hpp>
#include <include/complex.hpp>

namespace zcalc {

typedef std::shared_ptr<Node> node_ptr_t;

class Component {
protected:
    node_ptr_t m_node_0;
    node_ptr_t m_node_1;
public:
    Component () = default;
    virtual ~Component() = default;

    void set_node_0 (node_ptr_t node);
    void set_node_1 (node_ptr_t node);
    node_ptr_t get_node_0 ();
    node_ptr_t get_node_1 ();

    virtual Complex get_i_coeff(const node_ptr_t node) const = 0;
    virtual Complex get_u_coeff(const node_ptr_t node_0, const node_ptr_t node_1) const = 0;
};

} /* namespace zcalc */