
class CLamp extends IComponent {
    constructor (x, y) {
        super(x, y);
        this.L  = new CTerminal(this.x - 8 * grid_size, this.y + 8 * grid_size, color_l1);
        this.N  = new CTerminal(this.x - 2 * grid_size, this.y + 8 * grid_size, color_n);
        this.PE = new CTerminal(this.x + 4 * grid_size, this.y + 8 * grid_size, color_pe);
        this.on = false;
    }

    draw (context) {
        context.beginPath();
        context.arc(this.x, this.y, 6 * grid_size, 0, 2 * Math.PI);
        if (this.on == false) {
            context.fillStyle = 'rgba(192, 192, 192, 1)'; /* grey */
        }
        else {
            context.fillStyle = 'rgba(255, 215,   0, 1)'; /* yellow */
        }
        context.fill();
        context.moveTo(this.x - 4 * grid_size, this.y - 4 * grid_size);
        context.lineTo(this.x + 4 * grid_size, this.y + 4 * grid_size);
        context.moveTo(this.x - 4 * grid_size, this.y + 4 * grid_size);
        context.lineTo(this.x + 4 * grid_size, this.y - 4 * grid_size);
        context.lineWidth = (grid_size / 5) * 2;
        context.strokeStyle = '#000000';
        context.stroke();
        context.closePath();
        this.L.draw(context);
        this.N.draw(context);
        this.PE.draw(context);
    }

    is_inside(pos_x, pos_y) {
        return false; /* TODO if needed */
    }

    get_terminal_at (pos_x, pos_y) {
        if (this.L.is_inside(pos_x, pos_y)) return this.L;
        if (this.N.is_inside(pos_x, pos_y)) return this.N;
        if (this.PE.is_inside(pos_x, pos_y)) return this.PE;
        return null;
    }

    do_stuff () {
        return;
    }

    get_terminals () {
        return [this.L, this.N, this.PE];
    }

    propagate () {
        return false;
    }

    reset_terminals () {
        this.L.state = TerminalState.None;
        this.N.state = TerminalState.None;
        this.PE.state = TerminalState.None;
    }

    check_terminals () {
        this.on = false;
        if (((this.L.state == TerminalState.L1) || (this.L.state == TerminalState.L2) || (this.L.state == TerminalState.L3)) && (this.N.state == TerminalState.N)) {
            this.on = true;
            if (this.PE.state == TerminalState.None) {
                alert("CLamp : WARNING : connect PE");
            }
            return false;
        }
        if ((this.N.state == TerminalState.L1) || (this.N.state == TerminalState.L2) || (this.N.state == TerminalState.L3)) {
            alert("CLamp : DANGER : N connected to Lx");
            return false;
        }
        if ((this.PE.state == TerminalState.L1) || (this.PE.state == TerminalState.L2) || (this.PE.state == TerminalState.L3)) {
            alert("CLamp : DANGER : PE connected to Lx");
            return false;
        }
        if (this.N.state == TerminalState.PE) {
            alert("CLamp : DANGER : PE connected to N");
            return false;
        }
        if (this.PE.state == TerminalState.N) {
            alert("CLamp : DANGER : N connected to PE");
            return false;
        }
        return false;
    }
};