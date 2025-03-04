#pragma once

#include <algorithm>

#include "zcalc/math/complex.hpp"
#include "zcalc/plot/scatter_plot.hpp"

namespace zcalc {
namespace plot {

struct BodeDataPoint {
    double frequency { 0.0 };
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

    void add(double frequency, math::Complex response) {
        m_data_points.push_back(BodeDataPoint{frequency, response});
    }

    void clear_decoration () {
        m_lines.clear();
        m_texts.clear();
    }

    void mark_frequency (double frequency) {
        double min_x { 0.0 };
        double max_x { 0.0 };
        double min_y { 0.0 };
        double max_y { 0.0 };
        get_min_max(min_x, min_y, max_x, max_y);
        m_lines.push_back(Line{std::log10(frequency), min_y, std::log10(frequency), max_y});
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