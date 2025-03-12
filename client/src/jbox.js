class CJunctionBox extends IComponent {
    constructor (x, y) {
        super(x, y, 14 * grid_size, 14 * grid_size);
        this.terminals = {
            T1: new CTerminal(this.x +  1 * grid_size, this.y +  1 * grid_size, color_l3),
            T2: new CTerminal(this.x +  5 * grid_size, this.y +  5 * grid_size, color_l3),
            T3: new CTerminal(this.x +  9 * grid_size, this.y +  9 * grid_size, color_l3)
        }
    }

    draw (context) {
        context.beginPath();
        context.rect(this.x, this.y, this.w, this.h);
        context.fillStyle = 'rgba(230, 230, 230, 1)'; /* grey */
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
};