#pragma once

#include <include/component.hpp>
#include <include/complex.hpp>

#include <string>
#include <iostream>

namespace zcalc {

class Source : public Component {
protected:
    Complex m_voltage;
public:
    Source () = default;
    Source(const std::string& designator, Complex voltage);
    ~Source() = default;

    Complex get_i_coeff(const Node* node) const override;
    Complex get_u_coeff(const Node* node_0, const Node* node_1) const override;
    Complex get_own_i_coeff() const override;
    Complex get_own_u_coeff() const override;
    Complex get_own_result() const override;
};

} /* namespace zcalc */