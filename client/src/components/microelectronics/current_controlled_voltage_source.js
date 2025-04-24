/* Copyright (C) 2025 Marcell Juhasz. Licensed for non-commercial use. See LICENSE. */

import { CTwoPole } from "./two_pole";
import { ComponentType } from "../../defines";

export class CCurrentControlledVoltageSource extends CTwoPole {
    constructor (x, y, img) {
        super(x, y, img);
        this.type = ComponentType.current_controlled_voltage_source;
    }
};