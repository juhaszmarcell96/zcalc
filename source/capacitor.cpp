#include <numbers>

#include <include/capacitor.hpp>
#include <include/common.hpp>

namespace zcalc {

Capacitor::Capacitor(const std::string& designator, double capacitance, double frequency) : Impedance(designator, Complex{0.0, 0.0}) {
    m_value = std::polar(1.0 / (2.0 * std::numbers::pi * frequency * capacitance), -std::numbers::pi / 2.0);
}

} /* namespace zcalc */