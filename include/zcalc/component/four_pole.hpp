#pragma once

#include <zcalc/component/component.hpp>

namespace zcalc {
namespace component {

class FourPoleComponent : public ComponentBase {
protected:
    bool m_short { false };
    bool m_open { false };
public:
    FourPoleComponent () = delete;
    FourPoleComponent (Node node_0, Node node_1, Node node_2, Node node_3, id_t id) : ComponentBase(id) {
        m_gates.push_back(node_0);
        m_gates.push_back(node_1);
        m_gates.push_back(node_2);
        m_gates.push_back(node_3);
    }
    ~FourPoleComponent() = default;
};

} /* namespace component */
} /* namespace zcalc */
