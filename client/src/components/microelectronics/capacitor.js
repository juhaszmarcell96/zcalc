/* Copyright (C) 2025 Marcell Juhasz. Licensed for non-commercial use. See LICENSE. */

import { CTwoPole } from "./two_pole";
import { ComponentType, UnitPrefix, UnitPrefixMap, ReverseUnitPrefixMap } from "../../defines";

export class CCapacitor extends CTwoPole {
    constructor (x, y, img) {
        super(x, y, img);
        this.type = ComponentType.capacitor;
        this.capacitance = 0.0;
        this.prefix = UnitPrefix.base;
    }

    get_property () {
        return {value:this.capacitance, unit:"F", prefix:ReverseUnitPrefixMap[this.prefix]}
    }

    set_property (property) {
        if (typeof property !== 'object' || property === null) {
            console.error("invalid property: not an object");
            return;
        }
        // check for errors so that no partial fill happens
        if (!('value' in property)) { return "missing 'value' in property"; }
        if ('unit' in property) {
            if (property.unit != "farad" && property.unit != "F") {
                return "unit must be 'farad' or 'F'";
            }
        }
        let prefix = this.prefix;
        if ('prefix' in property) {
            prefix = UnitPrefixMap[property.prefix];
            if (prefix === undefined) {
                return "invalid prefix";
            }
        }
        const capacitance = parseFloat(property.value);
        if (isNaN(capacitance)) { return "invalid capacitance value"; }
        if (capacitance < 0.0) { return "capacitance cannot be negative..."; }

        // error check passed, set parameters
        this.capacitance = capacitance;
        this.prefix = prefix;

        return "success"
    }

    serialize (id) {
        return {
            i: id,
            t: this.type,
            n0: this.terminals.T1.nodeId,
            n1: this.terminals.T2.nodeId,
            c: this.capacitance,
            u: this.prefix
        };
    }
};