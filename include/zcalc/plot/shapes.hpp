#pragma once

#include <string>
#include <cstdint>

namespace zcalc {
namespace plot {

class Point {
private:
    double m_x { 0.0 };
    double m_y { 0.0 };
public:
    Point () = default;
    Point (double x, double y) : m_x(x), m_y(y) {}
    
    double get_x () const { return m_x; }
    double get_y () const { return m_y; }

    void offset (double x_offset, double y_offset) {
        m_x += x_offset;
        m_y += y_offset;
    }
    void scale (double scale_x, double scale_y) {
        m_x *= scale_x;
        m_y *= scale_y;
    }
};

class Line {
private:
    Point m_p0 {};
    Point m_p1 {};
public:
    Line () = default;
    Line (double x0, double y0, double x1, double y1) : m_p0(x0, y0), m_p1(x1, y1) {}
    
    const Point& get_p0 () const { return m_p0; }
    const Point& get_p1 () const { return m_p1; }

    void offset (double x_offset, double y_offset) {
        m_p0.offset(x_offset, y_offset);
        m_p1.offset(x_offset, y_offset);
    }
    void scale (double scale_x, double scale_y) {
        m_p0.scale(scale_x, scale_y);
        m_p1.scale(scale_x, scale_y);
    }
};

class Rectangle {
private:
    Point m_p {};
    double m_w { 0.0 };
    double m_h { 0.0 };
public:
    Rectangle () = default;
    Rectangle (double x, double y, double w, double h) : m_p(x, y), m_w(w), m_h(h) {}
    
    const Point& get_p () const { return m_p; }
    double get_w () const { return m_w; }
    double get_h () const { return m_h; }

    void offset (double x_offset, double y_offset) {
        m_p.offset(x_offset, y_offset);
    }
    void scale (double scale_x, double scale_y) {
        m_p.scale(scale_x, scale_y);
        m_w *= scale_x;
        m_h *= scale_y;
    }
};

class Text {
private:
    Point m_anchor {};
    std::string m_text;
    double m_font_size;
public:
    Text () = default;
    Text (double x, double y, const std::string& text, double font_size) : m_anchor(x, y), m_text(text), m_font_size(font_size) {}

    const Point& get_anchor_point () const { return m_anchor; }
    const std::string& get_text () const { return m_text; }
    double get_font_size () const { return m_font_size; }

    void offset (double x_offset, double y_offset) {
        m_anchor.offset(x_offset, y_offset);
    }
    void scale (double scale_x, double scale_y) {
        m_anchor.scale(scale_x, scale_y);
        m_font_size *= scale_x; // TODO ?
    }
};

} /* namespace plot */
} /* namespace zcalc */