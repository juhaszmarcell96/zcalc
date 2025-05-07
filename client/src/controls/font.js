/* Copyright (C) 2025 Marcell Juhasz. Licensed for non-commercial use. See LICENSE. */

import { CChar } from "./char";

export class CFont {
    constructor () {
        this.supported_characters = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ<>.,/?\\;:'\"{}[]-_=+()*&^%$#@!~| ";
        // digits
        //this.digits = [];
        //for (let i = 0; i < 10; ++i) {
        //    this.digits.push(new Image());
        //    this.digits[i].src = `assets/font/${i}.png`;
        //    this.digits[i].onerror = function() { console.error(`failed to load digit ${i} image`); };
        //}
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
        //switch (c) {
        //    case '0' : { return new CChar(this.digits[0]); }
        //    case '1' : { return new CChar(this.digits[1]); }
        //    case '2' : { return new CChar(this.digits[2]); }
        //    case '3' : { return new CChar(this.digits[3]); }
        //    case '4' : { return new CChar(this.digits[4]); }
        //    case '5' : { return new CChar(this.digits[5]); }
        //    case '6' : { return new CChar(this.digits[6]); }
        //    case '7' : { return new CChar(this.digits[7]); }
        //    case '8' : { return new CChar(this.digits[8]); }
        //    case '9' : { return new CChar(this.digits[9]); }
        //    case '' : { return new CChar(this.digits[9]); }
        //    default  : { console.error(`unsupported character ${c}`); return null; }
        //}
    }
};