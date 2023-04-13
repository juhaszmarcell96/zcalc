#include <include/capacitor.hpp>
#include <include/common.hpp>

namespace zcalc {

Capacitor::Capacitor(double capacitance, double frequency) {
    m_modulus = 1.0 / (2*pi*frequency*capacitance);
    m_argument = -pi / 2.0;
}

} /* namespace zcalc */