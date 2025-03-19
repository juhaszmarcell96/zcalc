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

#include "zcalc/plot/colors.hpp"

namespace zcalc {
namespace plot {

struct IShape {
    virtual ~IShape () = default;
    virtual void offset (double x_offset, double y_offset) = 0;
    virtual void scale (double scale_x, double scale_y) = 0;
    virtual void translate (double height) = 0; // height to translate coordinates to the downward growing svg coordinate systemv
    virtual void decorate (double stroke_width, colors stroke_color, colors fill_color) = 0;
    virtual double get_min_x () const = 0;
    virtual double get_max_x () const = 0;
    virtual double get_min_y () const = 0;
    virtual double get_max_y () const = 0;
};

struct ShapeBase : public IShape {
    double stroke_width { 1.0 };
    colors stroke_color { colors::black };
    colors fill_color { colors::black };

    void decorate (double stroke_width, colors stroke_color, colors fill_color) override {
        this->stroke_width = stroke_width;
        this->stroke_color = stroke_color;
        this->fill_color = fill_color;
    }
};

struct Point : public ShapeBase {
    double x { 0.0 };
    double y { 0.0 };

    Point () = default;
    Point (double x, double y) : x(x), y(y) {}

    void offset (double x_offset, double y_offset) override {
        x += x_offset;
        y += y_offset;
    }
    void scale (double scale_x, double scale_y) override {
        x *= scale_x;
        y *= scale_y;
    }
    void translate (double height) override {
        y = height - y;
    }

    double get_min_x () const override {
        return x;
    }
    double get_max_x () const override {
        return x;
    }
    double get_min_y () const override {
        return y;
    }
    double get_max_y () const override {
        return y;
    }
};

struct Line : public ShapeBase {
    Point p0 {};
    Point p1 {};
    
    Line () = default;
    Line (double x0, double y0, double x1, double y1) : p0(x0, y0), p1(x1, y1) {}

    void offset (double x_offset, double y_offset) override {
        p0.offset(x_offset, y_offset);
        p1.offset(x_offset, y_offset);
    }
    void scale (double scale_x, double scale_y) override {
        p0.scale(scale_x, scale_y);
        p1.scale(scale_x, scale_y);
    }
    void translate (double height) override {
        p0.translate(height);
        p1.translate(height);
    }

    double get_min_x () const override {
        const double x0 = p0.get_min_x();
        const double x1 = p1.get_min_x();
        return x0 < x1 ? x0 : x1;
    }
    double get_max_x () const override {
        const double x0 = p0.get_max_x();
        const double x1 = p1.get_max_x();
        return x0 > x1 ? x0 : x1;
    }
    double get_min_y () const override {
        const double y0 = p0.get_min_y();
        const double y1 = p1.get_min_y();
        return y0 < y1 ? y0 : y1;
    }
    double get_max_y () const override {
        const double y0 = p0.get_max_y();
        const double y1 = p1.get_max_y();
        return y0 > y1 ? y0 : y1;
    }
};

struct Rectangle : public ShapeBase {
    Point p {};
    double w { 0.0 };
    double h { 0.0 };
    
    Rectangle () = default;
    Rectangle (double x, double y, double w, double h) : p(x, y), w(w), h(h) {}

    void offset (double x_offset, double y_offset) override {
        p.offset(x_offset, y_offset);
    }
    void scale (double scale_x, double scale_y) override {
        p.scale(scale_x, scale_y);
        w *= scale_x;
        h *= scale_y;
    }
    void translate (double height) override {
        p.translate(height);
    }


    double get_min_x () const override {
        return p.get_min_x();
    }
    double get_max_x () const override {
        return p.get_min_x() + w;
    }
    double get_min_y () const override {
        return p.get_min_y();
    }
    double get_max_y () const override {
        return p.get_min_y() + h;
    }
};

struct Text : public ShapeBase {
    Point anchor {};
    std::string text;
    double font_size;
    
    Text () = default;
    Text (double x, double y, const std::string& text, double font_size) : anchor(x, y), text(text), font_size(font_size) {}

    void offset (double x_offset, double y_offset) override {
        anchor.offset(x_offset, y_offset);
    }
    void scale (double scale_x, double scale_y) override {
        anchor.scale(scale_x, scale_y);
        //font_size *= scale_x; // TODO ?
    }
    void translate (double height) override {
        anchor.translate(height);
    }

    double get_min_x () const override {
        return anchor.get_min_x();
    }
    double get_max_x () const override {
        return anchor.get_max_x();
    }
    double get_min_y () const override {
        return anchor.get_min_y();
    }
    double get_max_y () const override {
        return anchor.get_max_y();
    }
};

} /* namespace plot */
} /* namespace zcalc */