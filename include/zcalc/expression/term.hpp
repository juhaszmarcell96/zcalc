#pragma once

#include "zcalc/complex.hpp"

#include <complex>
#include <string>
#include <variant>
#include <memory>

namespace zcalc {

enum class term_types {
    constant,
    variable,
    operation
};

class Term {
public:
    virtual term_types get_type () const = 0;
    virtual bool is_numeric () const = 0;
    virtual complex get_value () const = 0;
    virtual void simplify () = 0;
    virtual bool is_zero () const = 0;
    virtual bool is_one () const = 0;
    virtual void print (std::ostream &os) const = 0;

    virtual bool is_constant () const = 0;
    virtual bool is_variable () const = 0;
    virtual bool is_operation () const = 0;
};

} // namespace zcalc