class CSwitch101 extends IComponent {
    constructor (x, y) {
        super(x, y, 90 * scale, 90 * scale);
        this.terminals = {
            T1: new CTerminal(this.x          - 10 * scale, this.y + this.w / 2, Colors.l3),
            T2: new CTerminal(this.x + this.w + 10 * scale, this.y + this.w / 2, Colors.l3)
        }
        this.closed = false;
    }

    draw (context) {
        context.beginPath();
        context.rect(this.x, this.y, this.w, this.h);
        context.fillStyle = Colors.dark_grey; /* grey */
        context.fill();
        context.moveTo(this.x +  0 * scale, this.y + 50 * scale);
        context.lineTo(this.x + 35 * scale, this.y + 50 * scale);
        if (this.closed == false) {
            context.moveTo(this.x + 35 * scale, this.y + 50 * scale);
            context.lineTo(this.x + 65 * scale, this.y + 30 * scale);
        }
        else {
            context.moveTo(this.x + 35 * scale, this.y + 50 * scale);
            context.lineTo(this.x + 65 * scale, this.y + 50 * scale);
        }
        context.moveTo(this.x + 65 * scale, this.y + 50 * scale);
        context.lineTo(this.x + 90 * scale, this.y + 50 * scale);
        context.lineWidth = this.lineWidth;
        context.strokeStyle = Colors.black;
        context.stroke();
        context.closePath();
        this.draw_terminals(context);
    }

    rotate () {
        return;
    }

    do_stuff () {
        this.closed = !this.closed;
    }
};