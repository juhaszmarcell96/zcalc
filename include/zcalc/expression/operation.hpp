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
    bool is_numeric () override;
    void reduce () override;
    bool is_zero () override;
    bool is_one () override;
    complex get () override;
    void print (std::ostream &os) override;
    void set_left_operand (std::shared_ptr<Term> operand);
    void set_right_operand (std::shared_ptr<Term> operand);
};

} // namespace zcalc