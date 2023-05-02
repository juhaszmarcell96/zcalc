#include <include/resistor.hpp>

namespace zcalc {

Resistor::Resistor(const std::string& designator, double resistance) : Impedance(designator, Complex{0.0, 0.0}) {
    m_value = std::complex<double> {resistance, 0};
}

} /* namespace zcalc */