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

class CWire {
    constructor (x, y, type) {
        this.x = x;
        this.y = y;
        this.points = []
        this.points.push(new Point(super.x, super.y));
        this.type = type;

        this.T1 = null;
        this.T2 = null;
    }
    
    draw (context, zoom) {
        context.beginPath();
        context.lineWidth = (grid_size / 5) * 2;
        context.arc(this.x, this.y, (grid_size / 5) * 2, 0, 2 * Math.PI);
        context.moveTo(this.x, this.y);
        for (let i = 0; i < this.points.length; i++) {
            context.lineTo(this.points[i].x, this.points[i].y);
            context.arc(this.points[i].x, this.points[i].y, (grid_size / 5) * 2, 0, 2 * Math.PI);
            context.moveTo(this.points[i].x, this.points[i].y);
        }
        if (this.type == WireType.L) context.strokeStyle = color_l1;
        else if (this.type == WireType.N) context.strokeStyle = color_n;
        else context.strokeStyle = color_pe;
        context.stroke();
        context.closePath();
    }

    set_last_pos (pos_x, pos_y) {
        if (this.points.length == 1) {
            if (Math.abs(this.x - pos_x) < Math.abs(this.y - pos_y)) pos_x = this.x;
            else pos_y = this.y;
        }
        else {
            if (Math.abs(this.points[this.points.length - 2].x - pos_x) < Math.abs(this.points[this.points.length - 2].y - pos_y)) pos_x = this.points[this.points.length - 2].x;
            else pos_y = this.points[this.points.length - 2].y;
        }
        this.points[this.points.length - 1].x = pos_x - (pos_x % grid_size);
        this.points[this.points.length - 1].y = pos_y - (pos_y % grid_size);
    }

    fix_last_pos (pos_x, pos_y) {
        pos_x = pos_x - (pos_x % grid_size);
        pos_y = pos_y - (pos_y % grid_size);
        this.points.push(new Point(pos_x, pos_y));
    }

    get_last_pos_x () {
        return this.points[this.points.length - 1].x;
    }

    get_last_pos_y () {
        return this.points[this.points.length - 1].y;
    }

    is_inside(pos_x, pos_y) {
        var x_1 = this.x
        var y_1 = this.y;
        for (let i = 0; i < this.points.length; i++) {
            var x_2 = this.points[i].x;
            var y_2 = this.points[i].y;

            var min_x = x_1 < x_2 ? x_1 : x_2;
            var max_x = x_1 < x_2 ? x_2 : x_1;
            var min_y = y_1 < y_2 ? y_1 : y_2;
            var max_y = y_1 < y_2 ? y_2 : y_1;
            min_x -= 2 * grid_size / 5;
            max_x += 2 * grid_size / 5;
            min_y -= 2 * grid_size / 5;
            max_y += 2 * grid_size / 5;
            
            x_1 = x_2;
            y_1 = y_2;
            
            if ((pos_x >= min_x) && (pos_x <= max_x) && (pos_y >= min_y) && (pos_y <= max_y)) {
                return true;
            }
        }
        return false;
    }
}