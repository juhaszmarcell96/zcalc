class CSource extends IComponent {
    constructor (x, y) {
        super(x, y, 40 * grid_size, 8 * grid_size);
        this.terminals = {
            L1: new CTerminal(this.x +  2 * grid_size, this.y + 2 * grid_size, color_l1),
            L2: new CTerminal(this.x + 10 * grid_size, this.y + 2 * grid_size, color_l2),
            L3: new CTerminal(this.x + 18 * grid_size, this.y + 2 * grid_size, color_l3),
            N : new CTerminal(this.x + 26 * grid_size, this.y + 2 * grid_size, color_n),
            PE: new CTerminal(this.x + 34 * grid_size, this.y + 2 * grid_size, color_pe)
        }
    }

    draw (context) {
        context.beginPath();
        context.rect(this.x, this.y, this.w, this.h);
        context.fillStyle = 'rgba(220, 220, 220, 1)';
        context.fill();
        context.lineWidth = this.lineWidth;
        context.strokeStyle = '#000000';
        context.stroke();
        context.closePath();
        super.draw_terminals(context);
    }

    do_stuff () {
        return;
    }
}