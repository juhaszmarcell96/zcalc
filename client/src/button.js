class CButton {
    constructor (x, y, w, h, fillStyle, text) {
        this.x = x;
        this.y = y;
        this.w = w;
        this.h = h;
        this.fillStyle = fillStyle;
        this.text = text;
    }

    draw (context) {
        context.beginPath();
        context.roundRect(this.x, this.y, this.w, this.h, [2 * grid_size]);
        context.fillStyle = this.fillStyle;
        context.fill();
        context.lineWidth = (grid_size / 5) * 2;
        context.strokeStyle = Colors.black;
        context.font = '14pt Kremlin Pro Web';
        context.fillStyle = '#FFFFFF';
        var width = context.measureText(this.text).width;
        context.fillText(this.text, this.x + (this.w - width) / 2, this.y + 35 * scale);
        context.stroke();
        context.closePath();
    }

    is_inside(pos_x, pos_y) {
        return pos_x > this.x && pos_x < this.x + this.w && pos_y < this.y + this.h && pos_y > this.y;
    }
};