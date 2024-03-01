#pragma once

#include <zcalc/expression/operation.hpp>

#include <tuple>

namespace zcalc {

class Rule {
public:
    virtual bool simplify (Operation* operation) const = 0;
};

class DistributiveRule : public Rule {
public:
    bool simplify (Operation* operation) const override;
};

} // namespace zcalc