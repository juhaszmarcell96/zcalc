class CSwitch101 extends IComponent {
    constructor (x, y) {
        super(x, y, 16 * grid_size, 16 * grid_size);
        this.terminals = {
            T1: new CTerminal(this.x -  4 * grid_size, this.y +  6 * grid_size, color_l3),
            T2: new CTerminal(this.x + 16 * grid_size, this.y +  6 * grid_size, color_l3)
        }
        this.closed = false;
    }

    draw (context, zoom) {
        context.beginPath();
        context.rect(this.x, this.y, this.w, this.h);
        context.fillStyle = 'rgba(230, 230, 230, 1)'; /* grey */
        context.fill();
        context.moveTo(this.x + 0 * grid_size, this.y + 8 * grid_size);
        context.lineTo(this.x + 5 * grid_size, this.y + 8 * grid_size);
        if (this.closed == false) {
            context.moveTo(this.x +  5 * grid_size, this.y + 8 * grid_size);
            context.lineTo(this.x + 11 * grid_size, this.y + 4 * grid_size);
        }
        else {
            context.moveTo(this.x +  5 * grid_size, this.y + 8 * grid_size);
            context.lineTo(this.x + 11 * grid_size, this.y + 8 * grid_size);
        }
        context.moveTo(this.x + 11 * grid_size, this.y + 8 * grid_size);
        context.lineTo(this.x + 16 * grid_size, this.y + 8 * grid_size);
        context.lineWidth = this.lineWidth;
        context.strokeStyle = '#000000';
        context.stroke();
        context.closePath();
        super.draw_terminals(context, zoom);
    }

    do_stuff () {
        this.closed = !this.closed;
    }
};