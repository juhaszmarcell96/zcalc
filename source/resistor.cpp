#include <include/resistor.hpp>

namespace zcalc {

Resistor::Resistor(double resistance) {
    m_modulus = resistance;
    m_argument = 0;
}

} /* namespace zcalc */