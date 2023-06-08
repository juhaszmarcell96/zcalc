#pragma once

#include <memory>
#include <string>

#include <zcalc/node.hpp>
#include <zcalc/complex.hpp>

namespace zcalc {

class Component {
protected:
    node_ptr_t m_node_0;
    node_ptr_t m_node_1;

    std::string m_designator;
public:
    Component () = default;
    Component (const std::string& designator) : m_designator(designator) {}
    virtual ~Component() = default;

    void set_node_0 (node_ptr_t node) { m_node_0 = node; }
    void set_node_1 (node_ptr_t node) { m_node_1 = node; }
    node_ptr_t get_node_0 () { return m_node_0; }
    node_ptr_t get_node_1 () { return m_node_1; }

    const std::string& get_designator () const { return m_designator; }

    virtual Complex get_i_coeff(const Node* node) const = 0;
    virtual Complex get_u_coeff(const Node* node_0, const Node* node_1) const = 0;
    virtual Complex get_own_i_coeff() const = 0;
    virtual Complex get_own_u_coeff() const = 0;
    virtual Complex get_own_result() const = 0;

    bool visited = false;
};

} /* namespace zcalc */