class CContactor extends IComponent {
    constructor (x, y) {
        super(x, y);
        this.w = 36 * grid_size;
        this.h = 55 * grid_size;
        this.A1   = new CTerminal(this.x +  1 * grid_size, this.y -  4 * grid_size, color_l1);
        this.L1   = new CTerminal(this.x +  7 * grid_size, this.y -  4 * grid_size, color_l3);
        this.L2   = new CTerminal(this.x + 13 * grid_size, this.y -  4 * grid_size, color_l3);
        this.L3   = new CTerminal(this.x + 19 * grid_size, this.y -  4 * grid_size, color_l3);
        this.NO13 = new CTerminal(this.x + 25 * grid_size, this.y -  4 * grid_size, color_l3);
        this.A2   = new CTerminal(this.x + 31 * grid_size, this.y -  4 * grid_size, color_n );

        this.T1   = new CTerminal(this.x +  7 * grid_size, this.y + 55 * grid_size, color_l3);
        this.T2   = new CTerminal(this.x + 13 * grid_size, this.y + 55 * grid_size, color_l3);
        this.T3   = new CTerminal(this.x + 19 * grid_size, this.y + 55 * grid_size, color_l3);
        this.NO14 = new CTerminal(this.x + 25 * grid_size, this.y + 55 * grid_size, color_l3);

        this.NO53 = new CTerminal(this.x +  3 * grid_size, this.y + 10 * grid_size, color_l3);
        this.NC61 = new CTerminal(this.x + 11 * grid_size, this.y + 10 * grid_size, color_l3);
        this.NC71 = new CTerminal(this.x + 20 * grid_size, this.y + 10 * grid_size, color_l3);
        this.NO83 = new CTerminal(this.x + 28 * grid_size, this.y + 10 * grid_size, color_l3);

        this.NO54 = new CTerminal(this.x +  3 * grid_size, this.y + 20 * grid_size, color_l3);
        this.NC62 = new CTerminal(this.x + 11 * grid_size, this.y + 20 * grid_size, color_l3);
        this.NC72 = new CTerminal(this.x + 20 * grid_size, this.y + 20 * grid_size, color_l3);
        this.NO84 = new CTerminal(this.x + 28 * grid_size, this.y + 20 * grid_size, color_l3);

        this.NC98 = new CTerminal(this.x +  3 * grid_size, this.y + 40 * grid_size, color_l3);
        this.NC97 = new CTerminal(this.x + 11 * grid_size, this.y + 40 * grid_size, color_l3);
        this.NO95 = new CTerminal(this.x + 20 * grid_size, this.y + 40 * grid_size, color_l3);
        this.NO96 = new CTerminal(this.x + 28 * grid_size, this.y + 40 * grid_size, color_l3);

        this.prev_closed = false;
        this.closed = false;
    }

    draw (context) {
        context.beginPath();
        context.rect(this.x, this.y, this.w, this.h);
        context.fillStyle = 'rgba(230, 230, 230, 1)'; /* grey */
        context.fill();
        context.lineWidth = (grid_size / 5) * 2;
        context.strokeStyle = '#000000';
        context.font = '10pt Kremlin Pro Web';
        context.fillStyle = '#000000';
        context.fillText("A1", this.x +  4 * grid_size - context.measureText("A1").width / 2, this.y +  3 * grid_size);
        context.fillText("L1", this.x +  9 * grid_size - context.measureText("L1").width / 2, this.y +  3 * grid_size);
        context.fillText("L2", this.x + 15 * grid_size - context.measureText("L2").width / 2, this.y +  3 * grid_size);
        context.fillText("L3", this.x + 21 * grid_size - context.measureText("L3").width / 2, this.y +  3 * grid_size);
        context.fillText("NO13", this.x + 27 * grid_size - context.measureText("NO13").width / 2, this.y +  3 * grid_size);
        context.fillText("A2", this.x + 33 * grid_size - context.measureText("A2").width / 2, this.y +  3 * grid_size);
        context.fillText("T1", this.x +  9 * grid_size - context.measureText("T1").width / 2, this.y + 54 * grid_size);
        context.fillText("T2", this.x + 15 * grid_size - context.measureText("T2").width / 2, this.y + 54 * grid_size);
        context.fillText("T3", this.x + 21 * grid_size - context.measureText("T3").width / 2, this.y + 54 * grid_size);
        context.fillText("NO14", this.x + 27 * grid_size - context.measureText("NO14").width / 2, this.y + 54 * grid_size);
        if (this.closed) {
            context.fillText("on", this.x + 17 * grid_size - context.measureText("on").width / 2, this.y + 34 * grid_size);
        }
        else {
            context.fillText("off", this.x + 17 * grid_size - context.measureText("off").width / 2, this.y + 34 * grid_size);
        }
        context.font = '10pt Kremlin Pro Web';
        context.fillText("NO53", this.x +  5 * grid_size - context.measureText("NO53").width / 2, this.y +  9 * grid_size);
        context.fillText("NC61", this.x + 13 * grid_size - context.measureText("NC61").width / 2, this.y +  9 * grid_size);
        context.fillText("NC71", this.x + 22 * grid_size - context.measureText("NC71").width / 2, this.y +  9 * grid_size);
        context.fillText("NO83", this.x + 30 * grid_size - context.measureText("NO83").width / 2, this.y +  9 * grid_size);
        context.fillText("NO54", this.x +  5 * grid_size - context.measureText("NO54").width / 2, this.y + 27 * grid_size);
        context.fillText("NC62", this.x + 13 * grid_size - context.measureText("NC62").width / 2, this.y + 27 * grid_size);
        context.fillText("NC72", this.x + 22 * grid_size - context.measureText("NC72").width / 2, this.y + 27 * grid_size);
        context.fillText("NO84", this.x + 30 * grid_size - context.measureText("NO84").width / 2, this.y + 27 * grid_size);
        context.fillText("NC98", this.x +  5 * grid_size - context.measureText("NC98").width / 2, this.y + 39 * grid_size);
        context.fillText("NC97", this.x + 13 * grid_size - context.measureText("NC97").width / 2, this.y + 39 * grid_size);
        context.fillText("NO95", this.x + 22 * grid_size - context.measureText("NO95").width / 2, this.y + 39 * grid_size);
        context.fillText("NO96", this.x + 30 * grid_size - context.measureText("NO96").width / 2, this.y + 39 * grid_size);
        context.stroke();
        context.closePath();
        this.A1.draw(context);
        this.A2.draw(context);

        this.L1.draw(context);
        this.L2.draw(context);
        this.L3.draw(context);
        this.NO13.draw(context);

        this.T1.draw(context);
        this.T2.draw(context);
        this.T3.draw(context);
        this.NO14.draw(context);

        this.NO53.draw(context);
        this.NC61.draw(context);
        this.NC71.draw(context);
        this.NO83.draw(context);

        this.NO54.draw(context);
        this.NC62.draw(context);
        this.NC72.draw(context);
        this.NO84.draw(context);

        this.NC98.draw(context);
        this.NC97.draw(context);

        this.NO95.draw(context);
        this.NO96.draw(context);
    }

    is_inside(pos_x, pos_y) {
        return pos_x > this.x && pos_x < this.x + this.w && pos_y < this.y + this.h && pos_y > this.y;
    }

    get_terminal_at (pos_x, pos_y) {
        if (this.A1.is_inside(pos_x, pos_y)) return this.A1;
        if (this.A2.is_inside(pos_x, pos_y)) return this.A2;
        if (this.L1.is_inside(pos_x, pos_y)) return this.L1;
        if (this.L2.is_inside(pos_x, pos_y)) return this.L2;
        if (this.L3.is_inside(pos_x, pos_y)) return this.L3;
        if (this.NO13.is_inside(pos_x, pos_y)) return this.NO13;

        if (this.T1.is_inside(pos_x, pos_y)) return this.T1;
        if (this.T2.is_inside(pos_x, pos_y)) return this.T2;
        if (this.T3.is_inside(pos_x, pos_y)) return this.T3;
        if (this.NO14.is_inside(pos_x, pos_y)) return this.NO14;

        if (this.NO53.is_inside(pos_x, pos_y)) return this.NO53;
        if (this.NC61.is_inside(pos_x, pos_y)) return this.NC61;
        if (this.NC71.is_inside(pos_x, pos_y)) return this.NC71;
        if (this.NO83.is_inside(pos_x, pos_y)) return this.NO83;

        if (this.NO54.is_inside(pos_x, pos_y)) return this.NO54;
        if (this.NC62.is_inside(pos_x, pos_y)) return this.NC62;
        if (this.NC72.is_inside(pos_x, pos_y)) return this.NC72;
        if (this.NO84.is_inside(pos_x, pos_y)) return this.NO84;

        if (this.NC98.is_inside(pos_x, pos_y)) return this.NC98;
        if (this.NC97.is_inside(pos_x, pos_y)) return this.NC97;
        if (this.NO95.is_inside(pos_x, pos_y)) return this.NO95;
        if (this.NO96.is_inside(pos_x, pos_y)) return this.NO96;
        return null;
    }

    do_stuff () {
        return;
    }

    get_terminals () {
        return [this.A1, this.A2, this.L1, this.L2, this.L3, this.T1, this.T2, this.T3,
                this.NO53, this.NC61, this.NC71, this.NO83, this.NO54, this.NC62, this.NC72, this.NO84,
                this.NC98, this.NC97, this.NO95, this.NO96, this.NO13, this.NO14];
    }

    propagate () {
        var something_changed = false;
        if (this.closed == false) {
            if (this.NC61.state != this.NC62.state) {
                if (this.NC61.state == TerminalState.None) {
                    this.NC61.state = this.NC62.state;
                    something_changed = true;
                }
                if (this.NC62.state == TerminalState.None) {
                    this.NC62.state = this.NC61.state;
                    something_changed = true;
                }
            }
            if (this.NC71.state != this.NC72.state) {
                if (this.NC71.state == TerminalState.None) {
                    this.NC71.state = this.NC72.state;
                    something_changed = true;
                }
                if (this.NC72.state == TerminalState.None) {
                    this.NC72.state = this.NC71.state;
                    something_changed = true;
                }
            }
            if (this.NC98.state != this.NC97.state) {
                if (this.NC98.state == TerminalState.None) {
                    this.NC98.state = this.NC97.state;
                    something_changed = true;
                }
                if (this.NC97.state == TerminalState.None) {
                    this.NC97.state = this.NC98.state;
                    something_changed = true;
                }
            }
        }
        else {
            if (this.L1.state != this.T1.state) {
                if (this.L1.state == TerminalState.None) {
                    this.L1.state = this.T1.state;
                    something_changed = true;
                }
                if (this.T1.state == TerminalState.None) {
                    this.T1.state = this.L1.state;
                    something_changed = true;
                }
            }
            if (this.L2.state != this.T2.state) {
                if (this.L2.state == TerminalState.None) {
                    this.L2.state = this.T2.state;
                    something_changed = true;
                }
                if (this.T2.state == TerminalState.None) {
                    this.T2.state = this.L2.state;
                    something_changed = true;
                }
            }
            if (this.L3.state != this.T3.state) {
                if (this.L3.state == TerminalState.None) {
                    this.L3.state = this.T3.state;
                    something_changed = true;
                }
                if (this.T3.state == TerminalState.None) {
                    this.T3.state = this.L3.state;
                    something_changed = true;
                }
            }
            if (this.NO13.state != this.NO14.state) {
                if (this.NO13.state == TerminalState.None) {
                    this.NO13.state = this.NO14.state;
                    something_changed = true;
                }
                if (this.NO14.state == TerminalState.None) {
                    this.NO14.state = this.NO13.state;
                    something_changed = true;
                }
            }
            if (this.NO53.state != this.NO54.state) {
                if (this.NO53.state == TerminalState.None) {
                    this.NO53.state = this.NO54.state;
                    something_changed = true;
                }
                if (this.NO54.state == TerminalState.None) {
                    this.NO54.state = this.NO53.state;
                    something_changed = true;
                }
            }
            if (this.NO83.state != this.NO84.state) {
                if (this.NO83.state == TerminalState.None) {
                    this.NO83.state = this.NO84.state;
                    something_changed = true;
                }
                if (this.NO84.state == TerminalState.None) {
                    this.NO84.state = this.NO83.state;
                    something_changed = true;
                }
            }
            if (this.NO95.state != this.NO96.state) {
                if (this.NO95.state == TerminalState.None) {
                    this.NO95.state = this.NO96.state;
                    something_changed = true;
                }
                if (this.NO96.state == TerminalState.None) {
                    this.NO96.state = this.NO95.state;
                    something_changed = true;
                }
            }
        }
        return something_changed;
    }

    reset_terminals () {
        this.A1.state = TerminalState.None;
        this.A2.state = TerminalState.None;
        this.L1.state = TerminalState.None;
        this.L2.state = TerminalState.None;
        this.L3.state = TerminalState.None;
        this.NO13.state = TerminalState.None;

        this.T1.state = TerminalState.None;
        this.T2.state = TerminalState.None;
        this.T3.state = TerminalState.None;
        this.NO14.state = TerminalState.None;

        this.NO53.state = TerminalState.None;
        this.NC61.state = TerminalState.None;
        this.NC71.state = TerminalState.None;
        this.NO83.state = TerminalState.None;

        this.NO54.state = TerminalState.None;
        this.NC62.state = TerminalState.None;
        this.NC72.state = TerminalState.None;
        this.NO84.state = TerminalState.None;

        this.NC98.state = TerminalState.None;
        this.NC97.state = TerminalState.None;
        this.NO95.state = TerminalState.None;
        this.NO96.state = TerminalState.None;
    }

    check_terminals () {
        //console.log("yo");
        if (((this.A1.state == TerminalState.L1) || (this.A1.state == TerminalState.L2) || (this.A1.state == TerminalState.L3)) && (this.A2.state == TerminalState.N)) {
            if (this.closed == false) {
                this.closed = true;
                return true;
            }
            return false;
        }
        if (this.closed == true) {
            this.closed = false;
            return true;
        }
        return false;
    }
};