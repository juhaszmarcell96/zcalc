#pragma once

#include <map>
#include <string>

#include "zcalc/expression/term.hpp"

namespace zcalc {

class Variable : public Term {
private:
    std::string m_id;
    bool m_known { false };
    complex m_value { 0.0, 0.0 };
public:
    Variable() = delete;
    ~Variable() = default;
    Variable (const std::string& id) : m_id(id) {}
    bool is_numeric () const override;
    void reduce () override;
    bool is_zero () const override;
    bool is_one () const override;
    complex get () const override;
    void set_value (complex value);
    void unset_value ();
    void print (std::ostream &os) const override;

    bool is_constant () const override;
    bool is_variable () const override;
    bool is_operation () const override;
};

} // namespace zcalc