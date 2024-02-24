#pragma once

#include <complex>
#include <string>

namespace zcalc {

typedef std::complex<double> complex;
constexpr double epsilon = 1.0e-10;

class Term {
public:
    virtual ~Term() {};

    virtual bool is_numeric () = 0;
    virtual void reduce () = 0;
    virtual complex get () = 0;
    virtual bool is_zero () = 0;
    virtual bool is_one () = 0;
    virtual std::string to_string() const = 0;
};

} // namespace zcalc