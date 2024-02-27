#pragma once

#include "zcalc/expression/term.hpp"
#include "zcalc/expression/operation.hpp"
#include "zcalc/expression/variable.hpp"

#include <memory>
#include <string>
#include <map>

namespace zcalc {

class TermFactory {
public:
    static std::unique_ptr<Term> create (const std::string& var_name);
    static std::unique_ptr<Term> create (complex value);
    static std::unique_ptr<Term> create (operation_type type, std::unique_ptr<Term>&& lhs, std::unique_ptr<Term>&& rhs);
};

} // namespace zcalc