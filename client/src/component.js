class IComponent {
    constructor (x, y, w, h) {
        this.x = x - (x % grid_size);
        this.y = y - (y % grid_size);
        this.w = w
        this.h = h
        this.lineWidth = (grid_size / 5) * 2;
        this.terminals = {};
        this.move_offset_x = 0;
        this.move_offset_y = 0;
        this.zoomed_g = grid_size;
    }

    draw_terminals(context, zoom) {
        for (const [key, value] of Object.entries(this.terminals)) {
            value.draw(context, zoom);
        }
    }

    zoom (zoom) {
        this.x *= zoom;
        this.y *= zoom;
        this.w *= zoom;
        this.h *= zoom;
        this.lineWidth *= zoom;
        this.zoomed_g *= zoom;
        for (const [key, value] of Object.entries(this.terminals)) {
            value.zoom(zoom);
        }
    }

    draw (context) {
        console.log('ERROR : "draw" function not overloaded');
    }

    is_inside(pos_x, pos_y) {
        return pos_x > this.x && pos_x < this.x + this.w && pos_y < this.y + this.h && pos_y > this.y;
    }

    start_move(pos_x, pos_y) {
        this.move_offset_x = pos_x - (pos_x % grid_size) - this.x;
        this.move_offset_y = pos_y - (pos_y % grid_size) - this.y;
    }

    move(dx, dy) {
        this.x += dx;
        this.y += dy;
        for (const [key, value] of Object.entries(this.terminals)) {
            value.move(dx, dy);
        }
    }

    get_terminal_at (pos_x, pos_y) {
        for (const [key, value] of Object.entries(this.terminals)) {
            if (value.is_inside(pos_x, pos_y)) { return value; }
        }
        return null;
    }

    do_stuff () {
        console.log('ERROR : "do_stuff" function not overloaded');
    }

    get_terminals () {
        return this.terminals;
    }
};