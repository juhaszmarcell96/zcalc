/* Copyright (C) 2025 Marcell Juhasz. Licensed for non-commercial use. See LICENSE. */

import { grid_size, Coordinates, ComponentType } from "./defines";

export class IComponent {
    constructor (x, y, w, h) {
        this.x = x - (x % grid_size);
        this.y = y - (y % grid_size);
        this.w = w
        this.h = h
        this.lineWidth = 2;
        this.terminals = {};
        this.move_offset_x = 0;
        this.move_offset_y = 0;
        
        this.angle = 0;

        this.type = ComponentType.resistor;
    }

    get_type () {
        return this.type;
    }

    draw_terminals(context) {
        for (const [key, value] of Object.entries(this.terminals)) {
            value.draw(context);
        }
    }

    draw (context) {
        console.log('ERROR : "draw" function not overloaded');
    }

    rotate () {
        this.angle += 1;
        if (this.angle == 4) {
            this.angle = 0;
        }
    }

    rotate_back () {
        this.angle -= 1;
        if (this.angle == -1) {
            this.angle = 3;
        }
    }

    is_inside(pos_x, pos_y) {
        let x = this.x;
        let y = this.y;
        let w = this.w;
        let h = this.h;
        if (this.angle == 1 || this.angle == 3) {
            x = x + w / 2 - h / 2;
            y = y + h / 2 - w / 2;
            w = h;
            h = this.w;
        }
        return pos_x > x && pos_x < x + w && pos_y < y + h && pos_y > y;
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
        for (const [key, value] of Object.entries(this.terminals)) {
            value.snap_to_grid();
        }
    }

    move(dx, dy) {
        this.x += dx;
        this.y += dy;
    }

    global_to_local (x, y) {
        const centerX = this.x + this.w / 2;
        const centerY = this.y + this.h / 2;
        const localX = x - centerX;
        const localY = y - centerY;
        const unrotatedX = localX * Math.cos(-this.angle * Math.PI / 2) - localY * Math.sin(-this.angle * Math.PI / 2);
        const unrotatedY = localX * Math.sin(-this.angle * Math.PI / 2) + localY * Math.cos(-this.angle * Math.PI / 2);
        return [ unrotatedX, unrotatedY ];
    }

    local_to_global (x, y) {
        const centerX = this.x + this.w / 2;
        const centerY = this.y + this.h / 2;
        const rotatedX = x * Math.cos(this.angle * Math.PI / 2) - y * Math.sin(this.angle * Math.PI / 2);
        const rotatedY = x * Math.sin(this.angle * Math.PI / 2) + y * Math.cos(this.angle * Math.PI / 2);
        return [rotatedX + centerX, rotatedY + centerY];
    }

    get_terminal_at (pos_x, pos_y) {
        const [ unrotatedX, unrotatedY ] = this.global_to_local(pos_x, pos_y);
        for (const [key, value] of Object.entries(this.terminals)) {
            if (value.is_inside(unrotatedX, unrotatedY)) {
                const [ x, y ] = this.local_to_global(value.get_middle_x(), value.get_middle_y());
                return new Coordinates (x, y);
            }
        }
        return null;
    }

    do_stuff () {
        console.log('ERROR : "do_stuff" function not overloaded');
    }

    get_terminals () {
        return this.terminals;
    }
};