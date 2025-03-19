/* Copyright (C) 2025 Marcell Juhasz. Licensed for non-commercial use. See LICENSE. */

import { scale, Colors } from "./defines";
import { CResistor } from "./components/microelectronics/resistor";
import { CCapacitor } from "./components/microelectronics/capacitor";
import { CInductor } from "./components/microelectronics/inductor";
import { CVoltageSource } from "./components/microelectronics/voltage_source";
import { CCurrentSource } from "./components/microelectronics/current_source";
import { CVoltageControlledVoltageSource } from "./components/microelectronics/voltage_controlled_voltage_source";
import { CCurrentControlledVoltageSource } from "./components/microelectronics/current_controlled_voltage_source";
import { CVoltageControlledCurrentSource } from "./components/microelectronics/voltage_controlled_current_source";
import { CCurrentControlledCurrentSource } from "./components/microelectronics/current_controlled_current_source";
import { CCoupledInductor } from "./components/microelectronics/coupled_inductor";
import { CIdealTransformer } from "./components/microelectronics/ideal_transformer";
import { CGyrator } from "./components/microelectronics/gyrator";
import { CIdealAmplifier } from "./components/microelectronics/ideal_amplifier";
import { CVoltmeter } from "./components/microelectronics/voltmeter";
import { CAmmeter } from "./components/microelectronics/ammeter";
import { CButton } from "./button";

export class CMenu {
    constructor (x, y, canvas, scene) {
        this.canvas = canvas;
        this.context = canvas.getContext('2d');
        this.scene = scene;
        this.x = x;
        this.y = y;

        this.offset_y = 0;

        canvas.addEventListener("wheel", (event) => {
            if (event.deltaY < 0) { // scroll up
                this.offset_y += 20;
            }
            else { // scroll down
                this.offset_y -= 20;
            }
            if (this.offset_y > 0) {
                this.offset_y = 0;
            }
            const max_scroll_down = 900 - this.canvas.height;
            if (this.offset_y < -max_scroll_down) {
                this.offset_y = -max_scroll_down;
            }
        
            this.redraw();
            event.preventDefault();
        });

        const x_offset = 10 * scale;
        const button_w = this.canvas.width - 2 * x_offset;
        this.add_resistor_button  = new CButton(x_offset,  10, button_w, 40 * scale, Colors.dark_grey, "resistor");
        this.add_capacitor_button = new CButton(x_offset,  60, button_w, 40 * scale, Colors.dark_grey, "capacitor");
        this.add_inductor_button  = new CButton(x_offset, 110, button_w, 40 * scale, Colors.dark_grey, "inductor");
        this.add_vsource_button   = new CButton(x_offset, 160, button_w, 40 * scale, Colors.dark_grey, "voltage source");
        this.add_csource_button   = new CButton(x_offset, 210, button_w, 40 * scale, Colors.dark_grey, "current source");
        this.add_vcvsource_button = new CButton(x_offset, 260, button_w, 70 * scale, Colors.dark_grey, "voltage controlled\nvoltage source");
        this.add_ccvsource_button = new CButton(x_offset, 340, button_w, 70 * scale, Colors.dark_grey, "current controlled\nvoltage source");
        this.add_vccsource_button = new CButton(x_offset, 420, button_w, 70 * scale, Colors.dark_grey, "voltage controlled\ncurrent source");
        this.add_cccsource_button = new CButton(x_offset, 500, button_w, 70 * scale, Colors.dark_grey, "current controlled\ncurrent source");
        this.add_cinductor_button = new CButton(x_offset, 580, button_w, 40 * scale, Colors.dark_grey, "coupled inductor");
        this.add_ideal_t_button   = new CButton(x_offset, 630, button_w, 40 * scale, Colors.dark_grey, "ideal transformer");
        this.add_gyrator_button   = new CButton(x_offset, 680, button_w, 40 * scale, Colors.dark_grey, "gyrator");
        this.add_amplifier_button = new CButton(x_offset, 730, button_w, 40 * scale, Colors.dark_grey, "ideal amplifier");
        this.add_voltmeter_button = new CButton(x_offset, 780, button_w, 40 * scale, Colors.dark_grey, "voltmeter");
        this.add_ammeter_button   = new CButton(x_offset, 830, button_w, 40 * scale, Colors.dark_grey, "ammeter");

        // basic components
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
        
        // dependent sources
        this.dvsource_img = new Image();
        this.dvsource_img.src = 'assets/svg/dependent_voltage_source.svg';
        this.dvsource_img.onerror = function() { console.error("failed to load dependent voltage source image"); };
        this.dcsource_img = new Image();
        this.dcsource_img.src = 'assets/svg/dependent_current_source.svg';
        this.dcsource_img.onerror = function() { console.error("failed to load dependent current source image"); };
        
        // four-poles
        this.cinductor_img = new Image();
        this.cinductor_img.src = 'assets/svg/coupled_inductor.svg';
        this.cinductor_img.onerror = function() { console.error("failed to load coupled inductor image"); };
        this.ideal_transformer_img = new Image();
        this.ideal_transformer_img.src = 'assets/svg/ideal_transformer.svg';
        this.ideal_transformer_img.onerror = function() { console.error("failed to load ideal transformer image"); };
        this.gyrator_img = new Image();
        this.gyrator_img.src = 'assets/svg/gyrator.svg';
        this.gyrator_img.onerror = function() { console.error("failed to load gyrator image"); };
        this.amplifier_img = new Image();
        this.amplifier_img.src = 'assets/svg/ideal_amplifier.svg';
        this.amplifier_img.onerror = function() { console.error("failed to load ideal amplifier image"); };

        // measurement
        this.voltmeter_img = new Image();
        this.voltmeter_img.src = 'assets/svg/voltmeter.svg';
        this.voltmeter_img.onerror = function() { console.error("failed to load voltmeter image"); };
        this.ammeter_img = new Image();
        this.ammeter_img.src = 'assets/svg/ammeter.svg';
        this.ammeter_img.onerror = function() { console.error("failed to load ammeter image"); };

        canvas.addEventListener('click', (event) => {
            const x = event.clientX - this.x;
            const y = event.clientY - this.y - this.offset_y;
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
            else if (this.add_vcvsource_button.is_inside(x, y)) {
                this.scene.components.push(new CVoltageControlledVoltageSource(50 * scale, 200 * scale, this.dvsource_img));
                this.scene.redraw();
            }
            else if (this.add_ccvsource_button.is_inside(x, y)) {
                this.scene.components.push(new CCurrentControlledVoltageSource(50 * scale, 200 * scale, this.dvsource_img));
                this.scene.redraw();
            }
            else if (this.add_vccsource_button.is_inside(x, y)) {
                this.scene.components.push(new CVoltageControlledCurrentSource(50 * scale, 200 * scale, this.dcsource_img));
                this.scene.redraw();
            }
            else if (this.add_cccsource_button.is_inside(x, y)) {
                this.scene.components.push(new CCurrentControlledCurrentSource(50 * scale, 200 * scale, this.dcsource_img));
                this.scene.redraw();
            }
            else if (this.add_cinductor_button.is_inside(x, y)) {
                this.scene.components.push(new CCoupledInductor(50 * scale, 200 * scale, this.cinductor_img));
                this.scene.redraw();
            }
            else if (this.add_ideal_t_button.is_inside(x, y)) {
                this.scene.components.push(new CIdealTransformer(50 * scale, 200 * scale, this.ideal_transformer_img));
                this.scene.redraw();
            }
            else if (this.add_gyrator_button.is_inside(x, y)) {
                this.scene.components.push(new CGyrator(50 * scale, 200 * scale, this.gyrator_img));
                this.scene.redraw();
            }
            else if (this.add_amplifier_button.is_inside(x, y)) {
                this.scene.components.push(new CIdealAmplifier(50 * scale, 200 * scale, this.amplifier_img));
                this.scene.redraw();
            }
            else if (this.add_voltmeter_button.is_inside(x, y)) {
                this.scene.components.push(new CVoltmeter(50 * scale, 200 * scale, this.voltmeter_img));
                this.scene.redraw();
            }
            else if (this.add_ammeter_button.is_inside(x, y)) {
                this.scene.components.push(new CAmmeter(50 * scale, 200 * scale, this.ammeter_img));
                this.scene.redraw();
            }
            event.preventDefault();
        });
    }

    redraw () {
        this.context.clearRect(0, 0, this.canvas.width, this.canvas.height);
        this.context.translate(0, this.offset_y);
        this.add_resistor_button.draw(this.context);
        this.add_capacitor_button.draw(this.context);
        this.add_inductor_button.draw(this.context);
        this.add_vsource_button.draw(this.context);
        this.add_csource_button.draw(this.context);
        this.add_vcvsource_button.draw(this.context);
        this.add_ccvsource_button.draw(this.context);
        this.add_vccsource_button.draw(this.context);
        this.add_cccsource_button.draw(this.context);
        this.add_cinductor_button.draw(this.context);
        this.add_ideal_t_button.draw(this.context);
        this.add_gyrator_button.draw(this.context);
        this.add_amplifier_button.draw(this.context);
        this.add_voltmeter_button.draw(this.context);
        this.add_ammeter_button.draw(this.context);
        this.context.translate(0, -this.offset_y);
    }
};