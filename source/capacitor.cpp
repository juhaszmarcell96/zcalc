#include <numbers>

#include <include/capacitor.hpp>
#include <include/common.hpp>

namespace zcalc {

Capacitor::Capacitor(double capacitance, double frequency) {
    m_value = std::polar(1.0 / (2.0 * std::numbers::pi * frequency * capacitance), -std::numbers::pi / 2.0);
}

} /* namespace zcalc */