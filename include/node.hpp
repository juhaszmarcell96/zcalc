#pragma once

#include <vector>
#include <memory>

namespace zcalc {

class Component;

typedef std::shared_ptr<Component> component_ptr_t;

class Node {
public:
    std::vector<component_ptr_t> components;
};

} /* namespace zcalc */