class CTimeSwitch extends IComponent {
    constructor (x, y) {
        super(x, y, 70 * scale, 100 * scale);
        this.terminals = {
            T1: new CTerminal(-this.w / 2 + 10 * scale, -this.h / 2          - 10 * scale, Colors.l1),
            T2: new CTerminal(-this.w / 2 + 35 * scale, -this.h / 2          - 10 * scale, Colors.l3),
            T3: new CTerminal(-this.w / 2 + 60 * scale, -this.h / 2          - 10 * scale, Colors.n),
            T4: new CTerminal(-this.w / 2 + 10 * scale, -this.h / 2 + this.h + 10 * scale, Colors.l3),
            T5: new CTerminal(-this.w / 2 + 35 * scale, -this.h / 2 + this.h + 10 * scale, Colors.l3),
            T6: new CTerminal(-this.w / 2 + 60 * scale, -this.h / 2 + this.h + 10 * scale, Colors.l3)
        }
        this.prev_closed = false;
        this.closed = false;
    }

    draw (context) {
        context.translate(this.x + this.w / 2, this.y + this.h / 2);
        context.rotate(this.angle * Math.PI / 2);
        context.beginPath();
        context.rect(-this.w / 2, -this.h / 2, this.w, this.h);
        context.fillStyle = Colors.dark_grey;
        context.fill();
        context.moveTo(-this.w / 2 + 45 * scale, -this.h / 2 +  0 * scale);
        context.lineTo(-this.w / 2 + 45 * scale, -this.h / 2 + 50 * scale);
        context.moveTo(-this.w / 2 + 40 * scale, -this.h / 2 + 40 * scale);
        context.lineTo(-this.w / 2 + 45 * scale, -this.h / 2 + 50 * scale);
        context.moveTo(-this.w / 2 + 50 * scale, -this.h / 2 + 40 * scale);
        context.lineTo(-this.w / 2 + 45 * scale, -this.h / 2 + 50 * scale);
        
        context.moveTo(-this.w / 2 + 20 * scale, -this.h / 2 + 110 * scale);
        context.lineTo(-this.w / 2 + 20 * scale, -this.h / 2 +  65 * scale);
        context.moveTo(-this.w / 2 + 20 * scale, -this.h / 2 +  65 * scale);
        context.lineTo(-this.w / 2 + 30 * scale, -this.h / 2 +  65 * scale);
        if (this.closed == true) {
            context.moveTo(-this.w / 2 + 30 * scale, -this.h / 2 + 65 * scale);
            context.lineTo(-this.w / 2 + 50 * scale, -this.h / 2 + 50 * scale);
        }
        else {
            context.moveTo(-this.w / 2 + 30 * scale, -this.h / 2 + 65 * scale);
            context.lineTo(-this.w / 2 + 50 * scale, -this.h / 2 + 80 * scale);
        }
        context.moveTo(-this.w / 2 + 45 * scale, -this.h / 2 + 110 * scale);
        context.lineTo(-this.w / 2 + 45 * scale, -this.h / 2 +  75 * scale);
        context.moveTo(-this.w / 2 + 70 * scale, -this.h / 2 + 110 * scale);
        context.lineTo(-this.w / 2 + 70 * scale, -this.h / 2 +  50 * scale);
        context.moveTo(-this.w / 2 + 50 * scale, -this.h / 2 +  50 * scale);
        context.lineTo(-this.w / 2 + 70 * scale, -this.h / 2 +  50 * scale);
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
        //setTimeout(timeElapsed, 5000)
        this.closed = false;
        return;
    }
};