#pragma once

#include <zcalc/internal/gate.hpp>
#include <zcalc/internal/loop_message.hpp>

#include <vector>
#include <string>

namespace zcalc {

struct Node {
    std::string designator;
    std::vector<Gate*> gates;

    void propagate (LoopMessage message, const Gate* source_gate) const {
        if (message.contains(this)) {
            if (message.is_starting_node(this)) {
                if (message.get_num_nodes() > 1) {
                    /* this is a valid loop -> push it to the stack */
                    LoopMessage::append_loop(std::move(message));
                    return;
                }
                /* this "loop" has just been started */
            }
            else {
                /* this is not a valid loop */
                return;
            }
        }
        for (Gate* gate : gates) {
            /* pass the message to the connected gates but not the gate it is coming from */
            if (gate != source_gate) gate->component->propagate(message, gate);
        }
    }
};

} /* namespace zcalc */