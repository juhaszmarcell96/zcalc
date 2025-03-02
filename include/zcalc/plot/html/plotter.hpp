#pragma once

#include <fstream>
#include <iostream>
#include <sstream>
#include <cmath>

#include "zcalc/plot/html/canvas.hpp"
#include "zcalc/plot/html/figure.hpp"
#include "zcalc/plot/bode.hpp"
#include "zcalc/network.hpp"

namespace zcalc {
namespace plot {
namespace html {

class Plotter {
public:
    void plot (const std::string& filename, Network& network, const std::string& input_source, const std::string& output_component) {
        html::Canvas canvas { filename, 10, 10, 1000, 800 };
        html::Figure* fig_magnitude = canvas.figure(5, 5, 990, 390);
        html::Figure* fig_phase = canvas.figure(5, 405, 990, 390);

        Bode bode { network };
        bode.plot(fig_magnitude, fig_phase, input_source, output_component);

        canvas.plot();
    }
};

} /* namespace html */
} /* namespace plot */
} /* namespace zcalc */