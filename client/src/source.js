/* Copyright (C) 2025 Marcell Juhasz. Licensed for non-commercial use. See LICENSE. */

import { IComponent } from "./component";
import { scale, Colors } from "./defines";
import { CTerminal } from "./terminal";

export class CSource extends IComponent {
    constructor (x, y) {
        super(x, y, 200 * scale, 40 * scale);
        this.terminals = {
            L1: new CTerminal(-this.w / 2 +  20 * scale, -this.h / 2 + 20 * scale, Colors.l1),
            L2: new CTerminal(-this.w / 2 +  60 * scale, -this.h / 2 + 20 * scale, Colors.l2),
            L3: new CTerminal(-this.w / 2 + 100 * scale, -this.h / 2 + 20 * scale, Colors.l3),
            N : new CTerminal(-this.w / 2 + 140 * scale, -this.h / 2 + 20 * scale, Colors.n),
            PE: new CTerminal(-this.w / 2 + 180 * scale, -this.h / 2 + 20 * scale, Colors.pe)
        }
    }

    draw (context) {
        context.translate(this.x + this.w / 2, this.y + this.h / 2);
        context.rotate(this.angle * Math.PI / 2);
        context.beginPath();
        context.rect(-this.w / 2, -this.h / 2, this.w, this.h);
        context.fillStyle = Colors.light_grey;
        context.fill();
        context.lineWidth = this.lineWidth;
        context.strokeStyle = Colors.black;
        context.stroke();
        context.closePath();
        this.draw_terminals(context);
        context.rotate(-1 * this.angle * Math.PI / 2);
        context.translate(-(this.x + this.w / 2), -(this.y + this.h / 2));
    }

    do_stuff () {
        return;
    }
}