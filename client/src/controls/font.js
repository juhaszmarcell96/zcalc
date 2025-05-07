/* Copyright (C) 2025 Marcell Juhasz. Licensed for non-commercial use. See LICENSE. */

import { CChar } from "./char";

export class CFont {
    constructor () {
        this.supported_characters = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ<>.,/?\\;:'\"{}[]-_=+()*&^%$#@!~| ";
        // letters
        this.letters = new Array(126);
        for (var i = 0; i < this.letters.length; i++) {
            if (this.supported_characters.includes(String.fromCharCode(i))) {
                this.letters[i] = new Image();
                this.letters[i].src = `assets/font/${i}.png`;
                this.letters[i].onerror = function() { console.error(`failed to load ASCII character ${i} image`); };
            }
        }
    }

    get (c) {
        if (this.supported_characters.includes(c)) {
            return new CChar(this.letters[c.charCodeAt(0)]);
        }
        else {
            console.error(`unsupported character ${c}`);
            return null;
        }
    }
};