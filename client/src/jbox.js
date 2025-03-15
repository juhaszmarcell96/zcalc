class CJunctionBox extends IComponent {
    constructor (x, y) {
        super(x, y, 70 * scale, 70 * scale);
        this.terminals = {
            T1: new CTerminal(this.x + 15 * scale, this.y + 15 * scale, Colors.l3),
            T2: new CTerminal(this.x + 35 * scale, this.y + 35 * scale, Colors.l3),
            T3: new CTerminal(this.x + 55 * scale, this.y + 55 * scale, Colors.l3)
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
};