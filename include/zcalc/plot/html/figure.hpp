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

#include <cstdint>
#include <string>

#include "zcalc/plot/plot.hpp"
#include "zcalc/plot/html/html_drawer.hpp"

namespace zcalc {
namespace plot {
namespace html {

class Figure {
private:
    Rectangle m_rect;

    IPlot* m_plot { nullptr };
    
    std::string m_text;
public:
    Figure () = delete;
    Figure (double x, double y, double w, double h) : m_rect(x, y, w, h) {
        m_rect.decorate(2.0, colors::black, colors::light_grey);
    }
    ~Figure () = default;

    std::size_t get_x () const { return m_rect.p.x; }
    std::size_t get_y () const { return m_rect.p.y; }
    std::size_t get_w () const { return m_rect.w; }
    std::size_t get_h () const { return m_rect.h; }

    void set_plot (IPlot* plot) {
        m_plot = plot;
    }

    void fit () {
        if (!m_plot) { return; }
        double min_x { 0.0 };
        double max_x { 0.0 };
        double min_y { 0.0 };
        double max_y { 0.0 };
        m_plot->get_min_max(min_x, min_y, max_x, max_y);
        // push everything to positive
        const double x_offset = 0.0 - min_x;
        const double y_offset = 0.0 - min_y;
        for (auto shape : m_plot->get_shapes()) {
            shape->offset(x_offset, y_offset);
        }
        // scale the plot
        const double x_scale = m_rect.w / (max_x - min_x);
        const double y_scale = m_rect.h / (max_y - min_y);
        for (auto shape : m_plot->get_shapes()) {
            shape->scale(x_scale, y_scale);
        }
        // translate
        for (auto shape : m_plot->get_shapes()) {
            shape->translate(m_rect.h);
        }
        // offset
        for (auto shape : m_plot->get_shapes()) {
            shape->offset(m_rect.p.x, m_rect.p.y);
        }
    }

    void plot (std::ostream& os) const {
        HtmlDrawer drawer;
        drawer.draw(&m_rect, os);
        for (const auto shape : m_plot->get_shapes()) {
            drawer.draw(shape, os);
        }
    }
};

} /* namespace html */
} /* namespace plot */
} /* namespace zcalc */