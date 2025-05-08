/* Copyright (C) 2025 Marcell Juhasz. Licensed for non-commercial use. See LICENSE. */

import { CTwoPole } from "./two_pole";
import { ComponentType, UnitPrefix, UnitPrefixMap, ReverseUnitPrefixMap } from "../../defines";

export class CVoltageSource extends CTwoPole {
    constructor (x, y, img) {
        super(x, y, img);
        this.type = ComponentType.voltage_source;
        this.voltage = 0.0;
        this.prefix = UnitPrefix.base;
        this.phase = 0.0;
        this.frequency = 0.0; // DC
    }

    get_property () {
        return {
            value: this.voltage,
            unit: "V",
            prefix: ReverseUnitPrefixMap[this.prefix],
            phase: this.phase,
            phaseUnit: "rad",
            frequency: this.frequency,
            frequencyUnit: "rad/s"
        }
    }

    set_property (property) {
        if (typeof property !== 'object' || property === null) {
            console.error("invalid property: not an object");
            return;
        }
        // check for errors so that no partial fill happens
        if (!('value' in property)) { return "missing 'value' in property"; }
        if (!('phase' in property)) { return "missing 'phase' in property"; }
        if (!('frequency' in property)) { return "missing 'frequency' in property"; }
        if ('unit' in property) {
            if (property.unit != "V" && property.unit != "volt") {
                return "unit must be 'volt' or 'V'";
            }
        }
        if ('phaseUnit' in property) {
            if (property.phaseUnit != "rad") {
                return "phase unit must be 'rad'";
            }
        }
        if ('frequencyUnit' in property) {
            if (property.frequencyUnit != "rad/s") {
                return "frequency unit must be 'rad/s'";
            }
        }
        let prefix = this.prefix;
        if ('prefix' in property) {
            prefix = UnitPrefixMap[property.prefix];
            if (prefix === undefined) {
                return "invalid prefix";
            }
        }
        const value = parseFloat(property.value);
        if (isNaN(value)) { return "invalid voltage value"; }
        const phase = parseFloat(property.phase);
        if (isNaN(phase)) { return "invalid phase value"; }
        const frequency = parseFloat(property.frequency);
        if (isNaN(frequency)) { return "invalid frequency value"; }

        // error check passed, set parameters
        this.voltage = value;
        this.prefix = prefix;
        this.phase = phase;
        this.frequency = frequency;

        return "success"
    }

    serialize (id) {
        return {
            i: id,
            t: this.type,
            n0: this.terminals.T1.nodeId,
            n1: this.terminals.T2.nodeId,
            v: this.voltage,
            u: this.prefix,
            p: this.phase,
            f: this.frequency
        };
    }
};