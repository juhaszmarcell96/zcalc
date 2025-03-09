class CTimeSwitch extends IComponent {
    constructor (x, y) {
        super(x, y);
        this.w = 14 * grid_size;
        this.h = 20 * grid_size;
        this.T1  = new CTerminal(this.x +  0 * grid_size, this.y -  4 * grid_size, color_l1);
        this.T2  = new CTerminal(this.x +  5 * grid_size, this.y -  4 * grid_size, color_l3);
        this.T3  = new CTerminal(this.x + 10 * grid_size, this.y -  4 * grid_size, color_n);
        this.T4  = new CTerminal(this.x +  0 * grid_size, this.y + 20 * grid_size, color_l3);
        this.T5  = new CTerminal(this.x +  5 * grid_size, this.y + 20 * grid_size, color_l3);
        this.T6  = new CTerminal(this.x + 10 * grid_size, this.y + 20 * grid_size, color_l3);
        this.prev_closed = false;
        this.closed = false;
    }

    draw (context) {
        context.beginPath();
        context.rect(this.x, this.y, this.w, this.h);
        context.fillStyle = 'rgba(230, 230, 230, 1)'; /* grey */
        context.fill();
        context.moveTo(this.x + 7 * grid_size, this.y + 0 * grid_size);
        context.lineTo(this.x + 7 * grid_size, this.y + 8 * grid_size);
        context.moveTo(this.x + 6 * grid_size, this.y + 6 * grid_size);
        context.lineTo(this.x + 7 * grid_size, this.y + 8 * grid_size);
        context.moveTo(this.x + 8 * grid_size, this.y + 6 * grid_size);
        context.lineTo(this.x + 7 * grid_size, this.y + 8 * grid_size);
        
        context.moveTo(this.x + 2 * grid_size, this.y + 20 * grid_size);
        context.lineTo(this.x + 2 * grid_size, this.y + 11 * grid_size);
        context.moveTo(this.x + 2 * grid_size, this.y + 11 * grid_size);
        context.lineTo(this.x + 4 * grid_size, this.y + 11 * grid_size);
        if (this.closed == true) {
            context.moveTo(this.x +  4 * grid_size, this.y + 11 * grid_size);
            context.lineTo(this.x +  8 * grid_size, this.y +  8 * grid_size);
        }
        else {
            context.moveTo(this.x +  4 * grid_size, this.y + 11 * grid_size);
            context.lineTo(this.x +  8 * grid_size, this.y + 14 * grid_size);
        }
        context.moveTo(this.x + 7 * grid_size, this.y + 20 * grid_size);
        context.lineTo(this.x + 7 * grid_size, this.y + 13 * grid_size);
        context.moveTo(this.x + 12 * grid_size, this.y + 20 * grid_size);
        context.lineTo(this.x + 12 * grid_size, this.y + 8 * grid_size);
        context.moveTo(this.x + 8 * grid_size, this.y + 8 * grid_size);
        context.lineTo(this.x + 12 * grid_size, this.y + 8 * grid_size);
        context.lineWidth = (grid_size / 5) * 2;
        context.strokeStyle = '#000000';
        context.stroke();
        context.closePath();
        this.T1.draw(context);
        this.T2.draw(context);
        this.T3.draw(context);
        this.T4.draw(context);
        this.T5.draw(context);
        this.T6.draw(context);
    }

    is_inside(pos_x, pos_y) {
        return pos_x > this.x && pos_x < this.x + this.w && pos_y < this.y + this.h && pos_y > this.y;
    }

    get_terminal_at (pos_x, pos_y) {
        if (this.T1.is_inside(pos_x, pos_y)) return this.T1;
        if (this.T2.is_inside(pos_x, pos_y)) return this.T2;
        if (this.T3.is_inside(pos_x, pos_y)) return this.T3;
        if (this.T4.is_inside(pos_x, pos_y)) return this.T4;
        if (this.T5.is_inside(pos_x, pos_y)) return this.T5;
        if (this.T6.is_inside(pos_x, pos_y)) return this.T6;
        return null;
    }

    do_stuff () {
        //setTimeout(timeElapsed, 5000)
        this.closed = false;
        return;
    }

    get_terminals () {
        return [this.T1, this.T2, this.T3, this.T4, this.T5, this.T6];
    }

    propagate () {
        if ((this.T1.state != TerminalState.None) && (this.T1.state != TerminalState.L1) && (this.T1.state != TerminalState.L2) && (this.T1.state != TerminalState.L3)) {
            alert("CTimeSwitch : ERROR : T1 of time relay connected incorrectly");
            return false;
        }
        if ((this.T3.state != TerminalState.None) && (this.T3.state != TerminalState.N)) {
            alert("CTimeSwitch : ERROR : T3 of time relay connected incorrectly");
            return false;
        }
        if (this.closed == false) {
            /* T4 is connected to T5 */
            if (this.T4.state == this.T5.state) return false;
            if (this.T4.state == TerminalState.None) {
                this.T4.state = this.T5.state;
                return true;
            }
            if (this.T5.state == TerminalState.None) {
                this.T5.state = this.T4.state;
                return true;
            }
            alert("CTimeSwitch : short circuit between " + this.T4.state + " and " + this.T5.state);
        }
        else {
            /* T4 is connected to T6 */
            if (this.T4.state == this.T6.state) return false;
            if (this.T4.state == TerminalState.None) {
                this.T4.state = this.T5.state;
                return true;
            }
            if (this.T6.state == TerminalState.None) {
                this.T6.state = this.T4.state;
                return true;
            }
            alert("CTimeSwitch : short circuit between " + this.T4.state + " and " + this.T6.state);
        }
        return false;
    }

    reset_terminals () {
        this.T1.state = TerminalState.None;
        this.T2.state = TerminalState.None;
        this.T3.state = TerminalState.None;
        this.T4.state = TerminalState.None;
        this.T5.state = TerminalState.None;
        this.T6.state = TerminalState.None;
    }

    check_terminals () {
        if (((this.T1.state == TerminalState.L1) || (this.T1.state == TerminalState.L2) || (this.T1.state == TerminalState.L3)) &&
             (this.T3.state == TerminalState.N) &&
            ((this.T2.state == TerminalState.L1) || (this.T2.state == TerminalState.L2) || (this.T2.state == TerminalState.L3))) {
            if ((this.closed == false) && (this.prev_closed == false)) {
                this.closed = true;
                this.prev_closed = true;
                setTimeout(timeElapsed, 5000);
                return true;
            }
            return false;
        }
        if (((this.T1.state == TerminalState.L1) || (this.T1.state == TerminalState.L2) || (this.T1.state == TerminalState.L3)) && (this.T3.state == TerminalState.N)) {
            this.prev_closed = false;
            return false;
        }
        if (this.closed == true) {
            this.closed = false;
            this.prev_closed = false;
            return true;
        }
        return false;
    }
};