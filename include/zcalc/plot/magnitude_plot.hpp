#pragma once

#include <cmath>

#include "zcalc/plot/scatter_plot.hpp"

namespace zcalc {
namespace plot {

/* bode plot supports frequencies between 1Hz and 10 GHz -> 10 decades */
class MagnitudePlot : public ScatterPlot {
private:
    double m_min_freq { 1.0 };
    double m_max_freq { 1e10 };

    std::vector<Line> m_lines;
    std::vector<Text> m_texts;
    std::vector<Point> m_3db_points;
public:
    MagnitudePlot () = delete;
    MagnitudePlot (double min_freq = 1.0, double max_freq = 1e10) : m_min_freq(min_freq), m_max_freq(max_freq) {}
    ~MagnitudePlot () = default;

    std::vector<IShape*> get_shapes () override {
        std::vector<IShape*> ret;
        for (auto & shape : m_data) { ret.push_back(&shape); }
        for (auto & shape : m_lines) { ret.push_back(&shape); }
        for (auto & shape : m_texts) { ret.push_back(&shape); }
        for (auto & shape : m_3db_points) { ret.push_back(&shape); }
        return ret;
    }

    std::size_t get_num_decades () const {
        return std::log10(m_max_freq) - std::log10(m_min_freq);
    }

    const auto& get_3db_points () const { return m_3db_points; }

    void process () {
        m_lines.clear();
        m_texts.clear();
        m_3db_points.clear();

        for (auto& point : m_data) {
            point.decorate (1.0, colors::red, colors::red);
        }

        double min_x { 0.0 };
        double max_x { 0.0 };
        double min_y { 0.0 };
        double max_y { 0.0 };
        get_min_max(min_x, min_y, max_x, max_y);
        const double height = max_y - min_y;
        // add the vertical decade lines and text
        double frequency = m_min_freq;
        while (frequency < m_max_freq) {
            m_lines.push_back(Line{std::log10(frequency), min_y, std::log10(frequency), max_y});
            m_lines.back().decorate(1.0, colors::black, colors::black);
            m_texts.push_back(Text{std::log10(frequency), min_y + (height / 2.0), "10^" + std::to_string((int)std::log10(frequency)) + "Hz", 0.1});
            
            for (int i = 1; i < 10; ++i) {
                const double x = std::log10(frequency + i * frequency);
                m_lines.push_back(Line{x, min_y, x, max_y});
                m_lines.back().decorate(0.2, colors::black, colors::black);
            }

            frequency *= 10.0;
        }
        // add horizontal 20dB lines and texts
        int y_tmp = std::ceil(min_y);
        while (y_tmp < max_y) {
            if (y_tmp % 20 == 0) {
                m_lines.push_back(Line{min_x, static_cast<double>(y_tmp), max_x, static_cast<double>(y_tmp)});
                m_texts.push_back(Text{min_x, static_cast<double>(y_tmp), std::to_string(y_tmp) + "dB", 0.1});
                y_tmp += 20;
            }
            else {
                ++y_tmp;
            }
        }

        // perform calculations for the -3dB point
        if (min_y < -3.0 && max_y > -3.0) {
            m_lines.push_back(Line{min_x, -3.0, max_x, -3.0});
            m_lines.back().decorate(1.0, colors::blue, colors::blue);
        }
        for (std::size_t index = 1; index < m_data.size(); ++index) {
            const auto& curr = m_data[index];
            const auto& prev = m_data[index - 1];
            if ((curr.y > -3.0 && prev.y < -3.0) || (curr.y < -3.0 && prev.y > -3.0)) {
                /* interpolate with a straight line */
                double slope = (curr.y - prev.y) / (curr.x - prev.x);
                double y_dist = curr.y - (-3.0);
                double x_dist = y_dist / slope;
                m_lines.push_back(Line{curr.x - x_dist, min_y, curr.x - x_dist, max_y});
                m_lines.back().decorate(1.0, colors::blue, colors::blue);
                m_3db_points.push_back(Point{curr.x - x_dist, -3.0});
                m_3db_points.back().decorate(2.0, colors::blue, colors::blue);
            }
        }
    }
};

} /* namespace plot */
} /* namespace zcalc */