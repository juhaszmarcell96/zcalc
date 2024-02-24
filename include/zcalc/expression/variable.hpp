#pragma once

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
    bool is_numeric () override { return m_known; }
    void reduce () override { return; }
    bool is_zero () override {
        if (!m_known) throw std::runtime_error("ERROR : variable value is unknown");
        return std::abs(m_value) < epsilon;
    }
    bool is_one () override {
        if (!m_known) throw std::runtime_error("ERROR : variable value is unknown");
        return ((std::abs(m_value.real() - 1.0)) < epsilon) && (std::abs(m_value.imag()) < epsilon);
    }
    complex get () override{
        if (!m_known) throw std::runtime_error("ERROR : variable value is unknown");
        return m_value;
    }
    std::string to_string() const override { return m_id; }
    void set_value (complex value) {
        m_value = value;
        m_known = true;
    }
    void unset_value () {
        m_value = complex { 0.0, 0.0 };
        m_known = false;
    }
};

} // namespace zcalc