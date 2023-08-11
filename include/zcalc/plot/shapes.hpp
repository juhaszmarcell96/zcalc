#pragma once

#include <string>
#include <cstdint>

namespace zcalc {

enum class colors {
    black,
    red,
    green,
    blue
};

std::string color_to_hex (colors color) {
    switch (color) {
        case colors::black : { return "#000000"; }
        case colors::red : { return "#FF0000"; }
        case colors::green : { return "#00FF00"; }
        case colors::blue : { return "#0000FF"; }
        default : { return "#000000"; }
    }
}

struct Shape {
    colors stroke_color { colors::black };
    colors fill_color { colors::black };
    double stroke_width { 0.0 };
};

struct Point : public Shape {
    double x { 0.0 };
    double y { 0.0 };
    double r { 0.0 };
};

struct Line : public Shape {
    double x0 { 0.0 };
    double y0 { 0.0 };
    double x1 { 0.0 };
    double y1 { 0.0 };
};

struct Text : public Shape {
    double x { 0.0 };
    double y { 0.0 };
    std::size_t font_size;
    std::string text;
};

} /* namespace zcalc */