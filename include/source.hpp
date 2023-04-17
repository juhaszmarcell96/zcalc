#pragma once

#include <string>
#include <iostream>
#include <complex>

namespace zcalc {

class Source {
protected:
    std::complex<double> m_voltage;
public:
    Source () = default;
    Source(std::complex<double> voltage);
    ~Source() = default;

    std::complex<double> get_voltage () const;
};

} /* namespace zcalc */