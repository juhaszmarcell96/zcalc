/*
 * Copyright (C) 2025 Marcell Juhasz
 *
 * This software is licensed under a non-commercial license.
 * Non-commercial use (personal, academic, research) is allowed for free.
 * Commercial use requires a paid license.
 * Hosting as a service is prohibited without explicit permission.
 *
 * See LICENSE for details or contact marcell.juhasz96@gmail.com.
 */

#pragma once

#include <algorithm>

#include "zcalc/math/complex.hpp"
#include "zcalc/math/frequency.hpp"
#include "zcalc/plot/scatter_plot.hpp"

namespace zcalc {
namespace plot {

struct BodeDataPoint {
    math::Frequency frequency;
    math::Complex response { 0.0, 0.0 };
};

class BodePlot : public ScatterPlot {
protected:
    std::vector<Line> m_lines;
    std::vector<Text> m_texts;
    std::vector<Point> m_3db_points;

    std::vector<BodeDataPoint> m_data_points;
public:
    BodePlot () = default;
    ~BodePlot () = default;

    void add(const math::Frequency& frequency, math::Complex response) {
        m_data_points.push_back(BodeDataPoint{frequency, response});
    }

    void clear_decoration () {
        m_lines.clear();
        m_texts.clear();
    }

    void mark_frequency (const math::Frequency& frequency) {
        double min_x { 0.0 };
        double max_x { 0.0 };
        double min_y { 0.0 };
        double max_y { 0.0 };
        get_min_max(min_x, min_y, max_x, max_y);
        m_lines.push_back(Line{frequency.decade(), min_y, frequency.decade(), max_y});
        m_lines.back().decorate(2.0, colors::green, colors::green);
    }

    void sort () {
        std::sort(m_data_points.begin(), m_data_points.end(), 
            [](const BodeDataPoint& a, const BodeDataPoint& b) {
                return a.frequency < b.frequency;
        });
    }
};

} /* namespace plot */
} /* namespace zcalc */