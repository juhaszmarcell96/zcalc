class Point {
    constructor (x, y) {
        this.x = x;
        this.y = y;
    }
};

const WireType = {
    L: 0,
    N: 1,
    PE: 2
};

class CWire extends IComponent {
    constructor (type) {
        super(0.0, 0.0, 0.0, 0.0);
        this.type = type;
        this.lineWidth = 2;
    }
    
    draw (context) {
        context.beginPath();
        context.lineWidth = this.lineWidth;
        context.moveTo(this.terminals.T1.get_middle_x(), this.terminals.T1.get_middle_y());
        context.lineTo(this.terminals.T2.get_middle_x(), this.terminals.T2.get_middle_y());
        if (this.type == WireType.L) context.strokeStyle = color_l1;
        else if (this.type == WireType.N) context.strokeStyle = color_n;
        else context.strokeStyle = color_pe;
        context.stroke();
        context.closePath();
        super.draw_terminals(context);
    }

    start (x, y) {
        this.terminals = {
            T1: new CTerminal(x, y, color_l1),
            T2: new CTerminal(x, y, color_l1)
        }
        this.terminals.T1.set_middle(x, y);
        this.terminals.T1.scale(0.5);
        this.terminals.T2.scale(0.5);
        this.x = this.terminals.T1.x;
        this.y = this.terminals.T1.y;
    }

    wire (x, y) {
        let dx = x - this.terminals.T1.get_middle_x();
        let dy = y - this.terminals.T1.get_middle_y();
        dx = dx - (dx % grid_size);
        dy = dy - (dy % grid_size);
        if (Math.abs(dx) > Math.abs(dy)) {
            this.w = Math.abs(dx);
            this.h = this.terminals.T1.w;
            this.terminals.T2.x = this.terminals.T1.get_middle_x() + dx - this.terminals.T2.w / 2;
            this.terminals.T2.y = this.terminals.T1.get_middle_y() + 0.0 - this.terminals.T2.h / 2;
        }
        else {
            this.w = this.terminals.T1.h;
            this.h = Math.abs(dy);
            this.terminals.T2.x = this.terminals.T1.get_middle_x() + 0.0 - this.terminals.T2.w / 2;
            this.terminals.T2.y = this.terminals.T1.get_middle_y() + dy - this.terminals.T2.h / 2;
        }
        if (this.terminals.T1.x < this.terminals.T2.x) {
            this.x = this.terminals.T1.x;
        }
        else {
            this.x = this.terminals.T2.x;
        }
        if (this.terminals.T1.y < this.terminals.T2.y) {
            this.y = this.terminals.T1.y;
        }
        else {
            this.y = this.terminals.T2.y;
        }
    }

    stop (x, y) {
        this.wire(x, y);
    }
}