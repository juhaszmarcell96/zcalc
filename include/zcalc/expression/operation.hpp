#pragma once

#include "zcalc/expression/term.hpp"
#include "zcalc/expression/constant.hpp"

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
    bool is_numeric () override {
        if (m_left_operand == nullptr) return false;
        if (m_right_operand == nullptr) return false;
        if (!m_left_operand->is_numeric()) return false;
        if (!m_right_operand->is_numeric()) return false;
        return true;
    }
    void reduce () override {
        if (m_left_operand == nullptr) throw std::runtime_error("ERROR : left operand is null");
        if (m_right_operand == nullptr) throw std::runtime_error("ERROR : right operand is null");

        if (m_left_operand->is_numeric()) {
            m_left_operand = std::make_shared<Constant>(m_left_operand->get());
        }
        else {
            m_left_operand->reduce();
        }
        if (m_right_operand->is_numeric()) {
            m_right_operand = std::make_shared<Constant>(m_right_operand->get());
        }
        else {
            m_right_operand->reduce();
        }
        return;
    }
    bool is_zero () override {
        return std::abs(get()) < epsilon;
    }
    bool is_one () override {
        return ((std::abs(get().real() - 1.0)) < epsilon) && (std::abs(get().imag()) < epsilon);
    }
    complex get () override {
        if (m_left_operand == nullptr) throw std::runtime_error("ERROR : operand cannot be null");
        if (m_right_operand == nullptr) throw std::runtime_error("ERROR : operand cannot be null");
        switch(m_type) {
            case operation_type::add : {
                return m_left_operand->get() + m_right_operand->get();
            }
            case operation_type::sub : {
                return m_left_operand->get() - m_right_operand->get();
            }
            case operation_type::mul : {
                return m_left_operand->get() * m_right_operand->get();
            }
            case operation_type::div : {
                return m_left_operand->get() / m_right_operand->get(); /* TODO -> check if it is 0, math error */
            }
            default : {
                throw std::runtime_error("ERROR : invalid operator type");
            }
        }
    }
    void set_left_operand (std::shared_ptr<Term> operand) {
        m_left_operand = operand;
    }
    void set_right_operand (std::shared_ptr<Term> operand) {
        m_right_operand = operand;
    }
    std::string to_string() const override {
        if (m_left_operand == nullptr) throw std::runtime_error("ERROR : operand cannot be null");
        if (m_right_operand == nullptr) throw std::runtime_error("ERROR : operand cannot be null");
        std::string str = "(";
        str += m_left_operand->to_string();
        switch(m_type) {
            case operation_type::add : {
                str += "+";
                break;
            }
            case operation_type::sub : {
                str += "-";
                break;
            }
            case operation_type::mul : {
                str += "*";
                break;
            }
            case operation_type::div : {
                str += "/";
                break;
            }
            default : {
                throw std::runtime_error("ERROR : invalid operator type");
            }
        }
        str += m_right_operand->to_string();
        str += ")";
        return str;
    }
};

} // namespace zcalc