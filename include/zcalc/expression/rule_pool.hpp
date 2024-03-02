#pragma once

#include <zcalc/expression/rule.hpp>

#include <vector>
#include <memory>

namespace zcalc {

class RulePool {
public:
    static const std::vector<std::shared_ptr<Rule>> rules;
};

} // namespace zcalc