#include <include/component.hpp>

namespace zcalc {

Component::Component (const std::string& designator) : m_designator(designator) {}

void Component::set_node_0 (node_ptr_t node) { m_node_0 = node; }
void Component::set_node_1 (node_ptr_t node) { m_node_1 = node; }
node_ptr_t Component::get_node_0 () { return m_node_0; }
node_ptr_t Component::get_node_1 () { return m_node_1; }

const std::string& Component::get_designator () const { return m_designator; }

} /* namespace zcalc */