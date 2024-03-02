#include <zcalc/expression/rule_pool.hpp>

#include <vector>

namespace zcalc {

const std::vector<std::shared_ptr<Rule>> RulePool::rules {
    std::make_shared<ConstantRule>(),
    std::make_shared<OneRule>(),
    std::make_shared<ZeroRule>()
};

} // namespace zcalc