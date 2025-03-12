class CPlayground {
    constructor (x, y, w, h) {
        this.x = x;
        this.y = y;
        this.w = w;
        this.h = h;
        
        this.components = [];
        this.wires = [];
    }

    draw (context) {
        context.beginPath();
        context.rect(this.x,this.y, this.w, this.h);
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
};