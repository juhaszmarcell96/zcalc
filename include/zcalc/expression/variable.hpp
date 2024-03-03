#pragma once

#include <map>
#include <string>

#include "zcalc/expression/term.hpp"

namespace zcalc {

class Variable : public Term {
private:
    std::string m_name;
    complex m_coeff { 1.0, 0.0 };
public:
    Variable() = delete;
    ~Variable() = default;
    Variable (const std::string& name, complex coeff = complex { 1.0, 0.0 });
    term_types get_type () const override;
    bool is_numeric () const override;
    void simplify () override;
    bool is_zero () const override;
    bool is_one () const override;
    complex get_value () const override;
    void set_value (complex value);
    void unset_value ();
    void print (std::ostream &os) const override;
    const std::string& get_name () const;
    complex get_coefficient () const;
    void set_coefficient (complex coeff);

    bool is_constant () const override;
    bool is_variable () const override;
    bool is_operation () const override;
};

} // namespace zcalc