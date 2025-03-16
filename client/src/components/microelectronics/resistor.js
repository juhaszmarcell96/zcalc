class CResistor extends IComponent {
    constructor (x, y) {
        super(x, y, 90 * scale, 20 * scale);
        const terminal_0_x = -this.w / 2 - 10 * scale;
        const terminal_1_x = -this.w / 2 + this.w + 10 * scale;
        const terminal_0_y = this.h / 2 - 10 * scale;
        const terminal_1_y = this.h / 2 - 10 * scale;
        this.terminals = {
            T1: new CTerminal(terminal_0_x, terminal_0_y, Colors.l3),
            T2: new CTerminal(terminal_1_x, terminal_1_y, Colors.l3)
        }
        this.angle = 0;

        this.img = new Image();
        this.img.src = 'assets/svg/resistor.svg';
    }

    rotate () {
        this.angle += 1;
        if (this.angle == 4) {
            this.andle = 0;
        }
    }

    draw (context) {
        context.translate(this.x + this.w / 2, this.y + this.h / 2);
        context.rotate(this.angle * Math.PI / 2);
        context.drawImage(this.img, -this.w / 2, -this.h / 2, this.w, this.h + 10 * scale);
        this.draw_terminals(context);
        context.rotate(-1 * this.angle * Math.PI / 2);
        context.translate(-(this.x + this.w / 2), -(this.y + this.h / 2));
    }

    do_stuff () {
        // nothing to do
    }
};