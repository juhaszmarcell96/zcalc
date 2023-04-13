#include <include/inductor.hpp>
#include <include/common.hpp>

namespace zcalc {

Inductor::Inductor(double inductance, double frequency) {
    m_modulus = 2*pi*frequency*inductance;
    m_argument = pi / 2.0;
}

} /* namespace zcalc */