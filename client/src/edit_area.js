/* Copyright (C) 2025 Marcell Juhasz. Licensed for non-commercial use. See LICENSE. */

import { scale, Colors } from "./defines";
import { CButton } from "./controls/button";

export class CEditArea {
    constructor (x, y, canvas, scene, editAreaInput) {
        this.canvas = canvas;
        this.context = canvas.getContext('2d');
        this.scene = scene;
        this.x = x;
        this.y = y;

        this.offset_x = 10 * scale;
        this.offset_y = 10 * scale;
        const button_h = 40 * scale;
        const content_w = this.canvas.width - 2 * this.offset_x;

        this.editAreaInput = editAreaInput;
        this.editAreaInput.style.position = 'absolute';
        this.editAreaInput.style.left = this.x + this.offset_x + 'px';
        this.editAreaInput.style.top = this.y + this.offset_y + 'px';
        this.editAreaInput.style.width = content_w + 'px';
        this.editAreaInput.style.height = (this.canvas.height - button_h - 4 * this.offset_y) + 'px';

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

        this.apply_button = new CButton(0, this.canvas.height - button_h - 2 * this.offset_y, content_w, button_h, Colors.green, "apply");

        this.visible = false;

        canvas.addEventListener('click', (event) => {
            if (this.visible) {
                const x = event.clientX - this.x - this.offset_x;
                const y = event.clientY - this.y - this.offset_y;
                if (this.apply_button.is_inside(x, y)) {
                    //this.scene.components.push(new CResistor(50 * scale, 200 * scale, this.resistor_img));
                    this.visible = false;
                    this.editAreaInput.value = "";
                    this.redraw();
                }
                event.preventDefault();
            }
        });
    }

    populate (properties) {
        console.log(properties);
        this.editAreaInput.value = JSON.stringify(properties, null, "  ");
        this.visible = true;
        this.redraw();
    }

    redraw () {
        this.context.clearRect(0, 0, this.canvas.width, this.canvas.height);
        if (this.visible) {
            this.context.translate(this.offset_x, this.offset_y);
            this.apply_button.draw(this.context);
            this.context.translate(-this.offset_x, -this.offset_y);
        }
    }
};