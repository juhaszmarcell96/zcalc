#pragma once

#include "zcalc/complex.hpp"

#include <complex>
#include <string>
#include <variant>

namespace zcalc {

class Term {
public:
    virtual bool is_numeric () = 0;
    virtual complex get () = 0;
    virtual void reduce () = 0;
    virtual bool is_zero () = 0;
    virtual bool is_one () = 0;
    virtual void print (std::ostream &os) = 0;
};

} // namespace zcalc