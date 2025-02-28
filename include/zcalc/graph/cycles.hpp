#pragma once

#include "zcalc/graph/path.hpp"

#include <vector>
#include <stdexcept>

namespace zcalc {
namespace graph {

template<typename T>
class Cycles {
private:
    std::vector<Path<T>> m_cycles;
public:
    Cycles () = default;
    ~Cycles () = default;

    void clear () { m_cycles.clear(); }

    void push_back (const Path<T>& path) {
        if (!path.is_cycle()) {
            throw std::invalid_argument("cannot push a non-cycle path");
        }
        // don't push the same cycle twice
        bool found = false;
        for (const auto& cycle : m_cycles) {
            if (cycle == path) {
                found = true;
                break;
            }
        }
        if (!found) {
            m_cycles.push_back(path);
        }
    }

    const auto& get_cycles () const { return m_cycles; }

    bool contains (const Path<T>& path) const {
        if (!path.is_cycle()) { return false; }
        for (const auto& cycle : m_cycles) {
            if (path == cycle) { return true; }
        }
        return false;
    }

    friend std::ostream& operator<<(std::ostream& os, const Cycles<T>& c) {
        for (const auto& cycle : c.m_cycles) {
            os << cycle << std::endl;
        }
        return os;
    }
};

} /* namespace graph */
} /* namespace zcalc */