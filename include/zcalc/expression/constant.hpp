#pragma once

#include "zcalc/expression/term.hpp"

#include <cmath>

namespace zcalc {

class Constant : public Term {
private:
    complex m_value { 0.0, 0.0 };
public:
    Constant () = delete;
    ~Constant() = default;
    Constant (complex value) : m_value(value) {}
    bool is_numeric () override { return true; }
    void reduce () override { return; }
    complex get () override { return m_value; }
    bool is_zero () override { return std::abs(m_value) < epsilon; }
    bool is_one () override {
        return ((std::abs(m_value.real() - 1.0)) < epsilon) && (std::abs(m_value.imag()) < epsilon);
    }
    std::string to_string() const override {
        std::string str = "(";
        str += std::to_string(m_value.real());
        str += ",";
        str += std::to_string(m_value.imag());
        str += ")";
        return str;
    }
};

} // namespace zcalc