#pragma once

#include "zcalc/complex.hpp"

#include <complex>
#include <string>

namespace zcalc {

enum class term_types {
    constant,
    variable,
    operation
};

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