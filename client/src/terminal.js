class CTerminal {
    constructor (x, y, fillStyle) {
        this.x = x - (x % grid_size);
        this.y = y - (y % grid_size);
        this.w = 4 * grid_size;
        this.h = 4 * grid_size;
        this.lineWidth = (grid_size / 5) * 2;
        this.fillStyle = fillStyle;
        this.selected = false;
        this.state = TerminalState.None;
    }

    select () {
        this.selected = true;
    }

    move (dx, dy) {
        this.x += dx;
        this.y += dy;
    }

    zoom (zoom) {
        this.x *= zoom;
        this.y *= zoom;
        this.w *= zoom;
        this.h *= zoom;
        this.lineWidth *= zoom;
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
        return pos_x > this.x && pos_x < this.x + this.w && pos_y < this.y + this.h && pos_y > this.y;
    }
};