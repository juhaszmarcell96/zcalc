#pragma once

#include "zcalc/expression/term.hpp"

#include <memory>

namespace zcalc {

enum class operation_type {
    add,
    sub,
    mul,
    div
};

class Operation : public Term {
private:
    std::shared_ptr<Term> m_left_operand { nullptr };
    std::shared_ptr<Term> m_right_operand { nullptr };

    operation_type m_type;
public:
    Operation () = delete;
    Operation (operation_type type) : m_type (type) {}
    ~Operation () = default;
    bool is_numeric () const override;
    void reduce () override;
    bool is_zero () const override;
    bool is_one () const override;
    complex get () const override;
    void print (std::ostream &os) const override;
    void set_left_operand (std::shared_ptr<Term> operand);
    //const std::shared_ptr<const Term> get_left_operand () const;
    std::shared_ptr<Term> get_left_operand ();
    void set_right_operand (std::shared_ptr<Term> operand);
    //const std::shared_ptr<const Term> get_right_operand () const;
    std::shared_ptr<Term> get_right_operand ();
    operation_type get_type () const;

    bool is_constant () const override;
    bool is_variable () const override;
    bool is_operation () const override;
};

} // namespace zcalc