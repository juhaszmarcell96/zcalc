class CSwitch101 extends IComponent {
    constructor (x, y) {
        super(x, y, 90 * scale, 90 * scale);
        this.terminals = {
            T1: new CTerminal(-this.w / 2 +        - 10 * scale, 0, Colors.l3),
            T2: new CTerminal(-this.w / 2 + this.w + 10 * scale, 0, Colors.l3)
        }
        this.closed = false;
    }

    draw (context) {
        context.translate(this.x + this.w / 2, this.y + this.h / 2);
        context.rotate(this.angle * Math.PI / 2);
        context.beginPath();
        context.rect(-this.w / 2, -this.h / 2, this.w, this.h);
        context.fillStyle = Colors.light_grey;
        context.fill();
        context.moveTo(-this.w / 2 +  0 * scale, -this.h / 2 + 50 * scale);
        context.lineTo(-this.w / 2 + 35 * scale, -this.h / 2 + 50 * scale);
        if (this.closed == false) {
            context.moveTo(-this.w / 2 + 35 * scale, -this.h / 2 + 50 * scale);
            context.lineTo(-this.w / 2 + 65 * scale, -this.h / 2 + 30 * scale);
        }
        else {
            context.moveTo(-this.w / 2 + 35 * scale, -this.h / 2 + 50 * scale);
            context.lineTo(-this.w / 2 + 65 * scale, -this.h / 2 + 50 * scale);
        }
        context.moveTo(-this.w / 2 + 65 * scale, -this.h / 2 + 50 * scale);
        context.lineTo(-this.w / 2 + 90 * scale, -this.h / 2 + 50 * scale);
        context.lineWidth = this.lineWidth;
        context.strokeStyle = Colors.black;
        context.stroke();
        context.closePath();
        this.draw_terminals(context);
        context.rotate(-1 * this.angle * Math.PI / 2);
        context.translate(-(this.x + this.w / 2), -(this.y + this.h / 2));
    }

    rotate () {
        return;
    }

    do_stuff () {
        this.closed = !this.closed;
    }
};