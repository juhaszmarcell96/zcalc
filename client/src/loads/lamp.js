/* Copyright (C) 2025 Marcell Juhasz. Licensed for non-commercial use. See LICENSE. */

import { IComponent } from "../../component";
import { Colors, scale } from "../../defines";
import { CTerminal } from "../../terminal";

export class CLamp extends IComponent {
    constructor (x, y) {
        super(x, y, 60 * scale, 60 * scale);
        this.terminals = {
            L : new CTerminal(this, -30 * scale, 50 * scale, Colors.l1),
            N : new CTerminal(this,   0 * scale, 50 * scale, Colors.n),
            PE: new CTerminal(this,  30 * scale, 50 * scale, Colors.pe)
        }
        this.on = false;
    }

    draw (context) {
        context.translate(this.x + this.w / 2, this.y + this.h / 2);
        context.rotate(this.angle * Math.PI / 2);
        context.beginPath();
        let radius = this.w / 2;
        context.arc(0, 0, radius, 0, 2 * Math.PI);
        if (this.on == false) {
            context.fillStyle = Colors.grey;
        }
        else {
            context.fillStyle = Colors.yellow;
        }
        context.fill();
        const line_offset = 20 * scale;
        context.moveTo(-line_offset, -line_offset);
        context.lineTo( line_offset,  line_offset);
        context.moveTo(-line_offset,  line_offset);
        context.lineTo( line_offset, -line_offset);
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
};