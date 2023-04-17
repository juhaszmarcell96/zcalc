#include <include/common.hpp>
#include <include/source.hpp>

#include <cmath>
#include <numbers>

namespace zcalc {

Source::Source(std::complex<double> voltage) : m_voltage(voltage) {}

std::complex<double> Source::get_voltage () const { return m_voltage; }

} /* namespace zcalc */