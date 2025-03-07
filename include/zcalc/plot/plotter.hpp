#pragma once

#include <fstream>
#include <iostream>
#include <sstream>
#include <cmath>

#include "zcalc/math/frequency.hpp"
#include "zcalc/component/component.hpp"

namespace zcalc {
namespace plot {

struct PlotterConfig {
    std::string filename;
    component::IComponent* input_source { nullptr };
    component::IComponent* output_component { nullptr };
    math::Frequency min_frequency;
    math::Frequency max_frequency;
    math::Frequency target_frequency;
    double num_points { 1.0e3 };
};

} /* namespace plot */
} /* namespace zcalc */