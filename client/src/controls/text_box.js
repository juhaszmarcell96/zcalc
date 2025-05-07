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
        this.text = Array.from(text).map(c => this.font.get(c));
        this.rawText = Array.from(text);

        // State tracking
        this.cursorIndex = this.rawText.length; // position between letters
        this.selectionStart = null;
        this.selectionEnd = null;

        this.dragging = false;
    }

    draw(context) {
        const charWidth = 6 * scale * 2;
        const charHeight = 11 * scale * 2;

        context.save();
        context.imageSmoothingEnabled = false;
        context.translate(this.x, this.y);
        
        // Draw box
        context.fillStyle = this.fillStyle;
        context.strokeStyle = Colors.black;
        context.lineWidth = 2 * scale;
        context.beginPath();
        context.rect(0, 0, this.w, this.h);
        context.fill();
        context.stroke();

        // Highlight selection
        if (this.selectionStart !== null && this.selectionEnd !== null) {
            const [start, end] = [this.selectionStart, this.selectionEnd].sort((a, b) => a - b);
            context.fillStyle = "rgba(100, 100, 255, 0.5)";
            context.fillRect(start * charWidth, 0, (end - start) * charWidth, charHeight);
        }

        // Draw text
        for (let i = 0; i < this.text.length; i++) {
            this.text[i].draw(context, i * charWidth, 0, charWidth, charHeight);
        }

        // Draw cursor
        context.strokeStyle = Colors.black;
        context.beginPath();
        context.moveTo(this.cursorIndex * charWidth, 0);
        context.lineTo(this.cursorIndex * charWidth, charHeight);
        context.stroke();

        context.restore();
    }

    is_inside(pos_x, pos_y) {
        return pos_x > this.x && pos_x < this.x + this.w && pos_y > this.y && pos_y < this.y + this.h;
    }

    getCursorIndexFromMouse(x) {
        const localX = x - this.x;
        const charWidth = 6 * scale * 2;
        return Math.min(this.rawText.length, Math.floor(localX / charWidth));
    }

    onMouseDown(x, y) {
        if (!this.is_inside(x, y)) { return false; }
        this.dragging = true;
        this.cursorIndex = this.getCursorIndexFromMouse(x);
        this.selectionStart = this.cursorIndex;
        this.selectionEnd = null;
        return true;
    }

    onMouseMove(x, y) {
        if (!this.dragging) { return false; }
        this.selectionEnd = this.getCursorIndexFromMouse(x);
        this.cursorIndex = this.selectionEnd;
        return true;
    }

    onMouseUp() {
        if (!this.dragging) { return false; }
        this.dragging = false;
        if (this.selectionStart === this.selectionEnd) {
            this.selectionStart = null;
            this.selectionEnd = null;
        }
        return true;
    }

    onKeyDown(e) {
        if (e.key.length === 1 && !e.ctrlKey && !e.metaKey) {
            // Handle text input
            this.removeSelection(); // Remove selected text if any
            this.rawText.splice(this.cursorIndex, 0, e.key);
            this.text.splice(this.cursorIndex, 0, this.font.get(e.key));
            this.cursorIndex++;
        } else if (e.key === "Backspace") {
            if (this.selectionStart !== null) {
                this.removeSelection();
            } else if (this.cursorIndex > 0) {
                this.rawText.splice(this.cursorIndex - 1, 1);
                this.text.splice(this.cursorIndex - 1, 1);
                this.cursorIndex--;
            }
        } else if (e.key === "Delete") {
            if (this.selectionStart !== null) {
                this.removeSelection();
            } else if (this.cursorIndex < this.rawText.length) {
                this.rawText.splice(this.cursorIndex, 1);
                this.text.splice(this.cursorIndex, 1);
            }
        } else if (e.key === "ArrowLeft") {
            if (this.cursorIndex > 0) this.cursorIndex--;
            this.clearSelection();
        } else if (e.key === "ArrowRight") {
            if (this.cursorIndex < this.rawText.length) this.cursorIndex++;
            this.clearSelection();
        }
    }

    removeSelection() {
        if (this.selectionStart === null || this.selectionEnd === null) return;
        const [start, end] = [this.selectionStart, this.selectionEnd].sort((a, b) => a - b);
        this.rawText.splice(start, end - start);
        this.text.splice(start, end - start);
        this.cursorIndex = start;
        this.selectionStart = null;
        this.selectionEnd = null;
    }

    clearSelection() {
        this.selectionStart = null;
        this.selectionEnd = null;
    }
};