#pragma once

#include <vector>
#include <string>
#include <memory>

#include <zcalc/internal/gate.hpp>
#include <zcalc/internal/linear_equation.hpp>
#include <zcalc/internal/loop_message.hpp>

namespace zcalc {

class Component {
private:
    std::size_t m_id;
protected:
    std::vector<std::unique_ptr<Gate>> m_gates;
    std::string m_designator;
public:
    Component () = delete;
    Component (const std::string& designator, std::size_t id) : m_designator(designator), m_id(id) {}
    virtual ~Component() = default;

    const std::string& get_designator () const { return m_designator; }
    std::size_t get_id () const { return m_id; }

    virtual std::size_t get_num_variables () const = 0;
    virtual void kcl(const Node* node, LinearEquation<Complex>& equ) const = 0;
    virtual void own_equ(LinearEquation<Complex>& equ) const = 0;

    virtual void propagate (LoopMessage message, const Gate* gate) const = 0;
};

} /* namespace zcalc */