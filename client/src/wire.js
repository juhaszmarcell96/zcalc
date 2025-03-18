class CWire extends IComponent {
    constructor (type) {
        super(0.0, 0.0, 10 * scale, 10 * scale);
        this.type = type;
        this.lineWidth = 2;
        this.terminals = {
            T1: new CTerminal(0, 0, Colors.l1),
            T2: new CTerminal(0, 0, Colors.l1)
        }
        this.terminals.T1.scale(0.5);
        this.terminals.T2.scale(0.5);
    }
    
    draw (context) {
        context.translate(this.x, this.y);
        context.rotate(this.angle * Math.PI / 2);
        context.beginPath();
        context.lineWidth = this.lineWidth;
        context.moveTo(this.terminals.T1.get_middle_x(), this.terminals.T1.get_middle_y());
        context.lineTo(this.terminals.T2.get_middle_x(), this.terminals.T2.get_middle_y());
        if (this.type == WireType.L) context.strokeStyle = Colors.l1;
        else if (this.type == WireType.N) context.strokeStyle = Colors.n;
        else context.strokeStyle = color_pe;
        context.stroke();
        context.closePath();
        this.draw_terminals(context);
        context.rotate(-1 * this.angle * Math.PI / 2);
        context.translate(-(this.x), -(this.y));
    }

    start (x, y) {
        this.x = x;
        this.y = y;
    }

    wire (x, y) {
        let dx = x - this.x;
        let dy = y - this.y;
        dx = dx - (dx % grid_size);
        dy = dy - (dy % grid_size);
        if (Math.abs(dx) > Math.abs(dy)) {
            this.w = dx;
            this.h = this.terminals.T1.h;
            this.terminals.T2.set_middle(this.w, 0);
        }
        else {
            this.w = this.terminals.T1.w;
            this.h = dy;
            this.terminals.T2.set_middle(0, this.h);
        }
    }

    is_inside(pos_x, pos_y) {
        const t1_middle_x = this.x + this.terminals.T1.x;
        const t1_middle_y = this.y + this.terminals.T1.y;
        const t2_middle_x = this.x + this.terminals.T2.x;
        const t2_middle_y = this.y + this.terminals.T2.y;
        let x = t1_middle_x < t2_middle_x ? t1_middle_x : t2_middle_x;
        let y = t1_middle_y < t2_middle_y ? t1_middle_y : t2_middle_y;
        let w = this.w > 0 ? this.w : -1*this.w;
        let h = this.h > 0 ? this.h : -1*this.h;
        return pos_x > x && pos_x < x + w && pos_y < y + h && pos_y > y;
    }

    get_end () {
        return [this.x + this.terminals.T2.get_middle_x(), this.y + this.terminals.T2.get_middle_y()];
    }

    stop (x, y) {
        this.wire(x, y);
        if (Math.abs(this.w) < this.terminals.T1.w) {
            this.w = this.w < 0 ? -this.terminals.T1.w : this.terminals.T1.w;
        }
        if (Math.abs(this.h) < this.terminals.T1.h) {
            this.h = this.h < 0 ? -this.terminals.T1.h : this.terminals.T1.h;
        }
    }

    get_terminal_at (pos_x, pos_y) {
        for (const [key, value] of Object.entries(this.terminals)) {
            if (value.is_inside(pos_x - this.x, pos_y - this.y)) {
                return new Coordinates (this.x + value.get_middle_x(), this.y + value.get_middle_y());
            }
        }
        return null;
    }

    rotate () {
        return;
    }
}