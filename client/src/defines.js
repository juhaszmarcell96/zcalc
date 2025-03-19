/* Copyright (C) 2025 Marcell Juhasz. Licensed for non-commercial use. See LICENSE. */

export const scale = 1;
export const grid_size = 5;
export const zoomFactor = 1.1;

export const Colors = {
    l1         : 'rgba(  0,   0,   0, 1)',
    l2         : 'rgba(139,  69,  19, 1)',
    l3         : 'rgba(192, 192, 192, 1)',
    n          : 'rgba( 30, 144, 255, 1)',
    pe         : 'rgba( 50, 205,  50, 1)',
    grey       : 'rgba(192, 192, 192, 1)',
    black      : 'rgba(  0,   0,   0, 1)',
    yellow     : 'rgba(255, 215,   0, 1)',
    dark_grey  : 'rgba(100, 100, 100, 1)',
    light_grey : 'rgba(230, 230, 230, 1)',
    red        : 'rgba(178,  34,  34, 1)',
    white      : 'rgba(255, 255, 255, 1)',
}

export const Mode = {
    Visual: "Visual",
    Wire: "Wire",
    Delete: "Delete",
    Move: "Move"
};

export const WireType = {
    L: 0,
    N: 1,
    PE: 2
};

export const TerminalState = {
    None : "None",
    L1 : "L1",
    L2 : "L2",
    L3 : "L3",
    N  : "N",
    PE : "PE",
    Virtual : "Virtual" /* virtual wire state, overrides None state but gets overridden by every other state -> to see whether wires with None states are connected */
};

export class Coordinates {
    constructor (x, y) {
        this.x = x;
        this.y = y;
    }
};