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
        context.fillText("A1"  , this.x +  4 * this.zoomed_g - context.measureText("A1").width / 2, this.y +  3 * this.zoomed_g);
        context.fillText("L1"  , this.x +  9 * this.zoomed_g - context.measureText("L1").width / 2, this.y +  3 * this.zoomed_g);
        context.fillText("L2"  , this.x + 15 * this.zoomed_g - context.measureText("L2").width / 2, this.y +  3 * this.zoomed_g);
        context.fillText("L3"  , this.x + 21 * this.zoomed_g - context.measureText("L3").width / 2, this.y +  3 * this.zoomed_g);
        context.fillText("NO13", this.x + 27 * this.zoomed_g - context.measureText("NO13").width / 2, this.y +  3 * this.zoomed_g);
        context.fillText("A2"  , this.x + 33 * this.zoomed_g - context.measureText("A2").width / 2, this.y +  3 * this.zoomed_g);
        context.fillText("T1"  , this.x +  9 * this.zoomed_g - context.measureText("T1").width / 2, this.y + 54 * this.zoomed_g);
        context.fillText("T2"  , this.x + 15 * this.zoomed_g - context.measureText("T2").width / 2, this.y + 54 * this.zoomed_g);
        context.fillText("T3"  , this.x + 21 * this.zoomed_g - context.measureText("T3").width / 2, this.y + 54 * this.zoomed_g);
        context.fillText("NO14", this.x + 27 * this.zoomed_g - context.measureText("NO14").width / 2, this.y + 54 * this.zoomed_g);
        if (this.closed) {
            context.fillText("on", this.x + 17 * this.zoomed_g - context.measureText("on").width / 2, this.y + 34 * this.zoomed_g);
        }
        else {
            context.fillText("off", this.x + 17 * this.zoomed_g - context.measureText("off").width / 2, this.y + 34 * this.zoomed_g);
        }
        context.font = '10pt Kremlin Pro Web';
        context.fillText("NO53", this.x +  5 * this.zoomed_g - context.measureText("NO53").width / 2, this.y +  9 * this.zoomed_g);
        context.fillText("NC61", this.x + 13 * this.zoomed_g - context.measureText("NC61").width / 2, this.y +  9 * this.zoomed_g);
        context.fillText("NC71", this.x + 22 * this.zoomed_g - context.measureText("NC71").width / 2, this.y +  9 * this.zoomed_g);
        context.fillText("NO83", this.x + 30 * this.zoomed_g - context.measureText("NO83").width / 2, this.y +  9 * this.zoomed_g);
        context.fillText("NO54", this.x +  5 * this.zoomed_g - context.measureText("NO54").width / 2, this.y + 27 * this.zoomed_g);
        context.fillText("NC62", this.x + 13 * this.zoomed_g - context.measureText("NC62").width / 2, this.y + 27 * this.zoomed_g);
        context.fillText("NC72", this.x + 22 * this.zoomed_g - context.measureText("NC72").width / 2, this.y + 27 * this.zoomed_g);
        context.fillText("NO84", this.x + 30 * this.zoomed_g - context.measureText("NO84").width / 2, this.y + 27 * this.zoomed_g);
        context.fillText("NC98", this.x +  5 * this.zoomed_g - context.measureText("NC98").width / 2, this.y + 39 * this.zoomed_g);
        context.fillText("NC97", this.x + 13 * this.zoomed_g - context.measureText("NC97").width / 2, this.y + 39 * this.zoomed_g);
        context.fillText("NO95", this.x + 22 * this.zoomed_g - context.measureText("NO95").width / 2, this.y + 39 * this.zoomed_g);
        context.fillText("NO96", this.x + 30 * this.zoomed_g - context.measureText("NO96").width / 2, this.y + 39 * this.zoomed_g);
        context.stroke();
        context.closePath();
        super.draw_terminals(context, zoom);
    }

    do_stuff () {
        return;
    }
};