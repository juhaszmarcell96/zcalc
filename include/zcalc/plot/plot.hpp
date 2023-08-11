#pragma once

#include <cstdint>
#include <vector>

#include "zcalc/plot/shapes.hpp"

namespace zcalc {

class Plot {
private:
    std::vector<Point> m_points;
    std::vector<Line> m_lines;
    std::vector<Text> m_texts;

    /* left trim */
    void ltrim (double limit) {
        std::vector<Point>::iterator it;
        for (it = m_points.begin(); it < m_points.end(); /* don't increment automatically */) {
            if (it->x < limit) {
                it = m_points.erase(it);
            }
            else {
                ++it;
            }
        }
    }

    /* right trim */
    void rtrim (double limit) {
        std::vector<Point>::iterator it;
        for (it = m_points.begin(); it < m_points.end(); /* don't increment automatically */) {
            if (it->x > limit) {
                it = m_points.erase(it);
            }
            else {
                ++it;
            }
        }
    }
public:
    Plot () = default;
    ~Plot () = default;

    void add_point (double x, double y, double r = 1.0, double stroke_w = 1.0, colors fill = colors::red, colors stroke = colors::red) {
        Point p {};
        p.fill_color = fill;
        p.stroke_color = stroke;
        p.x = x;
        p.y = y;
        p.r = r;
        p.stroke_width = stroke_w;
        m_points.push_back(std::move(p));
    }

    void add_line (double x0, double y0, double x1, double y1, double stroke_w = 1.0, colors stroke = colors::black) {
        Line l {};
        l.stroke_color = stroke;
        l.stroke_width = stroke_w;
        l.x0 = x0;
        l.x1 = x1;
        l.y0 = y0;
        l.y1 = y1;
        m_lines.push_back(std::move(l));
    }

    void add_text (std::string text, double x, double y, std::size_t font_size = 12, colors fill = colors::black) {
        Text t {};
        t.fill_color = fill;
        t.font_size = font_size;
        t.x = x;
        t.y = y;
        t.text = text;
        m_texts.push_back(std::move(t));
    }

    void clear () {
        m_points.clear();
        m_lines.clear();
        m_texts;clear();
    }

    std::vector<Point>& get_points () {
        return m_points;
    }

    std::vector<Line>& get_lines () {
        return m_lines;
    }

    std::vector<Text>& get_texts () {
        return m_texts;
    }

    void get_min_max (double& min_x, double& min_y, double& max_x, double& max_y) {
        if (m_points.size() == 0) return;

        min_x = m_points[0].x;
        min_y = m_points[0].y;
        max_x = m_points[0].x;
        max_y = m_points[0].y;

        for (const Point& point : m_points) {
            if (point.x < min_x) min_x = point.x;
            if (point.y < min_y) min_y = point.y;
            if (point.x > max_x) max_x = point.x;
            if (point.y > max_y) max_y = point.y;
        }

        for (const Line& line : m_lines) {
            if (line.x0 < min_x) min_x = line.x0;
            if (line.x1 < min_x) min_x = line.x1;
            if (line.y0 < min_y) min_y = line.y0;
            if (line.y1 < min_y) min_y = line.y1;
            if (line.x0 > max_x) max_x = line.x0;
            if (line.x1 > max_x) max_x = line.x1;
            if (line.y0 > max_y) max_y = line.y0;
            if (line.y1 > max_y) max_y = line.y1;
        }
    }

    void normalize (double x0, double x1, double y0, double y1) {
        if (m_points.size() == 0) return;
        /* scale the coordinates so that every point fits between the limits on both axis */
        double min_x;
        double min_y;
        double max_x;
        double max_y;

        get_min_max(min_x, min_y, max_x, max_y);

        double range_x = max_x - min_x;
        double range_y = max_y - min_y;
        
        for (Point& point : m_points) {
            point.x = x0 + (((point.x - min_x) * (x1 - x0)) / range_x);
            point.y = y0 + (((point.y - min_y) * (y1 - y0)) / range_y);
        }
        
        for (Line& line : m_lines) {
            line.x0 = x0 + (((line.x0 - min_x) * (x1 - x0)) / range_x);
            line.y0 = y0 + (((line.y0 - min_y) * (y1 - y0)) / range_y);
            line.x1 = x0 + (((line.x1 - min_x) * (x1 - x0)) / range_x);
            line.y1 = y0 + (((line.y1 - min_y) * (y1 - y0)) / range_y);
        }
        
        for (Text& text : m_texts) {
            text.x = x0 + (((text.x - min_x) * (x1 - x0)) / range_x);
            text.y = y0 + (((text.y - min_y) * (y1 - y0)) / range_y);
        }
    }
};

} /* namespace zcalc */