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

#include "zcalc/plot/shapes.hpp"
#include "zcalc/plot/html/colors.hpp"

#include <ostream>

namespace zcalc {
namespace plot {
namespace html {

class HtmlDrawer {
public:
    void draw (const IShape* shape, std::ostream& os) const {
        if (const Point* p = dynamic_cast<const Point*>(shape)) {
            os << "<circle ";
            os << "cx=\"" << p->x << "\" ";
            os << "cy=\"" << p->y << "\" ";
            os << "r=\"" << p->stroke_width << "\" ";
            os << "stroke=\"" << color_to_hex(p->stroke_color) << "\" ";
            os << "fill=\"" << color_to_hex(p->fill_color) << "\" ";
            os << "stroke-width=\"" << p->stroke_width << "\"/>" << std::endl;
        }
        else if (const Line* l = dynamic_cast<const Line*>(shape)) {
            os << "<line ";
            os << "x1=\"" << l->p0.x << "\" ";
            os << "y1=\"" << l->p0.y << "\" ";
            os << "x2=\"" << l->p1.x << "\" ";
            os << "y2=\"" << l->p1.y << "\" ";
            os << "stroke=\"" << color_to_hex(l->stroke_color) << "\" ";
            os << "stroke-width=\"" << l->stroke_width << "\"/>" << std::endl;
        }
        else if (const Rectangle* r = dynamic_cast<const Rectangle*>(shape)) {
            os << "<rect ";
            os << "width=\"" << r->w << "\" ";
            os << "height=\"" << r->h << "\" ";
            os << "x=\"" << r->p.x << "\" ";
            os << "y=\"" << r->p.y << "\" ";
            os << "style=\"fill:" << color_to_hex(r->fill_color) << ";";
            os << "stroke:" << color_to_hex(r->stroke_color) << ";";
            os << "stroke-width:" << r->stroke_width << "\"/>" << std::endl;
        }
        else if (const Text* t = dynamic_cast<const Text*>(shape)) {
            os << "<text ";
            os << "x=\"" << t->anchor.x << "\" ";
            os << "y=\"" << t->anchor.y << "\" ";
            os << "font-size=\"" << t->font_size << "\" ";
            os << "fill=\"" << color_to_hex(t->fill_color) << "\">";
            os << t->text << "</text>" << std::endl;
        }
        else {
            throw std::invalid_argument("unknown shape");
        }
    }
};

} /* namespace html */
} /* namespace plot */
} /* namespace zcalc */