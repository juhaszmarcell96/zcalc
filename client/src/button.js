/* Copyright (C) 2025 Marcell Juhasz. Licensed for non-commercial use. See LICENSE. */

import { Colors, scale } from "./defines";

export class CButton {
    constructor (x, y, w, h, fillStyle, text) {
        this.x = x;
        this.y = y;
        this.w = w;
        this.h = h;
        this.fillStyle = fillStyle;
        this.text = text;
    }

    draw (context) {
        context.beginPath();
        context.roundRect(this.x, this.y, this.w, this.h, [10 * scale]);
        context.fillStyle = this.fillStyle;
        context.fill();
        context.lineWidth = 2 * scale;
        context.strokeStyle = Colors.black;
        context.font = '12pt "Courier New"';
        context.fillStyle = Colors.white;
        var lines = this.text.split('\n');
        for (var i = 0; i<lines.length; i++) {
            context.fillText(lines[i], this.x + this.w / 2 - (lines[i].length / 2) * 9.5 * scale, this.y + (i + 1) * 25 * scale);
        }
        context.stroke();
        context.closePath();
    }

    is_inside(pos_x, pos_y) {
        return pos_x > this.x && pos_x < this.x + this.w && pos_y < this.y + this.h && pos_y > this.y;
    }
};