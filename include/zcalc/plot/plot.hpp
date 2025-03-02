#pragma once

#include <vector>

#include "zcalc/plot/shapes.hpp"

namespace zcalc {
namespace plot {

class IPlot {
public:
    virtual ~IPlot () = default;

    virtual std::vector<IShape*> get_shapes () = 0;
    virtual void get_min_max (double& min_x, double& min_y, double& max_x, double& max_y) const = 0;
    virtual void add_point (double x, double y) = 0;
};

} /* namespace plot */
} /* namespace zcalc */