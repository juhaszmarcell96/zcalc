#pragma once

#include <cstdint>
#include <string>

#include "zcalc/plot/plot.hpp"

namespace zcalc {

/* assumes HTML SVG context */
class Figure {
private:
    std::size_t m_x { 0 };
    std::size_t m_y { 0 };
    std::size_t m_w { 1000 };
    std::size_t m_h { 1000 };
    
    std::string m_text;
public:
    Figure () = delete;
    Figure (std::size_t x, std::size_t y, std::size_t w, std::size_t h) : m_x(x), m_y(y), m_w(w), m_h(h) {
        Line l0 {};
        Line l1 {};
        Line l2 {};
        Line l3 {};
        l0.x0 = m_x;       l0.x1 = m_x;       l0.y0 = m_y;       l0.y1 = m_y + m_h; l0.stroke_color = colors::black; l0.stroke_width = 2;
        l1.x0 = m_x;       l1.x1 = m_x + m_w; l1.y0 = m_y + m_h; l1.y1 = m_y + m_h; l1.stroke_color = colors::black; l1.stroke_width = 2;
        l2.x0 = m_x + m_w; l2.x1 = m_x + m_w; l2.y0 = m_y + m_h; l2.y1 = m_y;       l2.stroke_color = colors::black; l2.stroke_width = 2;
        l3.x0 = m_x + m_w; l3.x1 = m_x;       l3.y0 = m_y;       l3.y1 = m_y;       l3.stroke_color = colors::black; l3.stroke_width = 2;
        draw_line (l0);
        draw_line (l1);
        draw_line (l2);
        draw_line (l3);
    }
    ~Figure () = default;

    std::size_t get_x () const { return m_x; }
    std::size_t get_y () const { return m_y; }
    std::size_t get_w () const { return m_w; }
    std::size_t get_h () const { return m_h; }

    void draw_line (const Line& l) {
        m_text += "<line ";
        m_text += "x1=\"" + std::to_string(l.x0) + "\" ";
        m_text += "y1=\"" + std::to_string(l.y0) + "\" ";
        m_text += "x2=\"" + std::to_string(l.x1) + "\" ";
        m_text += "y2=\"" + std::to_string(l.y1) + "\" ";
        m_text += "stroke=\"" + color_to_hex(l.stroke_color) + "\"";
        m_text += "stroke-width=\"" + std::to_string(l.stroke_width) + "\"/>\n";
    }

    void draw_point (const Point& p) {
        m_text += "<circle cx=\"" + std::to_string(p.x) +
                       "\" cy=\"" + std::to_string(p.y) +
                       "\" r=\""  + std::to_string(p.r) + "\" ";
        m_text += "stroke=\"" + color_to_hex(p.stroke_color) + "\"";
        m_text += "fill=\""   + color_to_hex(p.fill_color)   + "\"";
        m_text += "stroke-width=\"" + std::to_string(p.stroke_width) + "\"/>\n";
    }

    void draw_text (const Text& t) {
        m_text += "<text x=\"" + std::to_string(t.x) + "\" y=\"" + std::to_string(t.y) + "\" ";
        m_text += "font-size=\"" + std::to_string(t.font_size) + "\" ";
        m_text += "fill=\"" + color_to_hex(t.fill_color) + "\">" + t.text + "</text>\n";
    }

    const std::string& get () const {
        return m_text;
    }

    void plot (Plot& plot) {
        /* modify the plot so that it fits the figure perfectly */
        plot.normalize(m_x, m_x + m_w, m_y, m_y + m_h);
        /* the y coordinates are mirrored in the plot because in the SVG the y coordinate grown downwards */
        for (Point& point : plot.get_points()) {
            point.y = m_y + m_h / 2.0 + (m_y + m_h / 2.0 - point.y);
        }
        for (Line& line : plot.get_lines()) {
            line.y0 = m_y + m_h / 2.0 + (m_y + m_h / 2.0 - line.y0);
            line.y1 = m_y + m_h / 2.0 + (m_y + m_h / 2.0 - line.y1);
        }
        for (Text& text : plot.get_texts()) {
            text.y = m_y + m_h / 2.0 + (m_y + m_h / 2.0 - text.y);
        }
        
        for (const Line& line : plot.get_lines()) {
            draw_line(line);
        }
        for (const Text& text : plot.get_texts()) {
            draw_text(text);
        }
        for (const Point& point : plot.get_points()) {
            draw_point(point);
        }
    }
};

} /* namespace zcalc */