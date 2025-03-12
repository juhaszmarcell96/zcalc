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
        context.beginPath();
        context.rect(this.x, this.y, this.w, this.h);
        context.fillStyle = 'rgba(230, 230, 230, 1)'; /* grey */
        context.fill();
        context.lineWidth = this.lineWidth;
        context.strokeStyle = '#000000';
        context.font = '10pt Kremlin Pro Web';
        context.fillStyle = '#000000';
        context.fillText("A1"  , this.x +  4 * grid_size - context.measureText("A1").width / 2, this.y +  3 * grid_size);
        context.fillText("L1"  , this.x +  9 * grid_size - context.measureText("L1").width / 2, this.y +  3 * grid_size);
        context.fillText("L2"  , this.x + 15 * grid_size - context.measureText("L2").width / 2, this.y +  3 * grid_size);
        context.fillText("L3"  , this.x + 21 * grid_size - context.measureText("L3").width / 2, this.y +  3 * grid_size);
        context.fillText("NO13", this.x + 27 * grid_size - context.measureText("NO13").width / 2, this.y +  3 * grid_size);
        context.fillText("A2"  , this.x + 33 * grid_size - context.measureText("A2").width / 2, this.y +  3 * grid_size);
        context.fillText("T1"  , this.x +  9 * grid_size - context.measureText("T1").width / 2, this.y + 54 * grid_size);
        context.fillText("T2"  , this.x + 15 * grid_size - context.measureText("T2").width / 2, this.y + 54 * grid_size);
        context.fillText("T3"  , this.x + 21 * grid_size - context.measureText("T3").width / 2, this.y + 54 * grid_size);
        context.fillText("NO14", this.x + 27 * grid_size - context.measureText("NO14").width / 2, this.y + 54 * grid_size);
        if (this.closed) {
            context.fillText("on", this.x + 17 * grid_size - context.measureText("on").width / 2, this.y + 34 * grid_size);
        }
        else {
            context.fillText("off", this.x + 17 * grid_size - context.measureText("off").width / 2, this.y + 34 * grid_size);
        }
        context.font = '10pt Kremlin Pro Web';
        context.fillText("NO53", this.x +  5 * grid_size - context.measureText("NO53").width / 2, this.y +  9 * grid_size);
        context.fillText("NC61", this.x + 13 * grid_size - context.measureText("NC61").width / 2, this.y +  9 * grid_size);
        context.fillText("NC71", this.x + 22 * grid_size - context.measureText("NC71").width / 2, this.y +  9 * grid_size);
        context.fillText("NO83", this.x + 30 * grid_size - context.measureText("NO83").width / 2, this.y +  9 * grid_size);
        context.fillText("NO54", this.x +  5 * grid_size - context.measureText("NO54").width / 2, this.y + 27 * grid_size);
        context.fillText("NC62", this.x + 13 * grid_size - context.measureText("NC62").width / 2, this.y + 27 * grid_size);
        context.fillText("NC72", this.x + 22 * grid_size - context.measureText("NC72").width / 2, this.y + 27 * grid_size);
        context.fillText("NO84", this.x + 30 * grid_size - context.measureText("NO84").width / 2, this.y + 27 * grid_size);
        context.fillText("NC98", this.x +  5 * grid_size - context.measureText("NC98").width / 2, this.y + 39 * grid_size);
        context.fillText("NC97", this.x + 13 * grid_size - context.measureText("NC97").width / 2, this.y + 39 * grid_size);
        context.fillText("NO95", this.x + 22 * grid_size - context.measureText("NO95").width / 2, this.y + 39 * grid_size);
        context.fillText("NO96", this.x + 30 * grid_size - context.measureText("NO96").width / 2, this.y + 39 * grid_size);
        context.stroke();
        context.closePath();
        super.draw_terminals(context, zoom);
    }

    do_stuff () {
        return;
    }
};