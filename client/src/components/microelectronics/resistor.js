/* Copyright (C) 2025 Marcell Juhasz. Licensed for non-commercial use. See LICENSE. */

import { CTwoPole } from "./two_pole";
import { ComponentType } from "../../defines";

export class CResistor extends CTwoPole {
    constructor (x, y, img) {
        super(x, y, img);
        this.type = ComponentType.resistor;
        this.resistance = 0;
    }

    serialize (id) {
        let json_data = "{";
        json_data += '"i":' + id.toString()                        + ","; // id
        json_data += '"t":' + this.type.toString()                 + ","; // type
        json_data += '"n0":' + this.terminals.T1.nodeId.toString() + ","; // node 0
        json_data += '"n1":' + this.terminals.T2.nodeId.toString() + ","; // node 1
        json_data += '"r":' + this.resistance.toString()           + ","; // resistance
        json_data += '"u":' + this.resistance.toString()           + ","; // unit
        json_data += '}';
        return json_data;
    }
};