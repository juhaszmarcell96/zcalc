/* Copyright (C) 2025 Marcell Juhasz. Licensed for non-commercial use. See LICENSE. */

class Canvas {
    constructor (x, y, w, h, canvas) {
        this.x = x;
        this.y = y;
        this.w = w;
        this.h = h;
        this.canvas = canvas;
    }
    Clear () {
        this.canvas.clearRect(this.x, this.y, this.w, this.h);
    }
    DrawLine (x0, y0, x1, y1, width, color) {
        if (x0 > (this.x + this.w) && x1 > (this.x + this.w)) { return; }
        if (y0 > (this.y + this.h) && y1 > (this.y + this.h)) { return; }
        if (x0 < this.x && x1 < this.x) { return; }
        if (y0 < this.y && y1 < this.y) { return; }
        this.canvas.beginPath();
        this.canvas.moveTo(this.x + x0, this.y + y0);
        this.canvas.lineTo(this.x + x1, this.y + y1);
        this.canvas.lineWidth = width;
        this.canvas.strokeStyle = color;
        this.canvas.stroke();
        this.canvas.closePath();
    }
    DrawRectangle (x, y, w, h, fill, width, color) {
        if (x > (this.x + this.w)) { return; }
        if (y > (this.y + this.h)) { return; }
        if (x + w < this.x) { return; }
        if (y + h < this.y) { return; }
        this.canvas.beginPath();
        this.canvas.rect(this.x + x, this.y + y, w, h);
        this.canvas.fillStyle = fill;
        this.canvas.fill();
        this.canvas.lineWidth = width;
        this.canvas.strokeStyle = color;
        this.canvas.stroke();
        this.canvas.closePath();
    }
    DrawRoundRectangle (x, y, w, h, r, fill, width, color) {
        if (x > (this.x + this.w)) { return; }
        if (y > (this.y + this.h)) { return; }
        if (x + w < this.x) { return; }
        if (y + h < this.y) { return; }
        this.canvas.beginPath();
        this.canvas.roundRect(this.x + x, this.y + y, w, h, [r]);
        this.canvas.fillStyle = fill;
        this.canvas.fill();
        this.canvas.lineWidth = width;
        this.canvas.strokeStyle = color;
        this.canvas.stroke();
        this.canvas.closePath();
    }
    DrawCircle (x, y, r, fill, width, color) {
        if (x > this.x + this.w) { return; }
        if (x + 2 * r < this.x) { return; }
        if (y > this.y + this.h) { return; }
        if (y + w * r < this.y) { return; }
        this.canvas.beginPath();
        this.canvas.arc(this.x + x + r, this.y + y + r, r, 0, 2 * Math.PI);
        this.canvas.fillStyle = fill;
        this.canvas.fill();
        this.canvas.lineWidth = width;
        this.canvas.strokeStyle = color;
        this.canvas.stroke();
        this.canvas.closePath();
    }
    DrawText (x, y, w, text, fill, color) {
        if (x > this.x + this.w) { return; }
        if (x + w < this.x) { return; }
        if (y > this.y + this.h) { return; }
        if (y + w < this.y) { return; }
        this.canvas.beginPath();
        this.canvas.fillText(text, this.x + x, this.y + y, w);
        this.canvas.fillStyle = fill;
        this.canvas.fill();
        this.canvas.strokeStyle = color;
        this.canvas.stroke();
        this.canvas.closePath();
    }
}

export { Canvas }