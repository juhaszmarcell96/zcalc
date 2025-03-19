/* Copyright (C) 2025 Marcell Juhasz. Licensed for non-commercial use. See LICENSE. */

import { scale, grid_size, TerminalState, Colors } from "./defines";

export class CTerminal {
    constructor (x, y, fillStyle) {
        this.w = 20 * scale;
        this.h = 20 * scale;
        this.set_middle(x, y);
        this.snap_to_grid(x, y);
        this.lineWidth = 2;
        this.fillStyle = fillStyle;
        this.state = TerminalState.None;
    }

    snap_to_grid () {
        const modulo_x = this.x % grid_size;
        const modulo_y = this.y % grid_size;
        if (modulo_x > grid_size / 2) {
            this.x += grid_size - modulo_x;
        }
        else {
            this.x -= modulo_x;
        }
        if (modulo_y > grid_size / 2) {
            this.y += grid_size - modulo_y;
        }
        else {
            this.y -= modulo_y;
        }
    }

    move (dx, dy) {
        this.x += dx;
        this.y += dy;
    }

    set_middle (x, y) {
        this.x = x - this.w / 2.0;
        this.y = y - this.h / 2.0;
    }

    scale (s) {
        this.x += (this.w - this.w * s) / 2.0;
        this.y += (this.h - this.h * s) / 2.0;
        this.w *= s;
        this.h *= s;
    }

    get_middle_x () {
        return this.x + this.w / 2.0;
    }

    get_middle_y () {
        return this.y + this.h / 2.0;
    }

    draw (context) {
        context.beginPath();
        context.rect(this.x, this.y, this.w, this.h);
        context.fillStyle = this.fillStyle;
        context.fill();
        context.lineWidth = this.lineWidth;
        context.strokeStyle = Colors.black;
        context.stroke();
        context.closePath();
    }

    is_inside(pos_x, pos_y) {
        return (pos_x > this.x) && (pos_x < (this.x + this.w)) && (pos_y < (this.y + this.h)) && (pos_y > this.y);
    }
};