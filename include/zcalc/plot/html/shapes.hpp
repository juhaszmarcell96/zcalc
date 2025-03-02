#pragma once

#include "zcalc/plot/shapes.hpp"
#include "zcalc/plot/html/colors.hpp"

#include <ostream>

namespace zcalc {
namespace plot {
namespace html {

class IHtmlShape {
public:
    virtual ~IHtmlShape () = default;

    virtual void offset (double x_offset, double y_offset) = 0;
    virtual void scale (double scale_x, double scale_y) = 0;
    virtual void translate (double height) = 0; // height to translate coordinates to the downward growing svg coordinate systemv

    virtual void draw (std::ostream& os) const = 0;
    virtual double get_min_x () const = 0;
    virtual double get_max_x () const = 0;
    virtual double get_min_y () const = 0;
    virtual double get_max_y () const = 0;
};

class HtmlShapeBase : IHtmlShape {
protected:
    double m_stroke_width { 0.0 };
    colors m_stroke_color { colors::black };
    colors m_fill_color { colors::black };
public:
    HtmlShapeBase () = default;
    HtmlShapeBase (double stroke_width, colors stroke_color, colors fill_color) :
        m_stroke_width(stroke_width), m_stroke_color(stroke_color), m_fill_color(fill_color) {}
    
    double get_stroke_width () const { return m_stroke_width; }
    colors get_stroke_color () const { return m_stroke_color; }
    colors get_fill_color () const { return m_fill_color; }
};

class HtmlPoint : public HtmlShapeBase {
private:
    Point m_p {};
    double m_r { 0.0 };
public:
    HtmlPoint () = default;
    HtmlPoint (double x, double y, double r, double stroke_width, colors stroke_color, colors fill_color) :
        HtmlShapeBase(stroke_width, stroke_color, fill_color), m_p(x, y), m_r(r) {}
    
    const Point& get_point () const { return m_p; }
    double get_r () const { return m_r; }

    void draw (std::ostream& os) const override {
        os << "<circle ";
        os << "cx=\"" << m_p.get_x() << "\" ";
        os << "cy=\"" << m_p.get_y() << "\" ";
        os << "r=\"" << m_r << "\" ";
        os << "stroke=\"" << color_to_hex(m_stroke_color) << "\" ";
        os << "fill=\"" << color_to_hex(m_fill_color) << "\" ";
        os << "stroke-width=\"" << m_stroke_width << "\"/>" << std::endl;
    }

    void offset (double x_offset, double y_offset) override {
        m_p.offset(x_offset, y_offset);
    }
    void scale (double scale_x, double scale_y) override {
        m_p.scale(scale_x, scale_y);
        m_r *= scale_x; // TODO ?
    }
    void translate (double height) override {
        m_p = Point {m_p.get_x(), height - m_p.get_y()};
    }

    double get_min_x () const override {
        return m_p.get_x() - m_r;
    }
    double get_max_x () const override {
        return m_p.get_x() + m_r;
    }
    double get_min_y () const override {
        return m_p.get_y() - m_r;
    }
    double get_max_y () const override {
        return m_p.get_y() + m_r;
    }
};

class HtmlLine : public HtmlShapeBase {
private:
    Line m_l {};
public:
    HtmlLine () = default;
    HtmlLine (double x0, double y0, double x1, double y1, double stroke_width, colors stroke_color, colors fill_color) :
        HtmlShapeBase(stroke_width, stroke_color, fill_color), m_l(x0, y0, x1, y1) {}

    void draw (std::ostream& os) const override {
        os << "<line ";
        os << "x1=\"" << m_l.get_p0().get_x() << "\" ";
        os << "y1=\"" << m_l.get_p0().get_y() << "\" ";
        os << "x2=\"" << m_l.get_p1().get_x() << "\" ";
        os << "y2=\"" << m_l.get_p1().get_y() << "\" ";
        os << "stroke=\"" << color_to_hex(m_stroke_color) << "\" ";
        os << "stroke-width=\"" << m_stroke_width << "\"/>" << std::endl;
    }

    void offset (double x_offset, double y_offset) override {
        m_l.offset(x_offset, y_offset);
    }
    void scale (double scale_x, double scale_y) override {
        m_l.scale(scale_x, scale_y);
    }
    void translate (double height) override {
        m_l = Line {m_l.get_p0().get_x(), height - m_l.get_p0().get_y(), m_l.get_p1().get_x(), height - m_l.get_p1().get_y()};
    }

    double get_min_x () const override {
        const double x0 = m_l.get_p0().get_x();
        const double x1 = m_l.get_p0().get_x();
        return x0 < x1 ? x0 : x1;
    }
    double get_max_x () const override {
        const double x0 = m_l.get_p0().get_x();
        const double x1 = m_l.get_p0().get_x();
        return x0 > x1 ? x0 : x1;
    }
    double get_min_y () const override {
        const double y0 = m_l.get_p0().get_y();
        const double y1 = m_l.get_p0().get_y();
        return y0 < y1 ? y0 : y1;
    }
    double get_max_y () const override {
        const double y0 = m_l.get_p0().get_y();
        const double y1 = m_l.get_p0().get_y();
        return y0 > y1 ? y0 : y1;
    }
};

class HtmlRectangle : public HtmlShapeBase {
private:
    Rectangle m_r {};
public:
    HtmlRectangle () = default;
    HtmlRectangle (double x, double y, double w, double h, double stroke_width, colors stroke_color, colors fill_color) :
        HtmlShapeBase(stroke_width, stroke_color, fill_color), m_r(x, y, w, h) {}
    
    double get_x () const { return m_r.get_p().get_x(); }
    double get_y () const { return m_r.get_p().get_y(); }
    double get_w () const { return m_r.get_w(); }
    double get_h () const { return m_r.get_h(); }

    void draw (std::ostream& os) const override {
        os << "<rect ";
        os << "width=\"" << m_r.get_w() << "\" ";
        os << "height=\"" << m_r.get_h() << "\" ";
        os << "x=\"" << m_r.get_p().get_x() << "\" ";
        os << "y=\"" << m_r.get_p().get_y() << "\" ";
        os << "style=\"fill:" << color_to_hex(m_fill_color) << ";";
        os << "stroke:" << color_to_hex(m_stroke_color) << ";";
        os << "stroke-width:" << m_stroke_width << "\"/>" << std::endl;
    }

    void offset (double x_offset, double y_offset) override {
        m_r.offset(x_offset, y_offset);
    }
    void scale (double scale_x, double scale_y) override {
        m_r.scale(scale_x, scale_y);
    }
    void translate (double height) override {
        m_r = Rectangle {m_r.get_p().get_x(), height - m_r.get_p().get_y(), m_r.get_w(), m_r.get_h()};
    }

    double get_min_x () const override {
        return m_r.get_p().get_x();
    }
    double get_max_x () const override {
        return m_r.get_p().get_x() + m_r.get_w();
    }
    double get_min_y () const override {
        return m_r.get_p().get_y();
    }
    double get_max_y () const override {
        return m_r.get_p().get_y() + m_r.get_h();
    }
};

class HtmlText : public HtmlShapeBase {
private:
    Text m_t {};
public:
    HtmlText () = default;
    HtmlText (double x, double y, const std::string& text, double font_size, colors fill_color) :
        HtmlShapeBase(0.0, colors::black, fill_color), m_t(x, y, text, font_size) {}

    void draw (std::ostream& os) const override {
        os << "<text ";
        os << "x=\"" << m_t.get_anchor_point().get_x() << "\" ";
        os << "y=\"" << m_t.get_anchor_point().get_y() << "\" ";
        os << "font-size=\"" << m_t.get_font_size() << "\" ";
        os << "fill=\"" << color_to_hex(m_fill_color) << "\">";
        os << m_t.get_text() << "</text>" << std::endl;
    }

    void offset (double x_offset, double y_offset) override {
        m_t.offset(x_offset, y_offset);
    }
    void scale (double scale_x, double scale_y) override {
        m_t.scale(scale_x, scale_y);
    }
    void translate (double height) override {
        m_t = Text {m_t.get_anchor_point().get_x(), height - m_t.get_anchor_point().get_y(), m_t.get_text(), m_t.get_font_size()};
    }

    double get_min_x () const override {
        return m_t.get_anchor_point().get_x();
    }
    double get_max_x () const override {
        return m_t.get_anchor_point().get_x();
    }
    double get_min_y () const override {
        return m_t.get_anchor_point().get_y();
    }
    double get_max_y () const override {
        return m_t.get_anchor_point().get_y();
    }
};

} /* namespace html */
} /* namespace plot */
} /* namespace zcalc */