#pragma once

#include <fstream>
#include <iostream>
#include <sstream>
#include <cmath>

#include "zcalc/plot/html/canvas.hpp"
#include "zcalc/plot/html/figure.hpp"
#include "zcalc/plot/bode.hpp"
#include "zcalc/plot/plotter.hpp"
#include "zcalc/network.hpp"

namespace zcalc {
namespace plot {
namespace html {

class Plotter {
public:
    void plot (Network& network, const PlotterConfig& config) {
        html::Canvas canvas { config.filename, 10, 10, 1000, 800 };
        html::Figure* fig_magnitude = canvas.figure(5, 5, 990, 390);
        html::Figure* fig_phase = canvas.figure(5, 405, 990, 390);

        Bode bode {};
        bode.plot(fig_magnitude, fig_phase, network, config);
        if (!config.target_frequency.is_dc()) {
            bode.mark_frequency(config.target_frequency);
        }

        canvas.plot();
    }
};

} /* namespace html */
} /* namespace plot */
} /* namespace zcalc */