/* Copyright (C) 2025 Marcell Juhasz. Licensed for non-commercial use. See LICENSE. */

export class CChar {
    constructor (img) {
        this.img = img;
    }

    draw (context, x, y, w, h) {
        context.drawImage(this.img, x, y, w, h);
    }
};