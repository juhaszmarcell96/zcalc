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
    green      : 'rgba( 19, 124,  19, 1)',
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
    PE : "PE"
};

export class Coordinates {
    constructor (x, y) {
        this.x = x;
        this.y = y;
    }
};

export const ComponentType = {
    resistor: 0,
    capacitor: 1,
    inductor: 2,
    current_source: 3,
    voltage_source: 4,
    ammeter: 5,
    voltmeter: 6,
    current_controlled_current_source: 7,
    current_controlled_voltage_source: 8,
    voltage_controlled_current_source: 9,
    voltage_controlled_voltage_source: 10,
    gyrator: 11,
    ideal_amplifier: 12,
    ideal_transformer: 13,
    coupled_inductor: 14
};

export const UnitPrefix = {
    peta : 0,         // 1e15
    tera : 1,         // 1e12
    giga : 2,         // 1e9
    mega : 3,         // 1e6
    kilo : 4,         // 1e3
    hecto : 5,        // 1e2
    deka : 6,         // 1e1
    base: 7,          // 1e0
    deci : 8,         // 1e-1
    centi : 9,        // 1e-2
    milli : 10,       // 1e-3
    micro : 11,       // 1e-6
    nano : 12,        // 1e-9
    angstrom : 13,    // 1e-10
    pico : 14         // 1e-12
};

export const UnitPrefixMap = {
    "peta": UnitPrefix.peta, "P": UnitPrefix.peta,
    "tera": UnitPrefix.tera, "T": UnitPrefix.tera,
    "giga": UnitPrefix.giga, "G": UnitPrefix.giga,
    "mega": UnitPrefix.mega, "M": UnitPrefix.mega,
    "kilo": UnitPrefix.kilo, "k": UnitPrefix.kilo,
    "hecto": UnitPrefix.hecto, "h": UnitPrefix.hecto,
    "deka": UnitPrefix.deka, "da": UnitPrefix.deka,
    "base": UnitPrefix.base, "": UnitPrefix.base,
    "deci": UnitPrefix.deci, "d": UnitPrefix.deci,
    "centi": UnitPrefix.centi, "c": UnitPrefix.centi,
    "milli": UnitPrefix.milli, "m": UnitPrefix.milli,
    "micro": UnitPrefix.micro, "u": UnitPrefix.micro,
    "nano": UnitPrefix.nano, "n": UnitPrefix.nano,
    "angstrom": UnitPrefix.angstrom, "a": UnitPrefix.angstrom,
    "pico": UnitPrefix.pico, "p": UnitPrefix.pico
};

export const ReverseUnitPrefixMap = {
    [UnitPrefix.peta]: "P",
    [UnitPrefix.tera]: "T",
    [UnitPrefix.giga]: "G",
    [UnitPrefix.mega]: "M",
    [UnitPrefix.kilo]: "k",
    [UnitPrefix.hecto]: "h",
    [UnitPrefix.deka]: "da",
    [UnitPrefix.base]: "",
    [UnitPrefix.deci]: "d",
    [UnitPrefix.centi]: "c",
    [UnitPrefix.milli]: "m",
    [UnitPrefix.micro]: "u",
    [UnitPrefix.nano]: "n",
    [UnitPrefix.angstrom]: "a",
    [UnitPrefix.pico]: "p"
};