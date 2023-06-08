#pragma once

#include <vector>
#include <string>

namespace zcalc {

class Gate;

struct Node {
    std::string designator;
    std::vector<Gate*> gates;
};

} /* namespace zcalc */