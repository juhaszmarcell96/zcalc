class CJunctionBox extends IComponent {
    constructor (x, y) {
        super(x, y, 14 * grid_size, 14 * grid_size);
        this.terminals = {
            T1: new CTerminal(this.x +  1 * grid_size, this.y +  1 * grid_size, color_l3),
            T2: new CTerminal(this.x +  5 * grid_size, this.y +  5 * grid_size, color_l3),
            T3: new CTerminal(this.x +  9 * grid_size, this.y +  9 * grid_size, color_l3)
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
        context.fillStyle = 'rgba(230, 230, 230, 1)'; /* grey */
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
};