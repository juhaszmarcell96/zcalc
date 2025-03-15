class C3PhaseMotor extends IComponent {
    constructor (x, y) {
        super(x, y, 160 * scale, 80 * scale);
        this.terminals = {
            U1: new CTerminal(this.x +  30 * scale, this.y          - 10 * scale, Colors.l3),
            V1: new CTerminal(this.x +  70 * scale, this.y          - 10 * scale, Colors.l3),
            W1: new CTerminal(this.x + 110 * scale, this.y          - 10 * scale, Colors.l3),
            W2: new CTerminal(this.x +  30 * scale, this.y + this.h + 10 * scale, Colors.l3),
            U2: new CTerminal(this.x +  70 * scale, this.y + this.h + 10 * scale, Colors.l3),
            V2: new CTerminal(this.x + 110 * scale, this.y + this.h + 10 * scale, Colors.l3),
            PE: new CTerminal(this.x -  10 * scale, this.y          + 40 * scale, Colors.pe)
        }

        this.error = false;
        this.on = false;
        this.forward = false;
        this.delta = false;
    }

    draw (context, zoom) {
        context.beginPath();
        context.rect(this.x, this.y, this.w, this.h);
        context.fillStyle = Colors.dark_grey;
        context.fill();
        context.lineWidth = this.lineWidth;
        context.strokeStyle = Colors.black;
        context.font = '14pt Kremlin Pro Web';
        context.fillStyle = Colors.black;
        context.fillText("U1", this.terminals.U1.get_middle_x() - 8 * scale, this.terminals.U1.get_middle_y() + 30 * scale);
        context.fillText("V1", this.terminals.V1.get_middle_x() - 8 * scale, this.terminals.V1.get_middle_y() + 30 * scale);
        context.fillText("W1", this.terminals.W1.get_middle_x() - 8 * scale, this.terminals.W1.get_middle_y() + 30 * scale);
        context.fillText("W2", this.terminals.W2.get_middle_x() - 8 * scale, this.terminals.W2.get_middle_y() - 20 * scale);
        context.fillText("U2", this.terminals.U2.get_middle_x() - 8 * scale, this.terminals.U2.get_middle_y() - 20 * scale);
        context.fillText("V2", this.terminals.V2.get_middle_x() - 8 * scale, this.terminals.V2.get_middle_y() - 20 * scale);
        if (this.error == true) {
                context.fillText("error", this.x + 120 * scale - context.measureText("error").width / 2, this.terminals.PE.get_middle_y() + 5 * scale);
        }
        else {
            if (this.on == false) {
                context.fillText("off", this.x + 120 * scale - context.measureText("off").width / 2, this.terminals.PE.get_middle_y() + 5 * scale);
            }
            else {
                if (this.forward == false) {
                    context.fillText("rev", this.x + 120 * scale - context.measureText("rev").width / 2, this.terminals.PE.get_middle_y() + 5 * scale);
                }
                else {
                    context.fillText("fwd", this.x + 120 * scale - context.measureText("fwd").width / 2, this.terminals.PE.get_middle_y() + 5 * scale);
                }
                if (this.delta == false) {
                    context.fillText("star", this.x + 120 * scale - context.measureText("star").width / 2, this.terminals.PE.get_middle_y() + 5 * scale);
                }
                else {
                    context.fillText("delta", this.x + 120 * scale - context.measureText("delta").width / 2, this.terminals.PE.get_middle_y() + 5 * scale);
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