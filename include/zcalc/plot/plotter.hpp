#pragma once

#include <fstream>
#include <iostream>
#include <sstream>
#include <cmath>

#include "zcalc/plot/canvas.hpp"
#include "zcalc/plot/figure.hpp"
#include "zcalc/plot/bode.hpp"
#include "zcalc/network.hpp"

namespace zcalc {

class Plotter {
public:
    void plot (const std::string& filename, Network& network, const std::string& input_source, const std::string& output_component) {
        Canvas canvas { filename, 10, 10, 1000, 800 };
        Figure* fig_magnitude = canvas.figure(5, 5, 990, 390);
        Figure* fig_phase = canvas.figure(5, 405, 990, 390);

        Bode bode { network };
        bode.plot(fig_magnitude, fig_phase, input_source, output_component);

        canvas.plot();
    }
};

} /* namespace zcalc */