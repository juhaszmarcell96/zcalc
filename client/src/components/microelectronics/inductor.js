/* Copyright (C) 2025 Marcell Juhasz. Licensed for non-commercial use. See LICENSE. */

import { CTwoPole } from "./two_pole";
import { ComponentType, UnitPrefix, UnitPrefixMap, ReverseUnitPrefixMap } from "../../defines";

export class CInductor extends CTwoPole {
    constructor (x, y, img) {
        super(x, y, img);
        this.type = ComponentType.inductor;
        this.inductance = 0.0;
        this.prefix = UnitPrefix.base;
    }

    get_property () {
        return {value:this.inductance, unit:"H", prefix:ReverseUnitPrefixMap[this.prefix]}
    }

    set_property (property) {
        if (typeof property !== 'object' || property === null) {
            console.error("invalid property: not an object");
            return;
        }
        // check for errors so that no partial fill happens
        if (!('value' in property)) { return "missing 'value' in property"; }
        if ('unit' in property) {
            if (property.unit != "henry" && property.unit != "H") {
                return "unit must be 'henry' or 'H'";
            }
        }
        let prefix = this.prefix;
        if ('prefix' in property) {
            prefix = UnitPrefixMap[property.prefix];
            if (prefix === undefined) {
                return "invalid prefix";
            }
        }
        const inductance = parseFloat(property.value);
        if (isNaN(inductance)) { return "invalid inductance value"; }
        if (inductance < 0.0) { return "inductance cannot be negative..."; }

        // error check passed, set parameters
        this.inductance = inductance;
        this.prefix = prefix;

        return "success"
    }

    serialize (id) {
        return {
            i: id,
            t: this.type,
            n0: this.terminals.T1.nodeId,
            n1: this.terminals.T2.nodeId,
            l: this.inductance,
            u: this.prefix
        };
    }
};