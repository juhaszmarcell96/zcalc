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

    draw (context, zoom) {
        const zoomed_x = this.x * zoom;
        const zoomed_y = this.y * zoom;
        const zoomed_w = this.w * zoom;
        const zoomed_h = this.h * zoom;
        const zoomed_g = grid_size * zoom;
        context.beginPath();
        context.rect(zoomed_x, zoomed_y, zoomed_w, zoomed_h);
        context.fillStyle = 'rgba(220, 220, 220, 1)';
        context.fill();
        context.lineWidth = (zoomed_g / 5) * 2;
        context.strokeStyle = '#000000';
        context.stroke();
        context.closePath();
        super.draw_terminals(context, zoom);
    }

    do_stuff () {
        return;
    }
}