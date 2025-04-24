/* Copyright (C) 2025 Marcell Juhasz. Licensed for non-commercial use. See LICENSE. */

import { CFourPole } from "./four_pole";
import { ComponentType } from "../../defines";

export class CCoupledInductor extends CFourPole {
    constructor (x, y, img) {
        super(x, y, img);
        this.type = ComponentType.coupled_inductor;
    }
};