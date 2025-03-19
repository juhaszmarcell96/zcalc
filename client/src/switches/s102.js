/* Copyright (C) 2025 Marcell Juhasz. Licensed for non-commercial use. See LICENSE. */

import { IComponent } from "../../component";
import { Colors, scale } from "../../defines";
import { CTerminal } from "../../terminal";

export class CSwitch102 extends IComponent {
    constructor (x, y) {
        super(x, y, 90 * scale, 90 * scale);
        this.terminals = {
            T1: new CTerminal(-this.w / 2          - 10 * scale, -this.h / 2 + 30 * scale, Colors.l3),
            T2: new CTerminal(-this.w / 2          - 10 * scale, -this.h / 2 + 70 * scale, Colors.l3),
            T3: new CTerminal(-this.w / 2 + this.w + 10 * scale, -this.h / 2 + 30 * scale, Colors.l3),
            T4: new CTerminal(-this.w / 2 + this.w + 10 * scale, -this.h / 2 + 70 * scale, Colors.l3)
        }
        this.closed = false;
    }

    draw (context) {
        context.translate(this.x + this.w / 2, this.y + this.h / 2);
        context.rotate(this.angle * Math.PI / 2);
        context.beginPath();
        context.rect(-this.w / 2, -this.h / 2, this.w, this.h);
        context.fillStyle = Colors.light_grey;
        context.fill();
        context.moveTo(-this.w / 2 +  0 * scale, -this.h / 2 + 30 * scale);
        context.lineTo(-this.w / 2 + 35 * scale, -this.h / 2 + 30 * scale);
        context.moveTo(-this.w / 2 +  0 * scale, -this.h / 2 + 70 * scale);
        context.lineTo(-this.w / 2 + 35 * scale, -this.h / 2 + 70 * scale);
        if (this.closed == false) {
            context.moveTo(-this.w / 2 + 35 * scale, -this.h / 2 + 30 * scale);
            context.lineTo(-this.w / 2 + 65 * scale, -this.h / 2 + 20 * scale);
            context.moveTo(-this.w / 2 + 35 * scale, -this.h / 2 + 70 * scale);
            context.lineTo(-this.w / 2 + 65 * scale, -this.h / 2 + 60 * scale);
        }
        else {
            context.moveTo(-this.w / 2 + 35 * scale, -this.h / 2 + 30 * scale);
            context.lineTo(-this.w / 2 + 65 * scale, -this.h / 2 + 30 * scale);
            context.moveTo(-this.w / 2 + 35 * scale, -this.h / 2 + 70 * scale);
            context.lineTo(-this.w / 2 + 65 * scale, -this.h / 2 + 70 * scale);
        }
        context.moveTo(-this.w / 2 + 65 * scale, -this.h / 2 + 30 * scale);
        context.lineTo(-this.w / 2 + 90 * scale, -this.h / 2 + 30 * scale);
        context.moveTo(-this.w / 2 + 65 * scale, -this.h / 2 + 70 * scale);
        context.lineTo(-this.w / 2 + 90 * scale, -this.h / 2 + 70 * scale);
        context.moveTo(-this.w / 2 + 50 * scale, -this.h / 2 + 35 * scale);
        context.lineTo(-this.w / 2 + 50 * scale, -this.h / 2 + 40 * scale);
        context.moveTo(-this.w / 2 + 50 * scale, -this.h / 2 + 45 * scale);
        context.lineTo(-this.w / 2 + 50 * scale, -this.h / 2 + 50 * scale);
        context.moveTo(-this.w / 2 + 50 * scale, -this.h / 2 + 45 * scale);
        context.lineTo(-this.w / 2 + 50 * scale, -this.h / 2 + 60 * scale);
        context.lineWidth = this.lineWidth;
        context.strokeStyle = Colors.black;
        context.stroke();
        context.closePath();
        this.draw_terminals(context);
        context.rotate(-1 * this.angle * Math.PI / 2);
        context.translate(-(this.x + this.w / 2), -(this.y + this.h / 2));
    }

    rotate () {
        return;
    }

    do_stuff () {
        this.closed = !this.closed;
    }
};