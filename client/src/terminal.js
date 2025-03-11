class CTerminal {
    constructor (x, y, fillStyle) {
        this.x = x - (x % grid_size);;
        this.y = y - (y % grid_size);;
        this.w = 4 * grid_size;
        this.h = 4 * grid_size;
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

    draw (context, zoom) {
        const zoomed_x = this.x * zoom;
        const zoomed_y = this.y * zoom;
        const zoomed_w = this.w * zoom;
        const zoomed_h = this.h * zoom;
        const zoomed_g = grid_size * zoom;
        context.beginPath();
        context.rect(zoomed_x,zoomed_y, zoomed_w, zoomed_h);
        context.fillStyle = this.fillStyle;
        context.fill();
        context.lineWidth = (zoomed_g / 5) * 2;
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