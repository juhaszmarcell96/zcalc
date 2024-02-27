#pragma once

#include "zcalc/complex.hpp"

#include <complex>
#include <string>
#include <variant>
#include <memory>

namespace zcalc {

class Term {
public:
    virtual bool is_numeric () const = 0;
    virtual complex get () const = 0;
    virtual void reduce () = 0;
    virtual bool is_zero () const = 0;
    virtual bool is_one () const = 0;
    virtual void print (std::ostream &os) const = 0;

    virtual bool is_constant () const = 0;
    virtual bool is_variable () const = 0;
    virtual bool is_operation () const = 0;

    virtual std::unique_ptr<Term> create_copy () const = 0;
};

} // namespace zcalc