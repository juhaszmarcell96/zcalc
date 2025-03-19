/* Copyright (C) 2025 Marcell Juhasz. Licensed for non-commercial use. See LICENSE. */

class CNetwork {
    constructor () {
        this.components = [];
        this.wires = [];
    }

    add_component (component) {
        if (component instanceof IComponent) {
            this.components.push(component);
        }
    }

    add_wire (wire) {
        if (wires instanceof CWire) {
            this.wires.push(wire);
        }
    }
};