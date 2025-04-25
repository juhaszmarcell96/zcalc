/* Copyright (C) 2025 Marcell Juhasz. Licensed for non-commercial use. See LICENSE. */

import { CTwoPole } from "./two_pole";
import { ComponentType, Unit } from "../../defines";

export class CResistor extends CTwoPole {
    constructor (x, y, img) {
        super(x, y, img);
        this.type = ComponentType.resistor;
        this.resistance = 0.0;
        this.unit = Unit.base;
    }

    get_property () {
        return `{"properties":[{"name":"type","editable":false,"type":"string","value":"resistor"},{"name":"value","editable":true,"type":"number","value":"${this.resistance}"},{"name":"unit","editable":true,"value":"ohm","type":"enum","options":["mega ohm","kilo ohm","ohm","milli ohm"]}]}`
    }

    set_property (property) {
        console.log('ERROR : "set_property" function not overloaded');
    }

    serialize (id) {
        let json_data = "{";
        json_data += '"i":' + id.toString()                        + ","; // id
        json_data += '"t":' + this.type.toString()                 + ","; // type
        json_data += '"n0":' + this.terminals.T1.nodeId.toString() + ","; // node 0
        json_data += '"n1":' + this.terminals.T2.nodeId.toString() + ","; // node 1
        json_data += '"r":' + this.resistance.toString()           + ","; // resistance
        json_data += '"u":' + this.unit.toString()                 + ","; // unit
        json_data += '}';
        return json_data;
    }
};

/*
{
    "properties": [
        {
            "name":"type",
            "editable":false,
            "type":"string",
            "value":"resistor"
        },
        {
            "name":"value",
            "editable":true,
            "type":"number",
            "value":"100"
        },
        {
            "name":"unit",
            "editable":true,
            "value":"ohm",
            "type":"enum",
            "options":[
                "mega ohm",
                "kilo ohm",
                "ohm",
                "milli ohm"
            ]
        }
    ]
}
*/