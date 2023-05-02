#include <numbers>

#include <include/inductor.hpp>
#include <include/common.hpp>

namespace zcalc {

Inductor::Inductor(const std::string& designator, double inductance, double frequency) : Impedance(designator, Complex{0.0, 0.0}) {
    m_value = std::polar(2.0 * std::numbers::pi * frequency * inductance, std::numbers::pi / 2.0);
}

} /* namespace zcalc */