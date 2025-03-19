/* Copyright (C) 2025 Marcell Juhasz. Licensed for non-commercial use. See LICENSE. */

import { IComponent } from "../../component";
import { Colors, scale } from "../../defines";
import { CTerminal } from "../../terminal";

export class C3PhaseMotor extends IComponent {
    constructor (x, y) {
        super(x, y, 160 * scale, 80 * scale);
        this.terminals = {
            U1: new CTerminal(-this.w / 2 +  30 * scale, -this.h / 2 +        - 10 * scale, Colors.l3),
            V1: new CTerminal(-this.w / 2 +  70 * scale, -this.h / 2 +        - 10 * scale, Colors.l3),
            W1: new CTerminal(-this.w / 2 + 110 * scale, -this.h / 2 +        - 10 * scale, Colors.l3),
            W2: new CTerminal(-this.w / 2 +  30 * scale, -this.h / 2 + this.h + 10 * scale, Colors.l3),
            U2: new CTerminal(-this.w / 2 +  70 * scale, -this.h / 2 + this.h + 10 * scale, Colors.l3),
            V2: new CTerminal(-this.w / 2 + 110 * scale, -this.h / 2 + this.h + 10 * scale, Colors.l3),
            PE: new CTerminal(-this.w / 2 + -10 * scale, -this.h / 2 +        + 40 * scale, Colors.pe)
        }

        this.error = false;
        this.on = false;
        this.forward = false;
        this.delta = false;
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
        context.font = '14pt Kremlin Pro Web';
        context.fillStyle = Colors.black;
        context.fillText("U1", this.terminals.U1.get_middle_x() - 8 * scale, this.terminals.U1.get_middle_y() + 30 * scale);
        context.fillText("V1", this.terminals.V1.get_middle_x() - 8 * scale, this.terminals.V1.get_middle_y() + 30 * scale);
        context.fillText("W1", this.terminals.W1.get_middle_x() - 8 * scale, this.terminals.W1.get_middle_y() + 30 * scale);
        context.fillText("W2", this.terminals.W2.get_middle_x() - 8 * scale, this.terminals.W2.get_middle_y() - 20 * scale);
        context.fillText("U2", this.terminals.U2.get_middle_x() - 8 * scale, this.terminals.U2.get_middle_y() - 20 * scale);
        context.fillText("V2", this.terminals.V2.get_middle_x() - 8 * scale, this.terminals.V2.get_middle_y() - 20 * scale);
        let msg = "";
        if (this.error == true) {
            msg = "error";
        }
        else {
            if (this.on == false) {
                msg = "off";
            }
            else {
                if (this.forward == false) {
                    msg = "rev";
                }
                else {
                    msg = "fwd";
                }
                if (this.delta == false) {
                    msg = "star";
                }
                else {
                    msg = "delta";
                }
            }
        }
        context.fillText(msg, 40 * scale - context.measureText(msg).width / 2, this.terminals.PE.get_middle_y() + 5 * scale);
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