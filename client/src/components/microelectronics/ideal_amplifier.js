/* Copyright (C) 2025 Marcell Juhasz. Licensed for non-commercial use. See LICENSE. */

import { IComponent } from "../../component";
import { Colors, scale } from "../../defines";
import { CTerminal } from "../../terminal";
import { ComponentType } from "../../defines";

export class CIdealAmplifier extends IComponent {
    constructor (x, y, img) {
        super(x, y, 140 * scale, 90 * scale);
        this.type = ComponentType.ideal_amplifier;

        const terminal_0_x = -this.w / 2 - 10 * scale;
        const terminal_0_y = -this.h / 2 + 10 * scale;

        const terminal_1_x = -this.w / 2 - 10 * scale;
        const terminal_1_y =  this.h / 2 - 10 * scale;

        const terminal_2_x =  this.w / 2 + 10 * scale;
        const terminal_2_y =             +  5 * scale;

        const terminal_3_x =            +  5 * scale;
        const terminal_3_y = this.h / 2 +  5 * scale;

        this.terminals = {
            T1: new CTerminal(this, terminal_0_x, terminal_0_y, Colors.l3),
            T2: new CTerminal(this, terminal_1_x, terminal_1_y, Colors.l3),
            T3: new CTerminal(this, terminal_2_x, terminal_2_y, Colors.l3),
            T4: new CTerminal(this, terminal_3_x, terminal_3_y, Colors.l3)
        }

        this.img = img
    }

    draw (context) {
        context.translate(this.x + this.w / 2, this.y + this.h / 2);
        context.drawImage(this.img, -this.w / 2, -this.h / 2, this.w, this.h);
        this.draw_terminals(context);
        context.translate(-(this.x + this.w / 2), -(this.y + this.h / 2));
    }

    rotate () {
        return;
    }

    do_stuff () {
        // nothing to do
    }
};