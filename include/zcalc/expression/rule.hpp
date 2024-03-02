#pragma once

#include <zcalc/expression/term.hpp>

#include <memory>

namespace zcalc {

class Rule {
public:
    // return true if the rule was applied to the term, false otherwise
    virtual bool apply (std::shared_ptr<Term>& term) const = 0;
};

class ConstantRule : public Rule {
public:
    bool apply (std::shared_ptr<Term>& term) const override;
};

class OneRule : public Rule {
public:
    bool apply (std::shared_ptr<Term>& term) const override;
};

/*

class ZeroRule : public Rule {
public:
    bool apply (Operation* operation) const override;
};

class DistributiveRule : public Rule {
public:
    bool apply (Operation* operation) const override;
};

class AssociativeRule : public Rule {
public:
    bool apply (Operation* operation) const override;
};

*/

} // namespace zcalc