class CJunctionBox extends IComponent {
    constructor (x, y) {
        super(x, y);
        this.w = 14 * grid_size;
        this.h = 14 * grid_size;
        this.T1  = new CTerminal(this.x +  1 * grid_size, this.y +  1 * grid_size, color_l3);
        this.T2  = new CTerminal(this.x +  5 * grid_size, this.y +  5 * grid_size, color_l3);
        this.T3  = new CTerminal(this.x +  9 * grid_size, this.y +  9 * grid_size, color_l3);
    }

    draw (context) {
        context.beginPath();
        context.rect(this.x, this.y, this.w, this.h);
        context.fillStyle = 'rgba(230, 230, 230, 1)'; /* grey */
        context.fill();
        context.lineWidth = (grid_size / 5) * 2;
        context.strokeStyle = '#000000';
        context.stroke();
        context.closePath();
        this.T1.draw(context);
        this.T2.draw(context);
        this.T3.draw(context);
    }

    is_inside(pos_x, pos_y) {
        return pos_x > this.x && pos_x < this.x + this.w && pos_y < this.y + this.h && pos_y > this.y;
    }

    get_terminal_at (pos_x, pos_y) {
        if (this.T1.is_inside(pos_x, pos_y)) return this.T1;
        if (this.T2.is_inside(pos_x, pos_y)) return this.T2;
        if (this.T3.is_inside(pos_x, pos_y)) return this.T3;
        return null;
    }

    do_stuff () {
        return;
    }

    get_terminals () {
        return [this.T1, this.T2, this.T3];
    }

    propagate () {
        return false;
    }

    reset_terminals () {
        this.T1.state = TerminalState.None;
        this.T2.state = TerminalState.None;
        this.T3.state = TerminalState.None;
    }

    check_terminals () {
        return false;
    }
};