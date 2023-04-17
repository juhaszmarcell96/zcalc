#include <include/inductor.hpp>
#include <include/common.hpp>

namespace zcalc {

Inductor::Inductor(double inductance, double frequency) {
    m_value = std::polar(2.0 * std::numbers::pi * frequency * inductance, std::numbers::pi / 2.0);
}

} /* namespace zcalc */