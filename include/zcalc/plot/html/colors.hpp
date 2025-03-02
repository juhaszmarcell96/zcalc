#pragma once

#include "zcalc/plot/shapes.hpp"

#include <ostream>

namespace zcalc {
namespace plot {
namespace html {

enum class colors {
    black,
    red,
    green,
    blue,
    white
};

std::string color_to_hex (colors color) {
    switch (color) {
        case colors::black : { return "#000000"; }
        case colors::red : { return "#FF0000"; }
        case colors::green : { return "#00FF00"; }
        case colors::blue : { return "#0000FF"; }
        case colors::white : { return "#FFFFFF"; }
        default : { return "#000000"; }
    }
}

} /* namespace html */
} /* namespace plot */
} /* namespace zcalc */