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
#include <cstdint>
#include <fstream>
#include <vector>
#include <memory>

#include "zcalc/plot/html/figure.hpp"

namespace zcalc {
namespace plot {
namespace html {

class Canvas {
private:
    std::size_t m_x { 0 };
    std::size_t m_y { 0 };
    std::size_t m_w { 1000 };
    std::size_t m_h { 1000 };

    std::ofstream m_file;
    std::string m_filename;

    std::vector<std::shared_ptr<Figure>> m_figures;
public:
    Canvas () = delete;
    Canvas (std::string filename, std::size_t x, std::size_t y, std::size_t w, std::size_t h) : m_x(x), m_y(y), m_w(w), m_h(h) {
        m_filename = filename + ".html";
    }
    ~Canvas () = default;

    Figure* figure (std::size_t x, std::size_t y, std::size_t w, std::size_t h) {
        std::shared_ptr<Figure> fig = std::make_shared<Figure>(x, y, w, h);
        m_figures.push_back(fig);
        return fig.get();
    }

    void plot () {
        m_file.open(m_filename, std::ios::out | std::ios::trunc);
        if (!m_file.is_open()) {
            throw std::runtime_error("could not open HTML file");
        }

        m_file << "<!DOCTYPE html>" << std::endl;
        m_file << "<html>" << std::endl;
        m_file << "<body>" << std::endl;
        m_file << "<svg x=\"" << m_x << "\" y=\"" << m_y << "\" height=\"" << m_h << "\" width=\"" << m_w << "\">" << std::endl;

        for (auto& figure : m_figures) {
            figure->fit();
            figure->plot(m_file);
        }

        m_file << "</svg>" << std::endl;
        m_file << "</body>" << std::endl;
        m_file << "</html>" << std::endl;
        m_file.close();
    }
};

} /* namespace html */
} /* namespace plot */
} /* namespace zcalc */