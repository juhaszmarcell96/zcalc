#pragma once

#include <cstdint>
#include <vector>

namespace zcalc {

struct Point {
    double x;
    double y;
};

class Plot {
private:
    std::vector<Point> m_points;

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

    void add_point (double x, double y) {
        m_points.push_back(Point{.x = x, .y = y });
    }

    void clear () {
        m_points.clear();
    }

    std::size_t size () const {
        return m_points.size();
    }

    const Point& get (std::size_t index) const {
        return m_points[index];
    }

    const std::vector<Point>& get () const {
        return m_points;
    }

    void normalize () {
        if (m_points.size() == 0) return;
        /* scale the coordinates so that every point fits between 0 and 1 on both axis */
        double min_x = m_points[0].x;
        double min_y = m_points[0].y;
        double max_x = m_points[0].x;
        double max_y = m_points[0].y;

        for (const Point& point : m_points) {
            if (point.x < min_x) min_x = point.x;
            if (point.y < min_y) min_y = point.y;
            if (point.x > max_x) max_x = point.x;
            if (point.y > max_y) max_y = point.y;
        }

        double range_x = max_x - min_x;
        double range_y = max_y - min_y;
        
        for (Point& point : m_points) {
            point.x = (point.x - min_x) / range_x;
            point.y = (point.y - min_y) / range_y;
        }
    }
/*
    void normalize (double min_x, double range_x) {
        if (m_points.size() == 0) return;
        ltrim(min_x);
        rtrim(min_x + range_x);
        
        m_min_x = min_x;
        m_min_y = m_points[0].y;
        double max_y = m_points[0].y;

        for (const Point& point : m_points) {
            if (point.y < m_min_y) m_min_y = point.y;
            if (point.y > max_y) max_y = point.y;
        }

        m_range_x = range_x;
        m_range_y = max_y - m_min_y;
        
        m_normalize();
    }
*/
    void normalize (double x0, double x1, double y0, double y1) {
        if (m_points.size() == 0) return;
        /* scale the coordinates so that every point fits between 0 and 1 on both axis */
        double min_x = m_points[0].x;
        double min_y = m_points[0].y;
        double max_x = m_points[0].x;
        double max_y = m_points[0].y;

        for (const Point& point : m_points) {
            if (point.x < min_x) min_x = point.x;
            if (point.y < min_y) min_y = point.y;
            if (point.x > max_x) max_x = point.x;
            if (point.y > max_y) max_y = point.y;
        }

        double range_x = max_x - min_x;
        double range_y = max_y - min_y;
        
        for (Point& point : m_points) {
            point.x = x0 + (((point.x - min_x) * (x1 - x0)) / range_x);
            point.y = y0 + (((point.y - min_y) * (y1 - y0)) / range_y);
        }
    }
};

} /* namespace zcalc */