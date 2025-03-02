#pragma once

#include <vector>

#include "zcalc/plot/plot.hpp"

namespace zcalc {
namespace plot {

class ScatterPlot : public IPlot {
protected:
    std::vector<Point> m_data {};
public:
    ScatterPlot () = default;
    ~ScatterPlot () = default;

    const auto& get_data () const { return m_data; }

    void add_point (double x, double y) {
        m_data.push_back(Point{x, y});
    }

    void get_min_max (double& min_x, double& min_y, double& max_x, double& max_y) const override {
        if (m_data.empty()) { return; }
        min_x = m_data[0].get_min_x();
        max_x = m_data[0].get_max_x();
        min_y = m_data[0].get_min_y();
        max_y = m_data[0].get_max_y();

        for (const auto& shape : m_data) {
            if (shape.get_min_x() < min_x) { min_x = shape.get_min_x(); }
            if (shape.get_min_y() < min_y) { min_y = shape.get_min_y(); }
            if (shape.get_max_x() > max_x) { max_x = shape.get_max_x(); }
            if (shape.get_max_y() > max_y) { max_y = shape.get_max_y(); }
        }
    }
};

} /* namespace plot */
} /* namespace zcalc */