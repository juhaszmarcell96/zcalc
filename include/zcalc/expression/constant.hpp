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
    bool is_numeric () override;
    complex get () override;
    void reduce () override;
    bool is_zero () override;
    bool is_one () override;
    void print (std::ostream &os) override;
};

} // namespace zcalc