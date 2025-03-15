class CLamp extends IComponent {
    constructor (x, y) {
        super(x, y, 60 * scale, 60 * scale);
        let middle_x = this.x + this.w / 2;
        let middle_y = this.y + this.h / 2;
        this.terminals = {
            L : new CTerminal(middle_x - 30 * scale, middle_y + 50 * scale, Colors.l1),
            N : new CTerminal(middle_x -  0 * scale, middle_y + 50 * scale, Colors.n),
            PE: new CTerminal(middle_x + 30 * scale, middle_y + 50 * scale, Colors.pe)
        }
        this.on = false;
    }

    draw (context) {
        context.beginPath();
        let middle_x = this.x + this.w / 2;
        let middle_y = this.y + this.h / 2;
        let radius = this.w / 2;
        context.arc(middle_x, middle_y, radius, 0, 2 * Math.PI);
        if (this.on == false) {
            context.fillStyle = Colors.grey;
        }
        else {
            context.fillStyle = Colors.yellow;
        }
        context.fill();
        const line_offset = 20 * scale;
        context.moveTo(middle_x - line_offset, middle_y - line_offset);
        context.lineTo(middle_x + line_offset, middle_y + line_offset);
        context.moveTo(middle_x - line_offset, middle_y + line_offset);
        context.lineTo(middle_x + line_offset, middle_y - line_offset);
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
        return;
    }
};