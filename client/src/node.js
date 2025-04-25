/* Copyright (C) 2025 Marcell Juhasz. Licensed for non-commercial use. See LICENSE. */

export class CNode {
    constructor () {
        this.terminals = [];
    }

    append (terminal) {
        this.terminals.push(terminal);
    }

    empty () {
        return this.terminals.length == 0;
    }

    merge_if_same_node (node) {
        if (!(node instanceof CNode)) {
            throw new Error("expected a node...");
        }
        for (const own_terminal of this.terminals) {
            for (const other_terminal of node.terminals) {
                if (own_terminal.is_connected_to(other_terminal)) {
                    this.terminals.push(...node.terminals);
                    node.terminals = [];
                    return true;
                }
            }
        }
        return false;
    }
};