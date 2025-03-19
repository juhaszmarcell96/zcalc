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

#include "zcalc/plot/colors.hpp"

#include <ostream>

namespace zcalc {
namespace plot {
namespace html {

std::string color_to_hex (colors color) {
    switch (color) {
        case colors::black : { return "#000000"; }
        case colors::red : { return "#FF0000"; }
        case colors::green : { return "#00FF00"; }
        case colors::blue : { return "#0000FF"; }
        case colors::white : { return "#FFFFFF"; }
        case colors::light_grey : { return "#F0F0F0"; }
        default : { return "#000000"; }
    }
}

} /* namespace html */
} /* namespace plot */
} /* namespace zcalc */