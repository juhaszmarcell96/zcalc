class IComponent {
    constructor (x, y, w, h) {
        this.x = x - (x % grid_size);
        this.y = y - (y % grid_size);
        this.w = w
        this.h = h
        this.lineWidth = 2;
        this.terminals = {};
        this.move_offset_x = 0;
        this.move_offset_y = 0;
        this.dx = 0.0
        this.dy = 0.0
    }

    draw_terminals(context, zoom) {
        for (const [key, value] of Object.entries(this.terminals)) {
            value.draw(context, zoom);
        }
    }

    draw (context) {
        console.log('ERROR : "draw" function not overloaded');
    }

    is_inside(pos_x, pos_y) {
        return pos_x > this.x && pos_x < this.x + this.w && pos_y < this.y + this.h && pos_y > this.y;
    }

    move(dx, dy) {
        this.dx += dx;
        this.dy += dy;
        let terminal_dx = 0.0;
        let terminal_dy = 0.0;
        if (this.dx > grid_size / 2) {
            this.x += grid_size;
            this.dx -= grid_size;
            terminal_dx = grid_size;
        }
        else if (this.dx < -grid_size / 2) {
            this.x -= grid_size;
            this.dx += grid_size;
            terminal_dx = -grid_size;
        }
        if (this.dy > grid_size / 2) {
            this.y += grid_size;
            this.dy -= grid_size;
            terminal_dy = grid_size;
        }
        else if (this.dy < -grid_size / 2) {
            this.y -= grid_size;
            this.dy += grid_size;
            terminal_dy = -grid_size;
        }
        //this.x += dx;
        //this.y += dy;
        for (const [key, value] of Object.entries(this.terminals)) {
            value.move(terminal_dx, terminal_dy);
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