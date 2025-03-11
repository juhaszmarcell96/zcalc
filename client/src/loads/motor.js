
class C3PhaseMotor extends IComponent {
    constructor (x, y) {
        super(x, y, 32 * grid_size, 16 * grid_size);
        this.terminals = {
            U1: new CTerminal(this.x +  2 * grid_size, this.y -  4 * grid_size, color_l3),
            V1: new CTerminal(this.x +  8 * grid_size, this.y -  4 * grid_size, color_l3),
            W1: new CTerminal(this.x + 14 * grid_size, this.y -  4 * grid_size, color_l3),
            W2: new CTerminal(this.x +  2 * grid_size, this.y + 16 * grid_size, color_l3),
            U2: new CTerminal(this.x +  8 * grid_size, this.y + 16 * grid_size, color_l3),
            V2: new CTerminal(this.x + 14 * grid_size, this.y + 16 * grid_size, color_l3),
            PE: new CTerminal(this.x -  4 * grid_size, this.y +  6 * grid_size, color_pe)
        }

        this.error = false;
        this.on = false;
        this.forward = false;
        this.delta = false;
    }

    draw (context, zoom) {
        context.beginPath();
        context.rect(this.x, this.y, this.w, this.h);
        context.fillStyle = 'rgba(230, 230, 230, 1)'; /* grey */
        context.fill();
        context.lineWidth = this.lineWidth;
        context.strokeStyle = '#000000';
        context.font = '14pt Kremlin Pro Web';
        context.fillStyle = '#000000';
        context.fillText("U1", this.x +  4 * this.zoomed_g - context.measureText("U1").width / 2, this.y +  4 * this.zoomed_g);
        context.fillText("V1", this.x + 10 * this.zoomed_g - context.measureText("V1").width / 2, this.y +  4 * this.zoomed_g);
        context.fillText("W1", this.x + 16 * this.zoomed_g - context.measureText("W1").width / 2, this.y +  4 * this.zoomed_g);
        context.fillText("W2", this.x +  4 * this.zoomed_g - context.measureText("W2").width / 2, this.y + 15 * this.zoomed_g);
        context.fillText("U2", this.x + 10 * this.zoomed_g - context.measureText("U2").width / 2, this.y + 15 * this.zoomed_g);
        context.fillText("V2", this.x + 16 * this.zoomed_g - context.measureText("V2").width / 2, this.y + 15 * this.zoomed_g);
        if (this.error == true) {
                context.fillText("error", this.x + 26 * this.zoomed_g - context.measureText("error").width / 2, this.y + 9 * this.zoomed_g);
        }
        else {
            if (this.on == false) {
                context.fillText("off", this.x + 26 * this.zoomed_g - context.measureText("off").width / 2, this.y + 9 * this.zoomed_g);
            }
            else {
                if (this.forward == false) {
                    context.fillText("rev", this.x + 26 * this.zoomed_g - context.measureText("rev").width / 2, this.y + 6 * this.zoomed_g);
                }
                else {
                    context.fillText("fwd", this.x + 26 * this.zoomed_g - context.measureText("fwd").width / 2, this.y + 6 * this.zoomed_g);
                }
                if (this.delta == false) {
                    context.fillText("star", this.x + 26 * this.zoomed_g - context.measureText("star").width / 2, this.y + 13 * this.zoomed_g);
                }
                else {
                    context.fillText("delta", this.x + 26 * this.zoomed_g - context.measureText("delta").width / 2, this.y + 13 * this.zoomed_g);
                }
            }
        }
        context.stroke();
        context.closePath();
        super.draw_terminals(context, zoom);
    }

    do_stuff () {
        return;
    }
};