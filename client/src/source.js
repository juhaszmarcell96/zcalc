class CSource extends IComponent {
    constructor (x, y) {
        super(x, y);
        this.w = 40 * grid_size;
        this.h = 8 * grid_size;

        this.L1 = new CTerminal(this.x +  2 * grid_size, this.y + 2 * grid_size, color_l1);
        this.L2 = new CTerminal(this.x + 10 * grid_size, this.y + 2 * grid_size, color_l2);
        this.L3 = new CTerminal(this.x + 18 * grid_size, this.y + 2 * grid_size, color_l3);
        this.N  = new CTerminal(this.x + 26 * grid_size, this.y + 2 * grid_size, color_n);
        this.PE = new CTerminal(this.x + 34 * grid_size, this.y + 2 * grid_size, color_pe);
    }

    draw (context) {
        context.beginPath();
        context.rect(this.x, this.y, this.w, this.h);
        context.fillStyle = 'rgba(220, 220, 220, 1)';
        context.fill();
        context.lineWidth = (grid_size / 5) * 2;
        context.strokeStyle = '#000000';
        context.stroke();
        context.closePath();
        this.L1.draw(context);
        this.L2.draw(context);
        this.L3.draw(context);
        this.N.draw(context);
        this.PE.draw(context);
    }

    is_inside(pos_x, pos_y) {
        return pos_x > this.x && pos_x < this.x + this.w && pos_y < this.y + this.h && pos_y > this.y;
    }

    get_terminal_at (pos_x, pos_y) {
        if (this.L1.is_inside(pos_x, pos_y)) return this.L1;
        if (this.L2.is_inside(pos_x, pos_y)) return this.L2;
        if (this.L3.is_inside(pos_x, pos_y)) return this.L3;
        if (this.N.is_inside(pos_x, pos_y)) return this.N;
        if (this.PE.is_inside(pos_x, pos_y)) return this.PE;
        return null;
    }

    do_stuff () {
        return;
    }

    get_terminals () {
        return [this.L1, this.L2, this.L3, this.N, this.PE];
    }

    propagate () {
        if (this.L1.state == TerminalState.None) {
            this.L1.state = TerminalState.L1;
            this.L2.state = TerminalState.L2;
            this.L3.state = TerminalState.L3;
            this.N.state = TerminalState.N;
            this.PE.state = TerminalState.PE;
            return true;
        }
        return false;
    }

    reset_terminals () {
        this.L1.state = TerminalState.None;
        this.L2.state = TerminalState.None;
        this.L3.state = TerminalState.None;
        this.N.state = TerminalState.None;
        this.PE.state = TerminalState.None;
    }

    check_terminals () {
        return false;
    }
}