
class CLamp extends IComponent {
    constructor (x, y) {
        super(x, y, 12 * grid_size, 12 * grid_size);
        let middle_x = this.x + this.w / 2;
        let middle_y = this.y + this.h / 2;
        this.terminals = {
            L : new CTerminal(middle_x - 8 * grid_size, middle_y + 8 * grid_size, color_l1),
            N : new CTerminal(middle_x - 2 * grid_size, middle_y + 8 * grid_size, color_n),
            PE: new CTerminal(middle_x + 4 * grid_size, middle_y + 8 * grid_size, color_pe)
        }
        this.on = false;
    }

    draw (context, zoom) {
        const zoomed_x = this.x * zoom;
        const zoomed_y = this.y * zoom;
        const zoomed_w = this.w * zoom;
        const zoomed_h = this.h * zoom;
        const zoomed_g = grid_size * zoom;
        context.beginPath();
        let middle_x = zoomed_x + zoomed_w / 2;
        let middle_y = zoomed_y + zoomed_h / 2;
        let radius = zoomed_w / 2;
        context.arc(middle_x, middle_y, radius, 0, 2 * Math.PI);
        if (this.on == false) {
            context.fillStyle = 'rgba(192, 192, 192, 1)'; /* grey */
        }
        else {
            context.fillStyle = 'rgba(255, 215,   0, 1)'; /* yellow */
        }
        context.fill();
        context.moveTo(middle_x - 4 * zoomed_g, middle_y - 4 * zoomed_g);
        context.lineTo(middle_x + 4 * zoomed_g, middle_y + 4 * zoomed_g);
        context.moveTo(middle_x - 4 * zoomed_g, middle_y + 4 * zoomed_g);
        context.lineTo(middle_x + 4 * zoomed_g, middle_y - 4 * zoomed_g);
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