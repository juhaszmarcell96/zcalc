/* Copyright (C) 2025 Marcell Juhasz. Licensed for non-commercial use. See LICENSE. */

import { CFourPole } from "./four_pole";
import { ComponentType, UnitPrefix, UnitPrefixMap, ReverseUnitPrefixMap } from "../../defines";

export class CGyrator extends CFourPole {
    constructor (x, y, img) {
        super(x, y, img);
        this.type = ComponentType.gyrator;
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
            n2: this.terminals.T3.nodeId,
            n3: this.terminals.T4.nodeId,
            r: this.resistance,
            u: this.prefix
        };
    }
};