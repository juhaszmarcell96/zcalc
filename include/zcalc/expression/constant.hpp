#pragma once

#include "zcalc/expression/term.hpp"

#include <ostream>

namespace zcalc {

class Constant : public Term {
private:
    complex m_value { 0.0, 0.0 };
public:
    Constant () = default;
    ~Constant () = default;
    Constant (complex value);
    bool is_numeric () const override;
    complex get () const override;
    void reduce () override;
    bool is_zero () const override;
    bool is_one () const override;
    void print (std::ostream &os) const override;

    bool is_constant () const override;
    bool is_variable () const override;
    bool is_operation () const override;

    std::unique_ptr<Term> create_copy () const override;
};

} // namespace zcalc