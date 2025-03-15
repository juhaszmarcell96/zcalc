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
    }

    draw_terminals(context) {
        for (const [key, value] of Object.entries(this.terminals)) {
            value.draw(context);
        }
    }

    draw (context) {
        console.log('ERROR : "draw" function not overloaded');
    }

    rotate () {
        console.log('ERROR : "rotate" function not overloaded');
    }

    is_inside(pos_x, pos_y) {
        return pos_x > this.x && pos_x < this.x + this.w && pos_y < this.y + this.h && pos_y > this.y;
    }

    snap_to_grid () {
        const modulo_x = this.x % grid_size;
        const modulo_y = this.y % grid_size;
        if (modulo_x > grid_size / 2) {
            this.x += grid_size - modulo_x;
        }
        else {
            this.x -= modulo_x;
        }
        if (modulo_y > grid_size / 2) {
            this.y += grid_size - modulo_y;
        }
        else {
            this.y -= modulo_y;
        }
        for (const [key, value] of Object.entries(this.terminals)) {
            value.snap_to_grid();
        }
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