class CSource extends IComponent {
    constructor (x, y) {
        super(x, y, 200 * scale, 40 * scale);
        this.terminals = {
            L1: new CTerminal(this.x +  20 * scale, this.y + 20 * scale, Colors.l1),
            L2: new CTerminal(this.x +  60 * scale, this.y + 20 * scale, Colors.l2),
            L3: new CTerminal(this.x + 100 * scale, this.y + 20 * scale, Colors.l3),
            N : new CTerminal(this.x + 140 * scale, this.y + 20 * scale, Colors.n),
            PE: new CTerminal(this.x + 180 * scale, this.y + 20 * scale, Colors.pe)
        }
    }

    draw (context) {
        context.beginPath();
        context.rect(this.x, this.y, this.w, this.h);
        context.fillStyle = Colors.dark_grey;
        context.fill();
        context.lineWidth = this.lineWidth;
        context.strokeStyle = Colors.black;
        context.stroke();
        context.closePath();
        super.draw_terminals(context);
    }

    do_stuff () {
        return;
    }
}