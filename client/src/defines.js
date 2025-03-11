const grid_size = 5;
const zoomFactor = 1.1;
const color_l1 = 'rgba(  0,   0,   0, 1)';
const color_l2 = 'rgba(139,  69,  19, 1)';
const color_l3 = 'rgba(192, 192, 192, 1)';
const color_n  = 'rgba( 30, 144, 255, 1)';
const color_pe = 'rgba( 50, 205,  50, 1)';

const Mode = {
    Visual: "Visual",
    Wire: "Wire",
    Delete: "Delete",
    Move: "Move"
};

const TerminalState = {
    None : "None",
    L1 : "L1",
    L2 : "L2",
    L3 : "L3",
    N  : "N",
    PE : "PE",
    Virtual : "Virtual" /* virtual wire state, overrides None state but gets overridden by every other state -> to see whether wires with None states are connected */
};