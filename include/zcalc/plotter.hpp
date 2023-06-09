#pragma once

#include <fstream>
#include <iostream>
#include <sstream>
#include <cmath>

namespace zcalc {

class Plotter {
private:
    std::size_t m_width;
    std::size_t m_height;
    std::string m_filename;
    std::stringstream m_text;

    std::size_t m_bode_w;
    std::size_t m_bode_h;
    std::size_t m_bode_y_offs;
    std::size_t m_bode_x_offs;

    std::size_t m_decade_w;
    std::size_t m_decade_h;
    std::size_t m_zero_db;
public:
    Plotter () = delete;
    Plotter (std::size_t width, std::size_t height) : m_width(width), m_height(height) {
        m_filename = "tmp.html";

        m_text << "<!DOCTYPE html>" << std::endl;
        m_text << "<html>" << std::endl;
        m_text << "<body>" << std::endl;
        m_text << "<svg height=\"" << width + 2 << "\" width=\"" << height + 2 << "\">" << std::endl;

        m_bode_w = width;
        m_bode_h = height;
        m_bode_y_offs = 1;
        m_bode_x_offs = 1;
        m_decade_w = width / 10;
        m_decade_h = width / 200;

        m_zero_db = 20 * m_decade_h + m_bode_y_offs;

        m_text << "<line x1=\"0\" y1=\"" <<   0 * m_decade_h + m_bode_y_offs << "\" x2=\"" << m_bode_w << "\" y2=\"" <<   0 * m_decade_h + m_bode_y_offs << "\" stroke=\"black\" stroke-width=\"1\"/>" << std::endl;
        m_text << "<line x1=\"0\" y1=\"" <<  20 * m_decade_h + m_bode_y_offs << "\" x2=\"" << m_bode_w << "\" y2=\"" <<  20 * m_decade_h + m_bode_y_offs << "\" stroke=\"black\" stroke-width=\"1\"/>" << std::endl;
        m_text << "<line x1=\"0\" y1=\"" <<  23 * m_decade_h + m_bode_y_offs << "\" x2=\"" << m_bode_w << "\" y2=\"" <<  23 * m_decade_h + m_bode_y_offs << "\" stroke=\"blue\" stroke-width=\"1\"/>" << std::endl;
        m_text << "<line x1=\"0\" y1=\"" <<  40 * m_decade_h + m_bode_y_offs << "\" x2=\"" << m_bode_w << "\" y2=\"" <<  40 * m_decade_h + m_bode_y_offs << "\" stroke=\"black\" stroke-width=\"1\"/>" << std::endl;
        m_text << "<line x1=\"0\" y1=\"" <<  60 * m_decade_h + m_bode_y_offs << "\" x2=\"" << m_bode_w << "\" y2=\"" <<  60 * m_decade_h + m_bode_y_offs << "\" stroke=\"black\" stroke-width=\"1\"/>" << std::endl;
        m_text << "<line x1=\"0\" y1=\"" <<  80 * m_decade_h + m_bode_y_offs << "\" x2=\"" << m_bode_w << "\" y2=\"" <<  80 * m_decade_h + m_bode_y_offs << "\" stroke=\"black\" stroke-width=\"1\"/>" << std::endl;
        m_text << "<line x1=\"0\" y1=\"" << 100 * m_decade_h + m_bode_y_offs << "\" x2=\"" << m_bode_w << "\" y2=\"" << 100 * m_decade_h + m_bode_y_offs << "\" stroke=\"black\" stroke-width=\"1\"/>" << std::endl;
        m_text << "<line x1=\"0\" y1=\"" << 120 * m_decade_h + m_bode_y_offs << "\" x2=\"" << m_bode_w << "\" y2=\"" << 120 * m_decade_h + m_bode_y_offs << "\" stroke=\"black\" stroke-width=\"1\"/>" << std::endl;
        m_text << "<line x1=\"0\" y1=\"" << 140 * m_decade_h + m_bode_y_offs << "\" x2=\"" << m_bode_w << "\" y2=\"" << 140 * m_decade_h + m_bode_y_offs << "\" stroke=\"black\" stroke-width=\"1\"/>" << std::endl;
        m_text << "<line x1=\"0\" y1=\"" << 160 * m_decade_h + m_bode_y_offs << "\" x2=\"" << m_bode_w << "\" y2=\"" << 160 * m_decade_h + m_bode_y_offs << "\" stroke=\"black\" stroke-width=\"1\"/>" << std::endl;
        m_text << "<line x1=\"0\" y1=\"" << 180 * m_decade_h + m_bode_y_offs << "\" x2=\"" << m_bode_w << "\" y2=\"" << 180 * m_decade_h + m_bode_y_offs << "\" stroke=\"black\" stroke-width=\"1\"/>" << std::endl;
        m_text << "<line x1=\"0\" y1=\"" << 200 * m_decade_h + m_bode_y_offs << "\" x2=\"" << m_bode_w << "\" y2=\"" << 200 * m_decade_h + m_bode_y_offs << "\" stroke=\"black\" stroke-width=\"1\"/>" << std::endl;

        m_text << "<line x1=\"" <<  0 * m_decade_w + m_bode_x_offs << "\" y1=\"0\" x2=\"" <<  0 * m_decade_w + m_bode_x_offs << "\" y2=\"" << m_bode_h << "\" stroke=\"black\" stroke-width=\"1\"/>" << std::endl;
        m_text << "<line x1=\"" <<  1 * m_decade_w + m_bode_x_offs << "\" y1=\"0\" x2=\"" <<  1 * m_decade_w + m_bode_x_offs << "\" y2=\"" << m_bode_h << "\" stroke=\"black\" stroke-width=\"1\"/>" << std::endl;
        m_text << "<line x1=\"" <<  2 * m_decade_w + m_bode_x_offs << "\" y1=\"0\" x2=\"" <<  2 * m_decade_w + m_bode_x_offs << "\" y2=\"" << m_bode_h << "\" stroke=\"black\" stroke-width=\"1\"/>" << std::endl;
        m_text << "<line x1=\"" <<  3 * m_decade_w + m_bode_x_offs << "\" y1=\"0\" x2=\"" <<  3 * m_decade_w + m_bode_x_offs << "\" y2=\"" << m_bode_h << "\" stroke=\"black\" stroke-width=\"1\"/>" << std::endl;
        m_text << "<line x1=\"" <<  4 * m_decade_w + m_bode_x_offs << "\" y1=\"0\" x2=\"" <<  4 * m_decade_w + m_bode_x_offs << "\" y2=\"" << m_bode_h << "\" stroke=\"black\" stroke-width=\"1\"/>" << std::endl;
        m_text << "<line x1=\"" <<  5 * m_decade_w + m_bode_x_offs << "\" y1=\"0\" x2=\"" <<  5 * m_decade_w + m_bode_x_offs << "\" y2=\"" << m_bode_h << "\" stroke=\"black\" stroke-width=\"1\"/>" << std::endl;
        m_text << "<line x1=\"" <<  6 * m_decade_w + m_bode_x_offs << "\" y1=\"0\" x2=\"" <<  6 * m_decade_w + m_bode_x_offs << "\" y2=\"" << m_bode_h << "\" stroke=\"black\" stroke-width=\"1\"/>" << std::endl;
        m_text << "<line x1=\"" <<  7 * m_decade_w + m_bode_x_offs << "\" y1=\"0\" x2=\"" <<  7 * m_decade_w + m_bode_x_offs << "\" y2=\"" << m_bode_h << "\" stroke=\"black\" stroke-width=\"1\"/>" << std::endl;
        m_text << "<line x1=\"" <<  8 * m_decade_w + m_bode_x_offs << "\" y1=\"0\" x2=\"" <<  8 * m_decade_w + m_bode_x_offs << "\" y2=\"" << m_bode_h << "\" stroke=\"black\" stroke-width=\"1\"/>" << std::endl;
        m_text << "<line x1=\"" <<  9 * m_decade_w + m_bode_x_offs << "\" y1=\"0\" x2=\"" <<  9 * m_decade_w + m_bode_x_offs << "\" y2=\"" << m_bode_h << "\" stroke=\"black\" stroke-width=\"1\"/>" << std::endl;
        m_text << "<line x1=\"" << 10 * m_decade_w + m_bode_x_offs << "\" y1=\"0\" x2=\"" << 10 * m_decade_w + m_bode_x_offs << "\" y2=\"" << m_bode_h << "\" stroke=\"black\" stroke-width=\"1\"/>" << std::endl;
    }
    ~Plotter () = default;

    void draw_line (std::size_t x0, std::size_t y0, std::size_t x1, std::size_t y1) {
        m_text << "<line x1=\"" << x0 <<
                  "\" y1=\"" << y0 <<
                  "\" x2=\"" << x1 <<
                  "\" y2=\"" << y1 <<
                  "\" stroke=\"red\" stroke-width=\"1\"/>" << std::endl;
    }

    void draw_dot (std::size_t x, std::size_t y) {
        m_text << "<circle cx=\"" << x << "\" cy=\"" << y << "\" r=\"1\" stroke=\"red\" stroke-width=\"1\" fill=\"red\" />" << std::endl;
    }

    void draw_hjw(double amplitude, double frequency) {
        double base_frequency = 1.0;
        //std::cout << frequency << "      " << std::log(frequency) << std::endl;
        double decade = m_bode_x_offs + std::log(frequency) * (m_decade_w / 2.302585);
        double decibel = m_zero_db + (-1.0) * (20.0 * std::log10(amplitude)) * (5.0);
        m_text << "<circle cx=\"" << decade << "\" cy=\"" << decibel << "\" r=\"1\" stroke=\"red\" stroke-width=\"1\" fill=\"red\" />" << std::endl;
    }

    void plot () {
        m_text << "</svg>" << std::endl;
        m_text << "</body>" << std::endl;
        m_text << "</html>" << std::endl;

        std::fstream html_file (m_filename, std::ios::out | std::ios::trunc);
        if (!html_file.is_open()) {
            std::cout << "ERROR : could not open file" << std::endl;
            return; /* TODO : throw some exception */
        }
        html_file << m_text.str();
        html_file.close();
    }
};

} /* namespace zcalc */