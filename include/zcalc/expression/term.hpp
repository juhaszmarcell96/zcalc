#pragma once

#include "zcalc/complex.hpp"
#include "zcalc/expression/variable_pool.hpp"

#include <complex>
#include <string>
#include <variant>
#include <memory>
#include <concepts>
#include <iomanip>

namespace zcalc {

template<bool flag = false> void static_no_match() { static_assert(flag, "no match"); }

enum class term_types
{
    constant,
    variable,
    oper_add,
    oper_sub,
    oper_mul,
    oper_div
};

template <term_types type>
concept is_constant_type = (type == term_types::constant);

template <term_types type>
concept is_variable_type = (type == term_types::variable);

template <term_types type>
concept is_operation_type = ((type == term_types::oper_add) ||
                             (type == term_types::oper_sub) ||
                             (type == term_types::oper_mul) ||
                             (type == term_types::oper_div));

template <term_types type>
concept is_valid_term_type = (is_constant_type<type> ||
                              is_variable_type<type> ||
                              is_operation_type<type>);

template <term_types type>
requires (is_valid_term_type<type>)
class Termasd {
private:
    // constant
    complex m_value { 0.0, 0.0 };
    // variable
    std::string m_name;
    complex m_coeff { 1.0, 0.0 };
    // operation
    std::vector<std::shared_ptr<Termasd>> m_operands;
public:
    term_types get_type () const { return type; }
    bool is_numeric () const
    {
        if constexpr (is_constant_type<type>)
        {
            return true;
        }
        else if constexpr (is_variable_type<type>)
        {
            return VariablePool::is_known(m_name);
        }
        else if constexpr (is_operation_type<type>)
        {
            // TODO
        }
        else
        {
            static_no_match();
        }
    }
    complex get_value () const
    {
        if constexpr (is_constant_type<type>)
        {
            return m_value;
        }
        else if constexpr (is_variable_type<type>)
        {
            return VariablePool::get_value(m_name);
        }
        else if constexpr (is_operation_type<type>)
        {
            // TODO
        }
        else
        {
            static_no_match();
        }
    }
    void simplify ()
    {
        if constexpr (is_constant_type<type>)
        {
            return;
        }
        else if constexpr (is_variable_type<type>)
        {
            return;
        }
        else if constexpr (is_operation_type<type>)
        {
            // TODO
        }
        else
        {
            static_no_match();
        }
    }
    bool is_zero () const
    {
        if constexpr (is_constant_type<type>)
        {
            return std::abs(m_value) < epsilon;
        }
        else if constexpr (is_variable_type<type>)
        {
            return std::abs(VariablePool::get_value(m_name)) < epsilon;
        }
        else if constexpr (is_operation_type<type>)
        {
            // TODO
        }
        else
        {
            static_no_match();
        }
    }
    bool is_one () const
    {
        if constexpr (is_constant_type<type>)
        {
            return ((std::abs(m_value.real() - 1.0)) < epsilon) && (std::abs(m_value.imag()) < epsilon);
        }
        else if constexpr (is_variable_type<type>)
        {
            complex value = VariablePool::get_value(m_name);
            return ((std::abs(value.real() - 1.0)) < epsilon) && (std::abs(value.imag()) < epsilon);
        }
        else if constexpr (is_operation_type<type>)
        {
            // TODO
        }
        else
        {
            static_no_match();
        }
    }
    void print (std::ostream &os) const
    {
        if constexpr (is_constant_type<type>)
        {
            if (std::abs(m_value.imag()) < epsilon) {
                os << std::setprecision(4) << m_value.real();
            }
            else {
                os << "(" << std::setprecision(4) << m_value.real();
                if (m_value.imag() < 0.0) {
                    os << "-" << (m_value.imag() * (-1.0));
                }
                else {
                    os << "+" << m_value.imag();
                }
                os  << "j)";
            }
        }
        else if constexpr (is_variable_type<type>)
        {
            if (std::abs(m_coeff.imag()) < epsilon) {
                if (!((std::abs(m_coeff.real() - 1.0)) < epsilon)) {
                    os << std::setprecision(4) << m_coeff.real();
                }
            }
            else {
                os << "(" << std::setprecision(4) << m_coeff.real();
                if (m_coeff.imag() < 0.0) {
                    os << "-" << (m_coeff.imag() * (-1.0));
                }
                else {
                    os << "+" << m_coeff.imag();
                }
                os  << "j)";
            }
            //os << "(" << std::setprecision(4) << m_coeff.real() << "," << m_coeff.imag() << ")";
            os << m_name;
        }
        else if constexpr (is_operation_type<type>)
        {
            // TODO
        }
        else
        {
            static_no_match();
        }
    }

    bool is_constant () const
    {
        if constexpr (is_constant_type<type>)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    bool is_variable () const
    {
        if constexpr (type == term_types::variable)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    bool is_operation () const
    {
        if constexpr (type == term_types::operation)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
};

class Term {
public:
    virtual term_types get_type () const = 0;
    virtual bool is_numeric () const = 0;
    virtual complex get_value () const = 0;
    virtual void simplify () = 0;
    virtual bool is_zero () const = 0;
    virtual bool is_one () const = 0;
    virtual void print (std::ostream &os) const = 0;

    virtual bool is_constant () const = 0;
    virtual bool is_variable () const = 0;
    virtual bool is_operation () const = 0;
};

} // namespace zcalc