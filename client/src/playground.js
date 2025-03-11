class CPlayground {
    constructor (x, y, w, h) {
        this.x = x;
        this.y = y;
        this.w = w;
        this.h = h;
        
        this.components = [];
        this.wires = [];
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
};