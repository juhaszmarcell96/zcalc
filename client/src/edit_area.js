/* Copyright (C) 2025 Marcell Juhasz. Licensed for non-commercial use. See LICENSE. */

import { scale, Colors } from "./defines";
import { CButton } from "./controls/button";
import { CTextBox } from "./controls/text_box";

export class CEditArea {
    constructor (x, y, canvas, scene) {
        this.canvas = canvas;
        this.context = canvas.getContext('2d');
        this.scene = scene;
        this.x = x;
        this.y = y;

        this.offset_y = 0;

        canvas.addEventListener("wheel", (event) => {
            /*
            if (event.deltaY < 0) { // scroll up
                this.offset_y += 20;
            }
            else { // scroll down
                this.offset_y -= 20;
            }
            */
        
            this.redraw();
            event.preventDefault();
        });

        const x_offset = 10 * scale;
        const y_offset = 10 * scale;
        const button_w = this.canvas.width - 2 * x_offset;
        const button_h = 40 * scale;
        this.apply_button = new CButton(x_offset, this.canvas.height - button_h - y_offset, button_w, button_h, Colors.green, "apply");

        this.textbox = new CTextBox(0, 0, this.w, this.h, Colors.grey, "0123456789 ABC abc %$#! ohm");

        this.visible = false;

        canvas.addEventListener('click', (event) => {
            if (this.visible) {
                const x = event.clientX - this.x;
                const y = event.clientY - this.y - this.offset_y;
                if (this.apply_button.is_inside(x, y)) {
                    //this.scene.components.push(new CResistor(50 * scale, 200 * scale, this.resistor_img));
                    this.visible = false;
                    this.redraw();
                }
                event.preventDefault();
            }
        });
    }

    populate (properties) {
        console.log(properties);
        this.visible = true;
        this.redraw();
    }

    redraw () {
        this.context.clearRect(0, 0, this.canvas.width, this.canvas.height);
        if (this.visible) {
            this.context.translate(0, this.offset_y);
            this.textbox.draw(this.context);
            this.apply_button.draw(this.context);
            this.context.translate(0, -this.offset_y);
        }
    }
};