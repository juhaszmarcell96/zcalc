
class C3PhaseMotor extends IComponent {
    constructor (x, y) {
        super(x, y);
        this.w = 32 * grid_size;
        this.h = 16 * grid_size;
        this.U1 = new CTerminal(this.x +  2 * grid_size, this.y -  4 * grid_size, color_l3);
        this.V1 = new CTerminal(this.x +  8 * grid_size, this.y -  4 * grid_size, color_l3);
        this.W1 = new CTerminal(this.x + 14 * grid_size, this.y -  4 * grid_size, color_l3);
        this.W2 = new CTerminal(this.x +  2 * grid_size, this.y + 16 * grid_size, color_l3);
        this.U2 = new CTerminal(this.x +  8 * grid_size, this.y + 16 * grid_size, color_l3);
        this.V2 = new CTerminal(this.x + 14 * grid_size, this.y + 16 * grid_size, color_l3);
        this.PE = new CTerminal(this.x -  4 * grid_size, this.y +  6 * grid_size, color_pe);

        this.error = false;
        this.on = false;
        this.forward = false;
        this.delta = false;
    }

    draw (context) {
        context.beginPath();
        context.rect(this.x, this.y, this.w, this.h);
        context.fillStyle = 'rgba(230, 230, 230, 1)'; /* grey */
        context.fill();
        context.lineWidth = (grid_size / 5) * 2;
        context.strokeStyle = '#000000';
        context.font = '14pt Kremlin Pro Web';
        context.fillStyle = '#000000';
        context.fillText("U1", this.x +  4 * grid_size - context.measureText("U1").width / 2, this.y +  4 * grid_size);
        context.fillText("V1", this.x + 10 * grid_size - context.measureText("V1").width / 2, this.y +  4 * grid_size);
        context.fillText("W1", this.x + 16 * grid_size - context.measureText("W1").width / 2, this.y +  4 * grid_size);
        context.fillText("W2", this.x +  4 * grid_size - context.measureText("W2").width / 2, this.y + 15 * grid_size);
        context.fillText("U2", this.x + 10 * grid_size - context.measureText("U2").width / 2, this.y + 15 * grid_size);
        context.fillText("V2", this.x + 16 * grid_size - context.measureText("V2").width / 2, this.y + 15 * grid_size);
        if (this.error == true) {
                context.fillText("error", this.x + 26 * grid_size - context.measureText("error").width / 2, this.y + 9 * grid_size);
        }
        else {
            if (this.on == false) {
                context.fillText("off", this.x + 26 * grid_size - context.measureText("off").width / 2, this.y + 9 * grid_size);
            }
            else {
                if (this.forward == false) {
                    context.fillText("rev", this.x + 26 * grid_size - context.measureText("rev").width / 2, this.y + 6 * grid_size);
                }
                else {
                    context.fillText("fwd", this.x + 26 * grid_size - context.measureText("fwd").width / 2, this.y + 6 * grid_size);
                }
                if (this.delta == false) {
                    context.fillText("star", this.x + 26 * grid_size - context.measureText("star").width / 2, this.y + 13 * grid_size);
                }
                else {
                    context.fillText("delta", this.x + 26 * grid_size - context.measureText("delta").width / 2, this.y + 13 * grid_size);
                }
            }
        }
        context.stroke();
        context.closePath();
        this.U1.draw(context);
        this.V1.draw(context);
        this.W1.draw(context);
        this.U2.draw(context);
        this.V2.draw(context);
        this.W2.draw(context);
        this.PE.draw(context);
    }

    is_inside(pos_x, pos_y) {
        return false; /* TODO if needed */
    }

    get_terminal_at (pos_x, pos_y) {
        if (this.U1.is_inside(pos_x, pos_y)) return this.U1;
        if (this.V1.is_inside(pos_x, pos_y)) return this.V1;
        if (this.W1.is_inside(pos_x, pos_y)) return this.W1;
        if (this.U2.is_inside(pos_x, pos_y)) return this.U2;
        if (this.V2.is_inside(pos_x, pos_y)) return this.V2;
        if (this.W2.is_inside(pos_x, pos_y)) return this.W2;
        if (this.PE.is_inside(pos_x, pos_y)) return this.PE;
        return null;
    }

    do_stuff () {
        return;
    }

    get_terminals () {
        return [this.U1, this.V1, this.W1, this.U2, this.V2, this.W2, this.PE];
    }

    propagate () {
        return false;
    }

    reset_terminals () {
        this.U1.state = TerminalState.None;
        this.V1.state = TerminalState.None;
        this.W1.state = TerminalState.None;
        /* virtual state, if at the end of the cycle both V2 and W2 have this state (or N), it is a star connection */
        this.U2.state = TerminalState.Virtual;
        this.V2.state = TerminalState.None;
        this.W2.state = TerminalState.None;
        this.PE.state = TerminalState.None;
    }

    check_terminals () {
        this.on = false;
        this.forward = false;
        this.delta = false;
        this.error = false;

        if ((this.U1.state == TerminalState.None) && (this.V1.state == TerminalState.None) && (this.W1.state == TerminalState.None)) {
            return false;
        }

        if (((this.U1.state == TerminalState.L1) && (this.V1.state == TerminalState.L2) && (this.W1.state == TerminalState.L3)) ||
            ((this.U1.state == TerminalState.L2) && (this.V1.state == TerminalState.L3) && (this.W1.state == TerminalState.L1)) ||
            ((this.U1.state == TerminalState.L3) && (this.V1.state == TerminalState.L1) && (this.W1.state == TerminalState.L2)))
        {
            this.forward = true;
            if (((this.U2.state == TerminalState.Virtual) && (this.V2.state == TerminalState.Virtual) && (this.W2.state == TerminalState.Virtual)) ||
                ((this.U2.state == TerminalState.N) && (this.V2.state == TerminalState.N) && (this.W2.state == TerminalState.N)))
            {
                this.delta = false;
                this.on = true;
                if (this.PE.state != TerminalState.PE) {alert("C3PhaseMotor : DANGER : PE connected incorrectly"); }
                return false;
            }
            else if ((this.U1.state == this.W2.state) && (this.V2.state == this.U2.state) && (this.W1.state == this.V1.state))
            {
                this.delta = true;
                this.on = true;
                if (this.PE.state != TerminalState.PE) {alert("C3PhaseMotor : DANGER : PE connected incorrectly"); }
                return false;
            }
        }
        else if (((this.U1.state == TerminalState.L1) && (this.V1.state == TerminalState.L3) && (this.W1.state == TerminalState.L2)) ||
                ((this.U1.state == TerminalState.L2) && (this.V1.state == TerminalState.L1) && (this.W1.state == TerminalState.L3)) ||
                ((this.U1.state == TerminalState.L3) && (this.V1.state == TerminalState.L2) && (this.W1.state == TerminalState.L1)))
        {
            this.forward = false;
            if (((this.U2.state == TerminalState.Virtual) && (this.V2.state == TerminalState.Virtual) && (this.W2.state == TerminalState.Virtual)) ||
                ((this.U1.state == TerminalState.N) && (this.V1.state == TerminalState.N) && (this.W1.state == TerminalState.N)))
            {
                this.delta = false;
                this.on = true;
                if (this.PE.state != TerminalState.PE) {alert("C3PhaseMotor : DANGER : PE connected incorrectly"); }
                return false;
            }
            else if ((this.U1.state == this.W2.state) && (this.V1.state == this.U2.state) && (this.W1.state == this.V2.state))
            {
                this.delta = true;
                this.on = true;
                if (this.PE.state != TerminalState.PE) {alert("C3PhaseMotor : DANGER : PE connected incorrectly"); }
                return false;
            }
        }

        this.error = true;
        return false;
    }
};