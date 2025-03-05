#pragma once

#include <fstream>
#include <iostream>
#include <sstream>
#include <cmath>

#include "zcalc/math/frequency.hpp"

namespace zcalc {
namespace plot {

struct PlotterConfig {
    std::string filename;
    std::string input_source;
    std::string output_component;
    math::Frequency min_frequency;
    math::Frequency max_frequency;
    math::Frequency target_frequency;
    double granularity { 1.0 };
};

} /* namespace plot */
} /* namespace zcalc */