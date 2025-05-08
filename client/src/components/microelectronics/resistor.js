/* Copyright (C) 2025 Marcell Juhasz. Licensed for non-commercial use. See LICENSE. */

import { CTwoPole } from "./two_pole";
import { ComponentType, UnitPrefix, UnitPrefixMap, ReverseUnitPrefixMap } from "../../defines";

export class CResistor extends CTwoPole {
    constructor (x, y, img) {
        super(x, y, img);
        this.type = ComponentType.resistor;
        this.resistance = 0.0;
        this.prefix = UnitPrefix.base;
    }

    get_property () {
        return {value:this.resistance, unit:"ohm", prefix:ReverseUnitPrefixMap[this.prefix]}
    }

    set_property (property) {
        if (typeof property !== 'object' || property === null) {
            console.error("invalid property: not an object");
            return;
        }
        // check for errors so that no partial fill happens
        if (!('value' in property)) { return "missing 'value' in property"; }
        if ('unit' in property) {
            if (property.unit != "ohm" && property.unit != "Ω") {
                return "unit must be 'ohm' or 'Ω'";
            }
        }
        let prefix = this.prefix;
        if ('prefix' in property) {
            prefix = UnitPrefixMap[property.prefix];
            if (prefix === undefined) {
                return "invalid prefix";
            }
        }
        const resistance = parseFloat(property.value);
        if (isNaN(resistance)) { return "invalid resistance value"; }
        if (resistance < 0.0) { return "resistance cannot be negative..."; }

        // error check passed, set parameters
        this.resistance = resistance;
        this.prefix = prefix;

        return "success"
    }

    serialize (id) {
        return {
            i: id,
            t: this.type,
            n0: this.terminals.T1.nodeId,
            n1: this.terminals.T2.nodeId,
            r: this.resistance,
            u: ReverseUnitPrefixMap[this.prefix]
        };
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