#pragma once

#include <vector>
#include <memory>
#include <string>

namespace zcalc {

class Component;

typedef std::shared_ptr<Component> component_ptr_t;

class Node {
public:
    std::vector<component_ptr_t> components;
    std::string name;
    bool visited = false;
    bool start = false;
};

typedef std::shared_ptr<Node> node_ptr_t;

} /* namespace zcalc */