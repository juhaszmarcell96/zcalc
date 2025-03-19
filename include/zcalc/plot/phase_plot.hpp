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

#include <string>
#include <array>

#include "zcalc/plot/bode_plot.hpp"

namespace zcalc {
namespace plot {

/* bode plot supports frequencies between 1Hz and 10 GHz -> 10 decades */
class PhasePlot : public BodePlot {
private:
    struct PhaseName {
        math::Phase phase {};
        std::string name;
    };
    static inline const std::array<PhaseName, 17> phaseNames {
        PhaseName { math::Phase::create_from_radians(-8.0 * std::numbers::pi / 4.0), "-2pi" },
        PhaseName { math::Phase::create_from_radians(-7.0 * std::numbers::pi / 4.0), "-7/4pi" },
        PhaseName { math::Phase::create_from_radians(-6.0 * std::numbers::pi / 4.0), "-3/2pi" },
        PhaseName { math::Phase::create_from_radians(-5.0 * std::numbers::pi / 4.0), "-5/4pi" },
        PhaseName { math::Phase::create_from_radians(-4.0 * std::numbers::pi / 4.0), "-1pi" },
        PhaseName { math::Phase::create_from_radians(-3.0 * std::numbers::pi / 4.0), "-3/4pi" },
        PhaseName { math::Phase::create_from_radians(-2.0 * std::numbers::pi / 4.0), "-1/2pi" },
        PhaseName { math::Phase::create_from_radians(-1.0 * std::numbers::pi / 4.0), "-1/4pi" },
        PhaseName { math::Phase::create_from_radians( 0.0 * std::numbers::pi / 4.0), "0" },
        PhaseName { math::Phase::create_from_radians( 1.0 * std::numbers::pi / 4.0), "1/4pi" },
        PhaseName { math::Phase::create_from_radians( 2.0 * std::numbers::pi / 4.0), "1/2pi" },
        PhaseName { math::Phase::create_from_radians( 3.0 * std::numbers::pi / 4.0), "3/4pi" },
        PhaseName { math::Phase::create_from_radians( 4.0 * std::numbers::pi / 4.0), "1pi" },
        PhaseName { math::Phase::create_from_radians( 5.0 * std::numbers::pi / 4.0), "5/4pi" },
        PhaseName { math::Phase::create_from_radians( 6.0 * std::numbers::pi / 4.0), "3/2pi" },
        PhaseName { math::Phase::create_from_radians( 7.0 * std::numbers::pi / 4.0), "7/4pi" },
        PhaseName { math::Phase::create_from_radians( 8.0 * std::numbers::pi / 4.0), "2pi" }
    };
public:
    PhasePlot () = default;
    ~PhasePlot () = default;

    std::vector<IShape*> get_shapes () override {
        std::vector<IShape*> ret;
        for (auto & shape : m_data) { ret.push_back(&shape); }
        for (auto & shape : m_lines) { ret.push_back(&shape); }
        for (auto & shape : m_texts) { ret.push_back(&shape); }
        // 3dB point is not part of this graph
        return ret;
    }

    void set_3db_points (const std::vector<Point>& points) { m_3db_points = points; }

    void process () {
        if (m_data_points.empty()) { return; }
        clear_decoration();

        // order the vector
        sort();
        for (const auto& data : m_data_points) {
            double phase = data.response.arg();
            if (!m_data.empty()) {
                double diff = phase - m_data.back().y;
                if (diff >= std::numbers::pi) {
                    phase -= 2.0 * std::numbers::pi;
                }
                else if (diff <= -std::numbers::pi) {
                    phase += 2.0 * std::numbers::pi;
                }
            }
            add_point(data.frequency.decade(), phase);
        }

        for (auto& point : m_data) {
            point.decorate(1.0, colors::red, colors::red);
        }

        const auto min_freq = m_data_points.front().frequency;
        const auto max_freq = m_data_points.back().frequency;

        double min_x { 0.0 };
        double max_x { 0.0 };
        double min_y { 0.0 };
        double max_y { 0.0 };
        get_min_max(min_x, min_y, max_x, max_y);
        const double height = max_y - min_y;
        // add the vertical decade lines and text
        auto frequency = min_freq;
        while (frequency < max_freq) {
            const auto decade = frequency.decade();
            m_lines.push_back(Line{decade, min_y, decade, max_y});
            m_lines.back().decorate(1.0, colors::black, colors::black);
            
            for (int i = 1; i < 10; ++i) {
                const double x = (frequency + i * frequency).decade();
                m_lines.push_back(Line{x, min_y, x, max_y});
                m_lines.back().decorate(0.2, colors::black, colors::black);
            }

            frequency *= 10.0;
        }

        // adding horizontal lines
        for (const auto& phaseName : phaseNames) {
            const auto phase = phaseName.phase.as_radians();
            if ((min_y <= phase) && (max_y >= phase)) {
                m_lines.push_back(Line{min_x, phase, max_x, phase});
                m_texts.push_back(Text{min_x, phase, phaseName.name, 12.0});
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