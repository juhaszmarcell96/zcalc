class CResistor extends IComponent {
    constructor (x, y) {
        super(x, y, 90 * scale, 20 * scale);
        const terminal_0_x = this.x          - 10 * scale;
        const terminal_1_x = this.x + this.w + 10 * scale;
        const terminal_0_y = this.y + this.h / 2;
        const terminal_1_y = this.y + this.h / 2;
        this.terminals = {
            T1: new CTerminal(terminal_0_x, terminal_0_y, Colors.l3),
            T2: new CTerminal(terminal_1_x, terminal_1_y, Colors.l3)
        }
        this.rotated = false;
    }

    rotate () {
        // flip rotated flag
        this.rotated = !this.rotated;
        // middle point
        const middle_x = this.x + this.w / 2;
        const middle_y = this.y + this.h / 2;
        // calculate new x and y
        this.x = middle_x - this.h / 2;
        this.y = middle_y - this.w / 2;
        // swap width and height
        const temp = this.w;
        this.w = this.h;
        this.h = temp;
        if (this.rotated) {
            const terminal_0_x = this.x + this.w / 2;
            const terminal_1_x = this.x + this.w / 2;
            const terminal_0_y = this.y          - 10 * scale;
            const terminal_1_y = this.y + this.h + 10 * scale
            this.terminals.T1.set_middle(terminal_0_x, terminal_0_y);
            this.terminals.T2.set_middle(terminal_1_x, terminal_1_y);
        }
        else {
            const terminal_0_x = this.x          - 10 * scale;
            const terminal_1_x = this.x + this.w + 10 * scale;
            const terminal_0_y = this.y + this.h / 2;
            const terminal_1_y = this.y + this.h / 2;
            this.terminals.T1.set_middle(terminal_0_x, terminal_0_y);
            this.terminals.T2.set_middle(terminal_1_x, terminal_1_y);
        }
    }

    draw (context) {
        context.beginPath();
        if (this.rotated) {
            context.rect(this.x, this.y + 1 * this.h / 4, this.w, this.h / 2);
        }
        else {
            context.rect(this.x + 1 * this.w / 4, this.y, this.w / 2, this.h);
        }
        context.fillStyle = Colors.dark_grey;
        context.fill();
        if (this.rotated) {
            context.moveTo(this.x + this.w / 2, this.y + 0 * this.h / 4);
            context.lineTo(this.x + this.w / 2, this.y + 1 * this.h / 4);
            context.moveTo(this.x + this.w / 2, this.y + 3 * this.h / 4);
            context.lineTo(this.x + this.w / 2, this.y + 4 * this.h / 4);
        }
        else {
            context.moveTo(this.x + 0 * this.w / 4, this.y + this.h / 2);
            context.lineTo(this.x + 1 * this.w / 4, this.y + this.h / 2);
            context.moveTo(this.x + 3 * this.w / 4, this.y + this.h / 2);
            context.lineTo(this.x + 4 * this.w / 4, this.y + this.h / 2);
        }
        context.lineWidth = this.lineWidth;
        context.strokeStyle = Colors.black;
        context.stroke();
        context.closePath();
        this.draw_terminals(context);
    }

    do_stuff () {
        // nothing to do
    }
};