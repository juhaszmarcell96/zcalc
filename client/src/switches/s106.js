class CSwitch106 extends IComponent {
    constructor (x, y) {
        super(x, y, 16 * grid_size, 16 * grid_size);
        this.terminals = {
            T1: new CTerminal(this.x -  4 * grid_size, this.y +  6 * grid_size, color_l3),
            T2: new CTerminal(this.x + 16 * grid_size, this.y +  2 * grid_size, color_l3),
            T3: new CTerminal(this.x + 16 * grid_size, this.y + 10 * grid_size, color_l3)
        }
        this.closed = false;
    }

    draw (context, zoom) {
        const zoomed_x = this.x * zoom;
        const zoomed_y = this.y * zoom;
        const zoomed_w = this.w * zoom;
        const zoomed_h = this.h * zoom;
        const zoomed_g = grid_size * zoom;
        context.beginPath();
        context.rect(zoomed_x, zoomed_y, zoomed_w, zoomed_h);
        context.fillStyle = 'rgba(230, 230, 230, 1)'; /* grey */
        context.fill();
        context.moveTo(zoomed_x + 0 * zoomed_g, zoomed_y + 8 * zoomed_g);
        context.lineTo(zoomed_x + 5 * zoomed_g, zoomed_y + 8 * zoomed_g);
        if (this.closed == false) {
            context.moveTo(zoomed_x +  5 * zoomed_g, zoomed_y + 8 * zoomed_g);
            context.lineTo(zoomed_x + 11 * zoomed_g, zoomed_y + 4 * zoomed_g);
        }
        else {
            context.moveTo(zoomed_x +  5 * zoomed_g, zoomed_y + 8 * zoomed_g);
            context.lineTo(zoomed_x + 11 * zoomed_g, zoomed_y + 12 * zoomed_g);
        }
        context.moveTo(zoomed_x + 11 * zoomed_g, zoomed_y + 4 * zoomed_g);
        context.lineTo(zoomed_x + 16 * zoomed_g, zoomed_y + 4 * zoomed_g);
        context.moveTo(zoomed_x + 11 * zoomed_g, zoomed_y + 12 * zoomed_g);
        context.lineTo(zoomed_x + 16 * zoomed_g, zoomed_y + 12 * zoomed_g);
        context.lineWidth = (zoomed_g / 5) * 2;
        context.strokeStyle = '#000000';
        context.stroke();
        context.closePath();
        super.draw_terminals(context, zoom);
    }

    do_stuff () {
        this.closed = !this.closed;
    }
};