#pragma once

#include <cstdint>
#include <vector>
#include <memory>

#include "zcalc/plot/html/shapes.hpp"

namespace zcalc {
namespace plot {
namespace html {

class Plot {
private:
    std::vector<std::shared_ptr<IHtmlShape>> m_shapes;
public:
    Plot () = default;
    ~Plot () = default;

    void add_point (double x, double y, double r = 1.0, double stroke_w = 1.0, colors fill = colors::red, colors stroke = colors::red) {
        m_shapes.push_back(std::static_pointer_cast<IHtmlShape>(std::make_shared<HtmlPoint>(x, y, r, stroke_w, fill, stroke)));
    }

    void add_line (double x0, double y0, double x1, double y1, double stroke_w = 1.0, colors stroke = colors::black) {
        m_shapes.push_back(std::static_pointer_cast<IHtmlShape>(std::make_shared<HtmlLine>(x0, y0, x1, y1, stroke_w, stroke)));
    }

    void add_rectangle (double x, double y, double w, double h, double stroke_w = 1.0, colors stroke = colors::black, colors fill = colors::white) {
        m_shapes.push_back(std::static_pointer_cast<IHtmlShape>(std::make_shared<HtmlRectangle>(x, y, w, h, stroke_w, stroke, fill)));
    }
    
    void add_text (std::string text, double x, double y, std::size_t font_size = 12, colors fill = colors::black) {
        m_shapes.push_back(std::static_pointer_cast<IHtmlShape>(std::make_shared<HtmlText>(x, y, text, font_size, fill)));
    }

    void clear () {
        m_shapes.clear();
    }

    const auto& get () const {
        return m_shapes;
    }

    void offset (double x_offset, double y_offset) {
        for (auto shape : m_shapes) {
            shape->offset(x_offset, y_offset);
        }
    }
    void scale (double scale_x, double scale_y) {
        for (auto shape : m_shapes) {
            shape->scale(scale_x, scale_y);
        }
    }
    // height to translate coordinates to the downward growing svg coordinate systemv
    void translate (double height) {
        for (auto shape : m_shapes) {
            shape->translate(height);
        }
    }

    void get_min_max (double& min_x, double& min_y, double& max_x, double& max_y) {
        if (m_shapes.empty()) { return; }
        min_x = m_shapes[0]->get_min_x();
        max_x = m_shapes[0]->get_max_x();
        min_y = m_shapes[0]->get_min_y();
        max_y = m_shapes[0]->get_max_y();

        for (const auto shape : m_shapes) {
            if (shape->get_min_x() < min_x) { min_x = shape->get_min_x(); }
            if (shape->get_min_y() < min_y) { min_y = shape->get_min_y(); }
            if (shape->get_max_x() > max_x) { max_x = shape->get_max_x(); }
            if (shape->get_max_y() > max_y) { max_y = shape->get_max_y(); }
        }
    }

    void draw (std::ostream& os) {
        for (auto shape : m_shapes) {
            shape->draw(os);
        }
    }
};

} /* namespace html */
} /* namespace plot */
} /* namespace zcalc */