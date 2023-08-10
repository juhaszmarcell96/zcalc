#pragma once

#include <cstdint>
#include <string>

#include "zcalc/plot/plot.hpp"

namespace zcalc {

enum class colors {
    black = 0,
    red = 1,
    blue = 2
};

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
        draw_line (m_x      , m_y      , m_x      , m_y + m_h, colors::black, 2);
        draw_line (m_x      , m_y + m_h, m_x + m_w, m_y + m_h, colors::black, 2);
        draw_line (m_x + m_w, m_y + m_h, m_x + m_w, m_y      , colors::black, 2);
        draw_line (m_x + m_w, m_y      , m_x      , m_y      , colors::black, 2);
    }
    ~Figure () = default;

    std::size_t get_x () const { return m_x; }
    std::size_t get_y () const { return m_y; }
    std::size_t get_w () const { return m_w; }
    std::size_t get_h () const { return m_h; }

    void draw_line (double x0, double y0, double x1, double y1, colors color, std::size_t width) {
        m_text += "<line x1=\"" + std::to_string(x0) +
                     "\" y1=\"" + std::to_string(y0) +
                     "\" x2=\"" + std::to_string(x1) +
                     "\" y2=\"" + std::to_string(y1) + "\" ";
        switch (color) {
            case colors::black : {
                m_text += "stroke=\"black\" ";
                break;
            }
            case colors::red : {
                m_text += "stroke=\"red\" ";
                break;
            }
            case colors::blue : {
                m_text += "stroke=\"blue\" ";
                break;
            }
            default : {
                m_text += "stroke=\"black\" ";
                break;
            }
        }
        m_text += "stroke-width=\"" + std::to_string(width) + "\"/>\n";
    }

    void draw_dot (double x, double y, std::size_t radius, colors color, std::size_t width) {
        m_text += "<circle cx=\"" + std::to_string(x) +
                       "\" cy=\"" + std::to_string(y) +
                       "\" r=\""  + std::to_string(radius) + "\" ";
        switch (color) {
            case colors::black : {
                m_text += "stroke=\"black\" fill=\"black\" ";
                break;
            }
            case colors::red : {
                m_text += "stroke=\"red\" fill=\"red\" ";
                break;
            }
            case colors::blue : {
                m_text += "stroke=\"blue\" fill=\"blue\" ";
                break;
            }
            default : {
                m_text += "stroke=\"black\" fill=\"black\" ";
                break;
            }
        }
        m_text += "stroke-width=\"" + std::to_string(width) + "\"/>\n";
    }

    void draw_text (double x, double y, std::string text) {
        m_text += "<text x=\"" + std::to_string(x) + "\" y=\"" + std::to_string(y) + "\" fill=\"black\">" + text + "</text>\n";
    }

    const std::string& get () const {
        return m_text;
    }

    void plot (Plot& plot) {
        plot.normalize(0, m_w, 0, m_h);
        /* the y coordinates are mirrored in the plot because in the SVG the y coordinate grown downwards */
        for (const Point& point : plot.get()) {
            double y_coordinate = m_h / 2 + (m_h / 2 - point.y);
            draw_dot(point.x, y_coordinate, 1, colors::red, 1);
        }
    }
};

} /* namespace zcalc */