#pragma once

#include <cstdint>
#include <string>

#include "zcalc/plot/html/plot.hpp"

namespace zcalc {
namespace plot {
namespace html {

class Figure {
private:
    HtmlRectangle m_rect;

    Plot* m_plot { nullptr };
    
    std::string m_text;
public:
    Figure () = delete;
    Figure (double x, double y, double w, double h) : m_rect(x, y, w, h, 2.0, colors::black, colors::white) {}
    ~Figure () = default;

    std::size_t get_x () const { return m_rect.get_x(); }
    std::size_t get_y () const { return m_rect.get_y(); }
    std::size_t get_w () const { return m_rect.get_w(); }
    std::size_t get_h () const { return m_rect.get_h(); }

    void set_plot (Plot* plot) {
        m_plot = plot;
    }

    void plot (std::ostream& os) {
        if (!m_plot) { return; }
        double min_x { 0.0 };
        double max_x { 0.0 };
        double min_y { 0.0 };
        double max_y { 0.0 };
        m_plot->get_min_max(min_x, min_y, max_x, max_y);
        // shift everything into the positive region
        const double x_offset = (min_x < 0.0) ? (-min_x) : 0.0;
        const double y_offset = (min_y < 0.0) ? (-min_x) : 0.0;
        m_plot->offset(x_offset, y_offset);
        // scale the plot (only after shifting)
        const double x_scale = m_rect.get_w() / (max_x - min_x);
        const double y_scale = m_rect.get_h() / (max_y - min_y);
        m_plot->scale(x_scale, y_scale);
        // draw
        m_plot->draw(os);
    }
};

} /* namespace html */
} /* namespace plot */
} /* namespace zcalc */