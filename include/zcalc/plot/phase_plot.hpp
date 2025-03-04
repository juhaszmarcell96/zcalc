#pragma once

#include <cmath>

#include "zcalc/plot/scatter_plot.hpp"

namespace zcalc {
namespace plot {

/* bode plot supports frequencies between 1Hz and 10 GHz -> 10 decades */
class PhasePlot : public ScatterPlot {
private:
    double m_min_freq { 1.0 };
    double m_max_freq { 1e10 };

    std::vector<Line> m_lines;
    std::vector<Text> m_texts;
    std::vector<Point> m_3db_points;
public:
    PhasePlot () = delete;
    PhasePlot (double min_freq = 1.0, double max_freq = 1e10) : m_min_freq(min_freq), m_max_freq(max_freq) {}
    ~PhasePlot () = default;

    std::size_t get_num_decades () const {
        return std::log10(m_max_freq) - std::log10(m_min_freq);
    }

    std::vector<IShape*> get_shapes () override {
        std::vector<IShape*> ret;
        for (auto & shape : m_data) { ret.push_back(&shape); }
        for (auto & shape : m_lines) { ret.push_back(&shape); }
        for (auto & shape : m_texts) { ret.push_back(&shape); }
        return ret;
    }

    void set_3db_points (const std::vector<Point>& points) { m_3db_points = points; }

    void mark_frequency (double frequency) {
        double min_x { 0.0 };
        double max_x { 0.0 };
        double min_y { 0.0 };
        double max_y { 0.0 };
        get_min_max(min_x, min_y, max_x, max_y);
        m_lines.push_back(Line{std::log10(frequency), min_y, std::log10(frequency), max_y});
        m_lines.back().decorate(2.0, colors::green, colors::green);
    }

    void process () {
        m_lines.clear();
        m_texts.clear();

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
            
            for (int i = 1; i < 10; ++i) {
                const double x = std::log10(frequency + i * frequency);
                m_lines.push_back(Line{x, min_y, x, max_y});
                m_lines.back().decorate(0.2, colors::black, colors::black);
            }

            frequency *= 10.0;
        }
        // add horizontal 15 degree (°) lines and texts
        int y_tmp = std::ceil(min_y);
        while (y_tmp < max_y) {
            if (y_tmp % 15 == 0) {
                m_lines.push_back(Line{min_x, static_cast<double>(y_tmp), max_x, static_cast<double>(y_tmp)});
                m_texts.push_back(Text{min_x, static_cast<double>(y_tmp), std::to_string(y_tmp - 180) + "°", 0.1});
                y_tmp += 15;
            }
            else {
                ++y_tmp;
            }
        }

        // perform calculations for the -3dB point
        for (const auto& point : m_3db_points) {
            m_lines.push_back(Line{point.x, min_y, point.x, max_y});
            m_lines.back().decorate(1.0, colors::blue, colors::blue);
        }
    }
};

} /* namespace plot */
} /* namespace zcalc */