#pragma once

#include <string>

namespace zcalc {

class Node;

struct Gate {
    std::string designator;
    Node* node;
};

} /* namespace zcalc */