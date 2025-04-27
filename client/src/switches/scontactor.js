/* Copyright (C) 2025 Marcell Juhasz. Licensed for non-commercial use. See LICENSE. */

import { IComponent } from "../../component";
import { Colors, scale } from "../../defines";
import { CTerminal } from "../../terminal";

export class CContactor extends IComponent {
    constructor (x, y) {
        super(x, y, 180 * scale, 275 * scale);
        this.terminals = {
            A1  : new CTerminal(this, -this.w / 2 +  15 * scale, -this.h / 2 -  10 * scale, Colors.l1),
            L1  : new CTerminal(this, -this.w / 2 +  45 * scale, -this.h / 2 -  10 * scale, Colors.l3),
            L2  : new CTerminal(this, -this.w / 2 +  75 * scale, -this.h / 2 -  10 * scale, Colors.l3),
            L3  : new CTerminal(this, -this.w / 2 + 105 * scale, -this.h / 2 -  10 * scale, Colors.l3),
            NO13: new CTerminal(this, -this.w / 2 + 135 * scale, -this.h / 2 -  10 * scale, Colors.l3),
            A2  : new CTerminal(this, -this.w / 2 + 165 * scale, -this.h / 2 -  10 * scale, Colors.n ),

            T1  : new CTerminal(this, -this.w / 2 +  45 * scale, -this.h / 2 + 285 * scale, Colors.l3),
            T2  : new CTerminal(this, -this.w / 2 +  75 * scale, -this.h / 2 + 285 * scale, Colors.l3),
            T3  : new CTerminal(this, -this.w / 2 + 105 * scale, -this.h / 2 + 285 * scale, Colors.l3),
            NO14: new CTerminal(this, -this.w / 2 + 135 * scale, -this.h / 2 + 285 * scale, Colors.l3),

            NO53: new CTerminal(this, -this.w / 2 +  25 * scale, -this.h / 2 +  60 * scale, Colors.l3),
            NC61: new CTerminal(this, -this.w / 2 +  65 * scale, -this.h / 2 +  60 * scale, Colors.l3),
            NC71: new CTerminal(this, -this.w / 2 + 110 * scale, -this.h / 2 +  60 * scale, Colors.l3),
            NO83: new CTerminal(this, -this.w / 2 + 150 * scale, -this.h / 2 +  60 * scale, Colors.l3),

            NO54: new CTerminal(this, -this.w / 2 +  25 * scale, -this.h / 2 + 110 * scale, Colors.l3),
            NC62: new CTerminal(this, -this.w / 2 +  65 * scale, -this.h / 2 + 110 * scale, Colors.l3),
            NC72: new CTerminal(this, -this.w / 2 + 110 * scale, -this.h / 2 + 110 * scale, Colors.l3),
            NO84: new CTerminal(this, -this.w / 2 + 150 * scale, -this.h / 2 + 110 * scale, Colors.l3),

            NC98: new CTerminal(this, -this.w / 2 +  25 * scale, -this.h / 2 + 210 * scale, Colors.l3),
            NC97: new CTerminal(this, -this.w / 2 +  65 * scale, -this.h / 2 + 210 * scale, Colors.l3),
            NO95: new CTerminal(this, -this.w / 2 + 110 * scale, -this.h / 2 + 210 * scale, Colors.l3),
            NO96: new CTerminal(this, -this.w / 2 + 150 * scale, -this.h / 2 + 210 * scale, Colors.l3)
        }

        this.prev_closed = false;
        this.closed = false;
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
        context.font = '10pt Kremlin Pro Web';
        context.fillStyle = Colors.black;
        context.fillText("A1"  , this.terminals.A1.get_middle_x()   -  8 * scale,   this.terminals.A1.get_middle_y()   + 30 * scale);
        context.fillText("L1"  , this.terminals.L1.get_middle_x()   -  8 * scale,   this.terminals.L1.get_middle_y()   + 30 * scale);
        context.fillText("L2"  , this.terminals.L2.get_middle_x()   -  8 * scale,   this.terminals.L2.get_middle_y()   + 30 * scale);
        context.fillText("L3"  , this.terminals.L3.get_middle_x()   -  8 * scale,   this.terminals.L3.get_middle_y()   + 30 * scale);
        context.fillText("NO13", this.terminals.NO13.get_middle_x() - 16 * scale,   this.terminals.NO13.get_middle_y() + 30 * scale);
        context.fillText("A2"  , this.terminals.A2.get_middle_x()   -  8 * scale,   this.terminals.A2.get_middle_y()   + 30 * scale);
        context.fillText("T1"  , this.terminals.T1.get_middle_x()   -  8 * scale,   this.terminals.T1.get_middle_y()   - 20 * scale);
        context.fillText("T2"  , this.terminals.T2.get_middle_x()   -  8 * scale,   this.terminals.T2.get_middle_y()   - 20 * scale);
        context.fillText("T3"  , this.terminals.T3.get_middle_x()   -  8 * scale,   this.terminals.T3.get_middle_y()   - 20 * scale);
        context.fillText("NO14", this.terminals.NO14.get_middle_x() - 16 * scale,   this.terminals.NO14.get_middle_y() - 20 * scale);
        if (this.closed) {
            context.fillText("on", -this.w / 2 + 85 * scale - context.measureText("on").width / 2, -this.h / 2 + 170 * scale);
        }
        else {
            context.fillText("off", -this.w / 2 + 85 * scale - context.measureText("off").width / 2, -this.h / 2 + 170 * scale);
        }
        context.font = '10pt Kremlin Pro Web';
        context.fillText("NO53", this.terminals.NO53.get_middle_x() - 16 * scale, this.terminals.NO53.get_middle_y() + 25 * scale);
        context.fillText("NC61", this.terminals.NC61.get_middle_x() - 16 * scale, this.terminals.NC61.get_middle_y() + 25 * scale);
        context.fillText("NC71", this.terminals.NC71.get_middle_x() - 16 * scale, this.terminals.NC71.get_middle_y() + 25 * scale);
        context.fillText("NO83", this.terminals.NO83.get_middle_x() - 16 * scale, this.terminals.NO83.get_middle_y() + 25 * scale);
        context.fillText("NO54", this.terminals.NO54.get_middle_x() - 16 * scale, this.terminals.NO54.get_middle_y() + 25 * scale);
        context.fillText("NC62", this.terminals.NC62.get_middle_x() - 16 * scale, this.terminals.NC62.get_middle_y() + 25 * scale);
        context.fillText("NC72", this.terminals.NC72.get_middle_x() - 16 * scale, this.terminals.NC72.get_middle_y() + 25 * scale);
        context.fillText("NO84", this.terminals.NO84.get_middle_x() - 16 * scale, this.terminals.NO84.get_middle_y() + 25 * scale);
        context.fillText("NC98", this.terminals.NC98.get_middle_x() - 16 * scale, this.terminals.NC98.get_middle_y() + 25 * scale);
        context.fillText("NC97", this.terminals.NC97.get_middle_x() - 16 * scale, this.terminals.NC97.get_middle_y() + 25 * scale);
        context.fillText("NO95", this.terminals.NO95.get_middle_x() - 16 * scale, this.terminals.NO95.get_middle_y() + 25 * scale);
        context.fillText("NO96", this.terminals.NO96.get_middle_x() - 16 * scale, this.terminals.NO96.get_middle_y() + 25 * scale);
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