class CTimeSwitch extends IComponent {
    constructor (x, y) {
        super(x, y, 14 * grid_size, 20 * grid_size);
        this.terminals = {
            T1: new CTerminal(this.x +  0 * grid_size, this.y -  4 * grid_size, color_l1),
            T2: new CTerminal(this.x +  5 * grid_size, this.y -  4 * grid_size, color_l3),
            T3: new CTerminal(this.x + 10 * grid_size, this.y -  4 * grid_size, color_n),
            T4: new CTerminal(this.x +  0 * grid_size, this.y + 20 * grid_size, color_l3),
            T5: new CTerminal(this.x +  5 * grid_size, this.y + 20 * grid_size, color_l3),
            T6: new CTerminal(this.x + 10 * grid_size, this.y + 20 * grid_size, color_l3)
        }
        this.prev_closed = false;
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
        context.moveTo(zoomed_x + 7 * zoomed_g, zoomed_y + 0 * zoomed_g);
        context.lineTo(zoomed_x + 7 * zoomed_g, zoomed_y + 8 * zoomed_g);
        context.moveTo(zoomed_x + 6 * zoomed_g, zoomed_y + 6 * zoomed_g);
        context.lineTo(zoomed_x + 7 * zoomed_g, zoomed_y + 8 * zoomed_g);
        context.moveTo(zoomed_x + 8 * zoomed_g, zoomed_y + 6 * zoomed_g);
        context.lineTo(zoomed_x + 7 * zoomed_g, zoomed_y + 8 * zoomed_g);
        
        context.moveTo(zoomed_x + 2 * zoomed_g, zoomed_y + 20 * zoomed_g);
        context.lineTo(zoomed_x + 2 * zoomed_g, zoomed_y + 11 * zoomed_g);
        context.moveTo(zoomed_x + 2 * zoomed_g, zoomed_y + 11 * zoomed_g);
        context.lineTo(zoomed_x + 4 * zoomed_g, zoomed_y + 11 * zoomed_g);
        if (this.closed == true) {
            context.moveTo(zoomed_x +  4 * zoomed_g, zoomed_y + 11 * zoomed_g);
            context.lineTo(zoomed_x +  8 * zoomed_g, zoomed_y +  8 * zoomed_g);
        }
        else {
            context.moveTo(zoomed_x +  4 * zoomed_g, zoomed_y + 11 * zoomed_g);
            context.lineTo(zoomed_x +  8 * zoomed_g, zoomed_y + 14 * zoomed_g);
        }
        context.moveTo(zoomed_x +  7 * zoomed_g, zoomed_y + 20 * zoomed_g);
        context.lineTo(zoomed_x +  7 * zoomed_g, zoomed_y + 13 * zoomed_g);
        context.moveTo(zoomed_x + 12 * zoomed_g, zoomed_y + 20 * zoomed_g);
        context.lineTo(zoomed_x + 12 * zoomed_g, zoomed_y +  8 * zoomed_g);
        context.moveTo(zoomed_x +  8 * zoomed_g, zoomed_y +  8 * zoomed_g);
        context.lineTo(zoomed_x + 12 * zoomed_g, zoomed_y +  8 * zoomed_g);
        context.lineWidth = (zoomed_g / 5) * 2;
        context.strokeStyle = '#000000';
        context.stroke();
        context.closePath();
        super.draw_terminals(context, zoom);
    }

    do_stuff () {
        //setTimeout(timeElapsed, 5000)
        this.closed = false;
        return;
    }
};