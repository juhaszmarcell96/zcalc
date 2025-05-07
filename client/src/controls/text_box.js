/* Copyright (C) 2025 Marcell Juhasz. Licensed for non-commercial use. See LICENSE. */

import { Colors, scale } from "../defines";
import { CFont } from "./font";

export class CTextBox {
    constructor (x, y, w, h, fillStyle, text) {
        this.x = x;
        this.y = y;
        this.w = w;
        this.h = h;
        this.fillStyle = fillStyle;
        this.font = new CFont();
        this.text = [];
        for (let i = 0; i < text.length; i++) {
            this.text.push(this.font.get(text[i]));
        }
    }

    draw (context) {
        context.imageSmoothingEnabled = false
        context.translate(this.x, this.y);
        context.rect(this.x, this.y, this.w, this.h);
        context.fillStyle = this.fillStyle;
        context.lineWidth = 2 * scale;
        context.strokeStyle = Colors.black;
        context.fill();
        context.stroke();
        for (var i = 0; i < this.text.length; i++) {
            this.text[i].draw(context, 6 * i * scale * 2, 0, 5 * scale * 2, 11 * scale * 2);
        }
        context.translate(-this.x, -this.y);
    }

    is_inside(pos_x, pos_y) {
        return pos_x > this.x && pos_x < this.x + this.w && pos_y < this.y + this.h && pos_y > this.y;
    }
};