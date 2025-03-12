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
        context.beginPath();
        context.rect(this.x, this.y, this.w, this.h);
        context.fillStyle = 'rgba(230, 230, 230, 1)'; /* grey */
        context.fill();
        context.moveTo(this.x + 7 * grid_size, this.y + 0 * grid_size);
        context.lineTo(this.x + 7 * grid_size, this.y + 8 * grid_size);
        context.moveTo(this.x + 6 * grid_size, this.y + 6 * grid_size);
        context.lineTo(this.x + 7 * grid_size, this.y + 8 * grid_size);
        context.moveTo(this.x + 8 * grid_size, this.y + 6 * grid_size);
        context.lineTo(this.x + 7 * grid_size, this.y + 8 * grid_size);
        
        context.moveTo(this.x + 2 * grid_size, this.y + 20 * grid_size);
        context.lineTo(this.x + 2 * grid_size, this.y + 11 * grid_size);
        context.moveTo(this.x + 2 * grid_size, this.y + 11 * grid_size);
        context.lineTo(this.x + 4 * grid_size, this.y + 11 * grid_size);
        if (this.closed == true) {
            context.moveTo(this.x +  4 * grid_size, this.y + 11 * grid_size);
            context.lineTo(this.x +  8 * grid_size, this.y +  8 * grid_size);
        }
        else {
            context.moveTo(this.x +  4 * grid_size, this.y + 11 * grid_size);
            context.lineTo(this.x +  8 * grid_size, this.y + 14 * grid_size);
        }
        context.moveTo(this.x +  7 * grid_size, this.y + 20 * grid_size);
        context.lineTo(this.x +  7 * grid_size, this.y + 13 * grid_size);
        context.moveTo(this.x + 12 * grid_size, this.y + 20 * grid_size);
        context.lineTo(this.x + 12 * grid_size, this.y +  8 * grid_size);
        context.moveTo(this.x +  8 * grid_size, this.y +  8 * grid_size);
        context.lineTo(this.x + 12 * grid_size, this.y +  8 * grid_size);
        context.lineWidth = this.lineWidth;
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