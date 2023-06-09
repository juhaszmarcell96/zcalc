#pragma once

#include <string>

namespace zcalc {

class Node;
class Component;

struct Gate {
    std::string designator;
    Node* node;
    Component* component;
};

} /* namespace zcalc */