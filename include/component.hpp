#pragma once

#include <memory>
#include <string>

#include <include/node.hpp>
#include <include/complex.hpp>

namespace zcalc {

class Component {
protected:
    node_ptr_t m_node_0;
    node_ptr_t m_node_1;

    std::string m_designator;
public:
    Component () = default;
    Component (const std::string& designator);
    virtual ~Component() = default;

    void set_node_0 (node_ptr_t node);
    void set_node_1 (node_ptr_t node);
    node_ptr_t get_node_0 ();
    node_ptr_t get_node_1 ();

    const std::string& get_designator () const;

    virtual Complex get_i_coeff(const Node* node) const = 0;
    virtual Complex get_u_coeff(const Node* node_0, const Node* node_1) const = 0;
    virtual Complex get_own_i_coeff() const = 0;
    virtual Complex get_own_u_coeff() const = 0;
    virtual Complex get_own_result() const = 0;

    bool visited = false;
};

} /* namespace zcalc */