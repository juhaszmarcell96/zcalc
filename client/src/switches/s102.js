class CSwitch102 extends IComponent {
    constructor (x, y) {
        super(x, y);
        this.w = 16 * grid_size;
        this.h = 16 * grid_size;
        this.T1  = new CTerminal(this.x -  4 * grid_size, this.y +  2 * grid_size, color_l3);
        this.T2  = new CTerminal(this.x -  4 * grid_size, this.y + 10 * grid_size, color_l3);
        this.T3  = new CTerminal(this.x + 16 * grid_size, this.y +  2 * grid_size, color_l3);
        this.T4  = new CTerminal(this.x + 16 * grid_size, this.y + 10 * grid_size, color_l3);
        this.closed = false;
    }

    draw (context) {
        context.beginPath();
        context.rect(this.x, this.y, this.w, this.h);
        context.fillStyle = 'rgba(230, 230, 230, 1)'; /* grey */
        context.fill();
        context.moveTo(this.x + 0 * grid_size, this.y + 4 * grid_size);
        context.lineTo(this.x + 5 * grid_size, this.y + 4 * grid_size);
        context.moveTo(this.x + 0 * grid_size, this.y + 12 * grid_size);
        context.lineTo(this.x + 5 * grid_size, this.y + 12 * grid_size);
        if (this.closed == false) {
            context.moveTo(this.x +  5 * grid_size, this.y + 4 * grid_size);
            context.lineTo(this.x + 11 * grid_size, this.y + 2 * grid_size);
            context.moveTo(this.x +  5 * grid_size, this.y + 12 * grid_size);
            context.lineTo(this.x + 11 * grid_size, this.y + 10 * grid_size);
        }
        else {
            context.moveTo(this.x +  5 * grid_size, this.y + 4 * grid_size);
            context.lineTo(this.x + 11 * grid_size, this.y + 4 * grid_size);
            context.moveTo(this.x +  5 * grid_size, this.y + 12 * grid_size);
            context.lineTo(this.x + 11 * grid_size, this.y + 12 * grid_size);
        }
        context.moveTo(this.x + 11 * grid_size, this.y + 4 * grid_size);
        context.lineTo(this.x + 16 * grid_size, this.y + 4 * grid_size);
        context.moveTo(this.x + 11 * grid_size, this.y + 12 * grid_size);
        context.lineTo(this.x + 16 * grid_size, this.y + 12 * grid_size);
        context.moveTo(this.x + 8 * grid_size, this.y + 5 * grid_size);
        context.lineTo(this.x + 8 * grid_size, this.y + 6 * grid_size);
        context.moveTo(this.x + 8 * grid_size, this.y + 7 * grid_size);
        context.lineTo(this.x + 8 * grid_size, this.y + 8 * grid_size);
        context.moveTo(this.x + 8 * grid_size, this.y + 9 * grid_size);
        context.lineTo(this.x + 8 * grid_size, this.y + 10 * grid_size);
        context.lineWidth = (grid_size / 5) * 2;
        context.strokeStyle = '#000000';
        context.stroke();
        context.closePath();
        this.T1.draw(context);
        this.T2.draw(context);
        this.T3.draw(context);
        this.T4.draw(context);
    }

    is_inside(pos_x, pos_y) {
        return pos_x > this.x && pos_x < this.x + this.w && pos_y < this.y + this.h && pos_y > this.y;
    }

    get_terminal_at (pos_x, pos_y) {
        if (this.T1.is_inside(pos_x, pos_y)) return this.T1;
        if (this.T2.is_inside(pos_x, pos_y)) return this.T2;
        if (this.T3.is_inside(pos_x, pos_y)) return this.T3;
        if (this.T4.is_inside(pos_x, pos_y)) return this.T4;
        return null;
    }

    do_stuff () {
        this.closed = !this.closed;
    }

    get_terminals () {
        return [this.T1, this.T2, this.T3, this.T4];
    }

    propagate () {
        if (this.closed == false) return false;
        if ((this.T1.state == this.T3.state) && (this.T2.state == this.T4.state)) return false;
        var ret_val = false;
        if (this.T1.state == TerminalState.None) {
            this.T1.state = this.T3.state;
            ret_val = true;
        }
        if (this.T3.state == TerminalState.None) {
            this.T3.state = this.T1.state;
            ret_val = true;
        }
        if (ret_val == false) {
            alert("CSwitch102 : short circuit between " + this.T1.state + " and " + this.T3.state);
            return false;
        }
        if (this.T2.state == TerminalState.None) {
            this.T2.state = this.T4.state;
            ret_val = true;
        }
        if (this.T4.state == TerminalState.None) {
            this.T4.state = this.T2.state;
            ret_val = true;
        }
        if (ret_val == false) {
            alert("CSwitch102 : short circuit between " + this.T1.state + " and " + this.T3.state);
            return false;
        }
        return ret_val;
    }

    reset_terminals () {
        this.T1.state = TerminalState.None;
        this.T2.state = TerminalState.None;
        this.T3.state = TerminalState.None;
        this.T4.state = TerminalState.None;
    }

    check_terminals () {
        return false;
    }
};