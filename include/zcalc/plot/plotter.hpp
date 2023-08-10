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
    void plot (const std::string& filename, Network& network) {
        Canvas canvas { filename, 10, 10, 1000, 800 };
        Figure* fig_magnitude = canvas.figure(0, 0, 1000, 400);
        Figure* fig_phase = canvas.figure(0, 400, 1000, 400);

        Bode bode { network };
        bode.plot(fig_magnitude, fig_phase);

        canvas.plot();
    }
};

} /* namespace zcalc */