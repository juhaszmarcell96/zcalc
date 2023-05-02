#include <include/common.hpp>
#include <include/source.hpp>

#include <cmath>
#include <numbers>

namespace zcalc {

Source::Source(const std::string& designator, Complex voltage) : Component(designator), m_voltage(voltage) {}

Complex Source::get_i_coeff(const Node* node) const {
    /* current direction is assumed to be from node_0 to node_1 */
    if (m_node_0.get() == node) return Complex { -1.0, 0.0 };
    else if (m_node_1.get() == node) return Complex { 1.0, 0.0 };
    else return Complex { 0.0, 0.0 };
}

Complex Source::get_u_coeff(const Node* node_0, const Node* node_1) const {
    if ((m_node_0.get() == node_0) && (m_node_1.get() == node_1)) return m_voltage;
    else if ((m_node_0.get() == node_1) && (m_node_1.get() == node_0)) return m_voltage * -1;
    else return Complex { 0.0, 0.0 };
}

Complex Source::get_own_i_coeff() const {
    return Complex {0.0, 0.0};
}

Complex Source::get_own_u_coeff() const {
    return Complex { 1.0, 0.0 };
}

Complex Source::get_own_result() const {
    return m_voltage;
}

} /* namespace zcalc */