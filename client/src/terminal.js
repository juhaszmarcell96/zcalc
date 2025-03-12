class CTerminal {
    constructor (x, y, fillStyle) {
        this.x = x - (x % grid_size);
        this.y = y - (y % grid_size);
        this.w = 4 * grid_size;
        this.h = 4 * grid_size;
        this.lineWidth = 2;
        this.fillStyle = fillStyle;
        this.state = TerminalState.None;
    }

    move (dx, dy) {
        this.x += dx;
        this.y += dy;
    }

    set_middle (x, y) {
        this.x = x - this.w / 2.0;
        this.y = y - this.h / 2.0;
    }

    scale (s) {
        this.x += (this.w - this.w * s) / 2.0;
        this.y += (this.h - this.h * s) / 2.0;
        this.w *= s;
        this.h *= s;
    }

    get_middle_x () {
        return this.x + this.w / 2.0;
    }

    get_middle_y () {
        return this.y + this.h / 2.0;
    }

    draw (context) {
        context.beginPath();
        context.rect(this.x, this.y, this.w, this.h);
        context.fillStyle = this.fillStyle;
        context.fill();
        context.lineWidth = this.lineWidth;
        if (this.selected == true) {
            context.strokeStyle = '#DC143C';
        }
        else {
            context.strokeStyle = '#000000';
        }
        context.stroke();
        context.closePath();
    }

    is_inside(pos_x, pos_y) {
        return (pos_x > this.x) && (pos_x < (this.x + this.w)) && (pos_y < (this.y + this.h)) && (pos_y > this.y);
    }
};