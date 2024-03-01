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
    static std::shared_ptr<Term> create (const std::string& var_name);
    static std::shared_ptr<Term> create (complex value);
    static std::shared_ptr<Term> create (operation_types type, std::shared_ptr<Term> lhs, std::shared_ptr<Term> rhs);
};

} // namespace zcalc