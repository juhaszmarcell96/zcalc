class CMenu {
    constructor (x, y, canvas, scene) {
        this.canvas = canvas;
        this.context = canvas.getContext('2d');
        this.scene = scene;
        this.x = x;
        this.y = y;

        this.add_resistor_button  = new CButton(10,  10, 150 * scale, 40 * scale, Colors.dark_grey, "resistor");
        this.add_capacitor_button = new CButton(10,  60, 150 * scale, 40 * scale, Colors.dark_grey, "capacitor");
        this.add_inductor_button  = new CButton(10, 110, 150 * scale, 40 * scale, Colors.dark_grey, "inductor");
        this.add_vsource_button   = new CButton(10, 160, 150 * scale, 40 * scale, Colors.dark_grey, "voltage source");
        this.add_csource_button   = new CButton(10, 210, 150 * scale, 40 * scale, Colors.dark_grey, "current source");

        this.resistor_img = new Image();
        this.resistor_img.src = 'assets/svg/resistor.svg';
        this.resistor_img.onerror = function() { console.error("failed to load resistor image"); };
        this.capacitor_img = new Image();
        this.capacitor_img.src = 'assets/svg/capacitor.svg';
        this.capacitor_img.onerror = function() { console.error("failed to load capacitor image"); };
        this.inductor_img = new Image();
        this.inductor_img.src = 'assets/svg/inductor.svg';
        this.inductor_img.onerror = function() { console.error("failed to load inductor image"); };
        this.vsource_img = new Image();
        this.vsource_img.src = 'assets/svg/voltage_source.svg';
        this.vsource_img.onerror = function() { console.error("failed to load voltage source image"); };
        this.csource_img = new Image();
        this.csource_img.src = 'assets/svg/current_source.svg';
        this.csource_img.onerror = function() { console.error("failed to load current source image"); };

        canvas.addEventListener('click', (event) => {
            const x = event.clientX - this.x;
            const y = event.clientY - this.y;
            if (this.add_resistor_button.is_inside(x, y)) {
                this.scene.components.push(new CResistor(50 * scale, 200 * scale, this.resistor_img));
                this.scene.redraw();
            }
            else if (this.add_capacitor_button.is_inside(x, y)) {
                this.scene.components.push(new CCapacitor(50 * scale, 200 * scale, this.capacitor_img));
                this.scene.redraw();
            }
            else if (this.add_inductor_button.is_inside(x, y)) {
                this.scene.components.push(new CInductor(50 * scale, 200 * scale, this.inductor_img));
                this.scene.redraw();
            }
            else if (this.add_vsource_button.is_inside(x, y)) {
                this.scene.components.push(new CVoltageSource(50 * scale, 200 * scale, this.vsource_img));
                this.scene.redraw();
            }
            else if (this.add_csource_button.is_inside(x, y)) {
                this.scene.components.push(new CCurrentSource(50 * scale, 200 * scale, this.csource_img));
                this.scene.redraw();
            }
            event.preventDefault();
        });
    }

    redraw () {
        this.add_resistor_button.draw(this.context);
        this.add_capacitor_button.draw(this.context);
        this.add_inductor_button.draw(this.context);
        this.add_vsource_button.draw(this.context);
        this.add_csource_button.draw(this.context);
    }
};