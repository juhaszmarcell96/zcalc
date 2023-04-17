#include <include/resistor.hpp>

namespace zcalc {

Resistor::Resistor(double resistance) {
    m_value = std::complex<double> {resistance, 0};
}

} /* namespace zcalc */