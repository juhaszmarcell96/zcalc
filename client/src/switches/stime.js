class CTimeSwitch extends IComponent {
    constructor (x, y) {
        super(x, y, 70 * scale, 100 * scale);
        this.terminals = {
            T1: new CTerminal(this.x + 10 * scale, this.y          - 10 * scale, Colors.l1),
            T2: new CTerminal(this.x + 35 * scale, this.y          - 10 * scale, Colors.l3),
            T3: new CTerminal(this.x + 60 * scale, this.y          - 10 * scale, Colors.n),
            T4: new CTerminal(this.x + 10 * scale, this.y + this.h + 10 * scale, Colors.l3),
            T5: new CTerminal(this.x + 35 * scale, this.y + this.h + 10 * scale, Colors.l3),
            T6: new CTerminal(this.x + 60 * scale, this.y + this.h + 10 * scale, Colors.l3)
        }
        this.prev_closed = false;
        this.closed = false;
    }

    draw (context) {
        context.beginPath();
        context.rect(this.x, this.y, this.w, this.h);
        context.fillStyle = Colors.dark_grey;
        context.fill();
        context.moveTo(this.x + 45 * scale, this.y +  0 * scale);
        context.lineTo(this.x + 45 * scale, this.y + 50 * scale);
        context.moveTo(this.x + 40 * scale, this.y + 40 * scale);
        context.lineTo(this.x + 45 * scale, this.y + 50 * scale);
        context.moveTo(this.x + 50 * scale, this.y + 40 * scale);
        context.lineTo(this.x + 45 * scale, this.y + 50 * scale);
        
        context.moveTo(this.x + 20 * scale, this.y + 110 * scale);
        context.lineTo(this.x + 20 * scale, this.y +  65 * scale);
        context.moveTo(this.x + 20 * scale, this.y +  65 * scale);
        context.lineTo(this.x + 30 * scale, this.y +  65 * scale);
        if (this.closed == true) {
            context.moveTo(this.x + 30 * scale, this.y + 65 * scale);
            context.lineTo(this.x + 50 * scale, this.y + 50 * scale);
        }
        else {
            context.moveTo(this.x + 30 * scale, this.y + 65 * scale);
            context.lineTo(this.x + 50 * scale, this.y + 80 * scale);
        }
        context.moveTo(this.x + 45 * scale, this.y + 110 * scale);
        context.lineTo(this.x + 45 * scale, this.y +  75 * scale);
        context.moveTo(this.x + 70 * scale, this.y + 110 * scale);
        context.lineTo(this.x + 70 * scale, this.y +  50 * scale);
        context.moveTo(this.x + 50 * scale, this.y +  50 * scale);
        context.lineTo(this.x + 70 * scale, this.y +  50 * scale);
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
        //setTimeout(timeElapsed, 5000)
        this.closed = false;
        return;
    }
};