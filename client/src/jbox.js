/* Copyright (C) 2025 Marcell Juhasz. Licensed for non-commercial use. See LICENSE. */

class CJunctionBox extends IComponent {
    constructor (x, y) {
        super(x, y, 70 * scale, 70 * scale);
        this.terminals = {
            T1: new CTerminal(-this.w / 2 + 15 * scale, -this.h / 2 + 15 * scale, Colors.l3),
            T2: new CTerminal(-this.w / 2 + 35 * scale, -this.h / 2 + 35 * scale, Colors.l3),
            T3: new CTerminal(-this.w / 2 + 55 * scale, -this.h / 2 + 55 * scale, Colors.l3)
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

    rotate () {
        return;
    }

    do_stuff () {
        return;
    }
};