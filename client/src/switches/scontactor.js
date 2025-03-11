class CContactor extends IComponent {
    constructor (x, y) {
        super(x, y, 36 * grid_size, 55 * grid_size);
        this.terminals = {
            A1  : new CTerminal(this.x +  1 * grid_size, this.y -  4 * grid_size, color_l1),
            L1  : new CTerminal(this.x +  7 * grid_size, this.y -  4 * grid_size, color_l3),
            L2  : new CTerminal(this.x + 13 * grid_size, this.y -  4 * grid_size, color_l3),
            L3  : new CTerminal(this.x + 19 * grid_size, this.y -  4 * grid_size, color_l3),
            NO13: new CTerminal(this.x + 25 * grid_size, this.y -  4 * grid_size, color_l3),
            A2  : new CTerminal(this.x + 31 * grid_size, this.y -  4 * grid_size, color_n ),
    
            T1  : new CTerminal(this.x +  7 * grid_size, this.y + 55 * grid_size, color_l3),
            T2  : new CTerminal(this.x + 13 * grid_size, this.y + 55 * grid_size, color_l3),
            T3  : new CTerminal(this.x + 19 * grid_size, this.y + 55 * grid_size, color_l3),
            NO14: new CTerminal(this.x + 25 * grid_size, this.y + 55 * grid_size, color_l3),
    
            NO53: new CTerminal(this.x +  3 * grid_size, this.y + 10 * grid_size, color_l3),
            NC61: new CTerminal(this.x + 11 * grid_size, this.y + 10 * grid_size, color_l3),
            NC71: new CTerminal(this.x + 20 * grid_size, this.y + 10 * grid_size, color_l3),
            NO83: new CTerminal(this.x + 28 * grid_size, this.y + 10 * grid_size, color_l3),
    
            NO54: new CTerminal(this.x +  3 * grid_size, this.y + 20 * grid_size, color_l3),
            NC62: new CTerminal(this.x + 11 * grid_size, this.y + 20 * grid_size, color_l3),
            NC72: new CTerminal(this.x + 20 * grid_size, this.y + 20 * grid_size, color_l3),
            NO84: new CTerminal(this.x + 28 * grid_size, this.y + 20 * grid_size, color_l3),
    
            NC98: new CTerminal(this.x +  3 * grid_size, this.y + 40 * grid_size, color_l3),
            NC97: new CTerminal(this.x + 11 * grid_size, this.y + 40 * grid_size, color_l3),
            NO95: new CTerminal(this.x + 20 * grid_size, this.y + 40 * grid_size, color_l3),
            NO96: new CTerminal(this.x + 28 * grid_size, this.y + 40 * grid_size, color_l3)
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
        context.lineWidth = (zoomed_g / 5) * 2;
        context.strokeStyle = '#000000';
        context.font = '10pt Kremlin Pro Web';
        context.fillStyle = '#000000';
        context.fillText("A1"  , zoomed_x +  4 * zoomed_g - context.measureText("A1").width / 2, zoomed_y +  3 * zoomed_g);
        context.fillText("L1"  , zoomed_x +  9 * zoomed_g - context.measureText("L1").width / 2, zoomed_y +  3 * zoomed_g);
        context.fillText("L2"  , zoomed_x + 15 * zoomed_g - context.measureText("L2").width / 2, zoomed_y +  3 * zoomed_g);
        context.fillText("L3"  , zoomed_x + 21 * zoomed_g - context.measureText("L3").width / 2, zoomed_y +  3 * zoomed_g);
        context.fillText("NO13", zoomed_x + 27 * zoomed_g - context.measureText("NO13").width / 2, zoomed_y +  3 * zoomed_g);
        context.fillText("A2"  , zoomed_x + 33 * zoomed_g - context.measureText("A2").width / 2, zoomed_y +  3 * zoomed_g);
        context.fillText("T1"  , zoomed_x +  9 * zoomed_g - context.measureText("T1").width / 2, zoomed_y + 54 * zoomed_g);
        context.fillText("T2"  , zoomed_x + 15 * zoomed_g - context.measureText("T2").width / 2, zoomed_y + 54 * zoomed_g);
        context.fillText("T3"  , zoomed_x + 21 * zoomed_g - context.measureText("T3").width / 2, zoomed_y + 54 * zoomed_g);
        context.fillText("NO14", zoomed_x + 27 * zoomed_g - context.measureText("NO14").width / 2, zoomed_y + 54 * zoomed_g);
        if (this.closed) {
            context.fillText("on", zoomed_x + 17 * zoomed_g - context.measureText("on").width / 2, zoomed_y + 34 * zoomed_g);
        }
        else {
            context.fillText("off", zoomed_x + 17 * zoomed_g - context.measureText("off").width / 2, zoomed_y + 34 * zoomed_g);
        }
        context.font = '10pt Kremlin Pro Web';
        context.fillText("NO53", zoomed_x +  5 * zoomed_g - context.measureText("NO53").width / 2, zoomed_y +  9 * zoomed_g);
        context.fillText("NC61", zoomed_x + 13 * zoomed_g - context.measureText("NC61").width / 2, zoomed_y +  9 * zoomed_g);
        context.fillText("NC71", zoomed_x + 22 * zoomed_g - context.measureText("NC71").width / 2, zoomed_y +  9 * zoomed_g);
        context.fillText("NO83", zoomed_x + 30 * zoomed_g - context.measureText("NO83").width / 2, zoomed_y +  9 * zoomed_g);
        context.fillText("NO54", zoomed_x +  5 * zoomed_g - context.measureText("NO54").width / 2, zoomed_y + 27 * zoomed_g);
        context.fillText("NC62", zoomed_x + 13 * zoomed_g - context.measureText("NC62").width / 2, zoomed_y + 27 * zoomed_g);
        context.fillText("NC72", zoomed_x + 22 * zoomed_g - context.measureText("NC72").width / 2, zoomed_y + 27 * zoomed_g);
        context.fillText("NO84", zoomed_x + 30 * zoomed_g - context.measureText("NO84").width / 2, zoomed_y + 27 * zoomed_g);
        context.fillText("NC98", zoomed_x +  5 * zoomed_g - context.measureText("NC98").width / 2, zoomed_y + 39 * zoomed_g);
        context.fillText("NC97", zoomed_x + 13 * zoomed_g - context.measureText("NC97").width / 2, zoomed_y + 39 * zoomed_g);
        context.fillText("NO95", zoomed_x + 22 * zoomed_g - context.measureText("NO95").width / 2, zoomed_y + 39 * zoomed_g);
        context.fillText("NO96", zoomed_x + 30 * zoomed_g - context.measureText("NO96").width / 2, zoomed_y + 39 * zoomed_g);
        context.stroke();
        context.closePath();
        super.draw_terminals(context, zoom);
    }

    do_stuff () {
        return;
    }
};