/* Copyright (C) 2025 Marcell Juhasz. Licensed for non-commercial use. See LICENSE. */

import { scale, WireType, Colors } from "./defines";
import { CButton } from "./controls/button";
import { CWire } from "./wire";

export class CScene {
    screen_to_canvas (x, y) {
        return {
            x: (x - this.offset_x) / this.scale,
            y: (y - this.offset_y) / this.scale
        };
    }

    get_component_at(x, y) {
        return this.components.find(component => component.is_inside(x, y));
    }

    get_terminal_at(x, y) {
        for (const component of this.components){
            let terminal = component.get_terminal_at(x, y);
            if (terminal) { return terminal; }
        }
        return null;
    }

    constructor (canvas) {
        this.canvas = canvas;
        this.context = canvas.getContext('2d');
        this.scale = 1.0;
        this.offset_x = 0.0;
        this.offset_y = 0.0;
        this.selected = null;
        this.panning = false;
        this.dragging = false;
        this.last_x = 0.0;
        this.last_y = 0.0
        this.components = [];
        this.new_wire = null;
        this.wire_type = WireType.L;

        this.edit_area = null;

        this.del_button = null;
        this.rotate_button = null;
        this.edit_button = null;
        this.context_menu = false;
        this.context_component_index = -1;

        canvas.addEventListener("wheel", (event) => {
            const { x, y } = this.screen_to_canvas(event.clientX, event.clientY);
            const zoomFactor = 1.1;
            
            if (event.deltaY < 0) { // Zoom in
                if (this.scale < 2.0) {
                    this.scale *= zoomFactor;
                }
            }
            else { // Zoom out
                if (this.scale > 0.5) {
                    this.scale /= zoomFactor;
                }
            }
        
            // Adjust offset to zoom towards cursor
            this.offset_x = event.clientX - x * this.scale;
            this.offset_y = event.clientY - y * this.scale;
        
            this.redraw();
            event.preventDefault();
        });
        canvas.addEventListener("mousedown", (event) => {
            const { x, y } = this.screen_to_canvas(event.clientX, event.clientY);
            this.last_x = event.clientX;
            this.last_y = event.clientY;
        
            if (event.button === 0) { // Left click (select object)
                const terminal = this.get_terminal_at(x, y);
                if (terminal) {
                    this.new_wire = new CWire(this.wire_type);
                    this.new_wire.start(terminal.x, terminal.y);
                }
                else {
                    this.selected = this.get_component_at(x, y);
                    if (this.selected) {
                        this.dragging = true;
                    }
                }
            }
            else if (event.button === 1) { // Middle click (pan)
                this.panning = true;
            }
            event.preventDefault();
        });
        canvas.addEventListener("mousemove", (event) => {
            const { x, y } = this.screen_to_canvas(event.clientX, event.clientY);
            
            if (this.new_wire) {
                this.new_wire.wire(x, y);
                this.redraw();
            }
            else if (this.dragging && this.selected) {
                this.selected.move((event.clientX - this.last_x) / this.scale, (event.clientY - this.last_y) / this.scale);
                this.redraw();
            }
            else if (this.panning) {
                this.offset_x += event.clientX - this.last_x;
                this.offset_y += event.clientY - this.last_y;
                this.redraw();
            }
            
            this.last_x = event.clientX;
            this.last_y = event.clientY;
        });
        canvas.addEventListener("mouseup", () => {
            if (this.dragging && this.selected) {
                this.selected.snap_to_grid();
            }
            this.dragging = false;
            this.panning = false;
            this.selected = null;
            const { x, y } = this.screen_to_canvas(event.clientX, event.clientY);
            if (this.new_wire) {
                this.new_wire.stop(x, y);
                this.components.push(this.new_wire);
                this.new_wire = null;
            }
            this.redraw();
        });
        canvas.addEventListener("contextmenu", (event) => {
            const { x, y } = this.screen_to_canvas(event.clientX, event.clientY);
            this.context_component_index = [...this.components].reverse().findIndex(component => component.is_inside(x, y));
            if (this.context_component_index !== -1) {
                this.del_button = new CButton(x, y, 75 * scale, 40 * scale, Colors.red, "delete");
                this.rotate_button = new CButton(x, y + this.del_button.h, 75 * scale, 40 * scale, Colors.dark_grey, "rotate");
                this.edit_button = new CButton(x, y + this.del_button.h + this.rotate_button.h, 75 * scale, 40 * scale, Colors.dark_grey, "edit");
                this.context_menu = true;
            }
            event.preventDefault();
            this.redraw();
        });
        canvas.addEventListener('click', (event) => {
            const { x, y } = this.screen_to_canvas(event.clientX, event.clientY);
            if (this.context_menu) {
                if (this.del_button.is_inside(x, y)) {
                    this.components.splice(this.components.length - 1 - this.context_component_index, 1);
                }
                else if (this.rotate_button.is_inside(x, y)) {
                    this.components[this.components.length - 1 - this.context_component_index].rotate();
                }
                else if (this.edit_button.is_inside(x, y)) {
                    if (this.edit_area) {
                        this.edit_area.populate(this.components[this.components.length - 1 - this.context_component_index]);
                    }
                }
            }
            this.context_menu = false;
            this.del_button = null;
            this.rotate_button = null;
            this.edit_button = null;
            event.preventDefault();
            this.redraw();
        });
    }

    draw_cursor_helper () {
        /* draw cursor */
        const [ x, y ] = this.new_wire.get_end();
        this.context.beginPath();
        this.context.lineWidth = 2 * scale;
        this.context.moveTo(-this.offset_x / this.scale, y);
        this.context.lineTo((-this.offset_x + this.canvas.width) / this.scale, y);
        this.context.moveTo(x, -this.offset_y / this.scale);
        this.context.lineTo(x, (-this.offset_y + this.canvas.height) / this.scale);
        this.context.strokeStyle = 'rgba(255, 0, 0, 0.5)';
        this.context.stroke();
        this.context.closePath();
    }

    redraw () {
        //console.log("redraw");
        this.context.setTransform(this.scale, 0, 0, this.scale, this.offset_x, this.offset_y);
        this.context.clearRect(-this.offset_x / this.scale, -this.offset_y / this.scale, this.canvas.width / this.scale, this.canvas.height / this.scale);
        this.components.forEach(component => {
            component.draw(this.context);
        });
        if (this.new_wire) {
            this.new_wire.draw(this.context);
            this.draw_cursor_helper();
        }
        if (this.context_menu) {
            this.del_button.draw(this.context);
            this.rotate_button.draw(this.context);
            this.edit_button.draw(this.context);
        }
    }

    calculate_nodes () {
        let nodes = [];
        this.components.forEach(component => {
            component.get_nodes(nodes, null, 2);
        });
        let found_change = true;
        while (found_change) {
            found_change = false;

            // try to merge every pair of nodes
            for (let i = 0; i < nodes.length; ++i) {
                for (let j = i + 1; j < nodes.length; ++j) {
                    if (!nodes[i] || !nodes[j]) { continue; }
                    if (nodes[i].merge_if_same_node(nodes[j])) {
                        // if merged, mark change and clear the merged node
                        found_change = true;
                        nodes[j] = null; // mark for deletion
                    }
                }
            }
    
            // clean up merged nodes
            nodes = nodes.filter(node => node && !node.empty());
        }
        let node_id = 0;
        nodes.forEach(node => {
            node.mark(node_id);
            ++node_id;
        });
    }

    to_json () {
        this.calculate_nodes();
        let json_data = {
            c: []
        };
        let index = 0;
        this.components.forEach(component => {
            const serialized = component.serialize(index);
            if (serialized)
            {
                json_data.c.push(serialized);
                ++index;
            }
        });
        console.log(JSON.stringify(json_data, null, "    "));
    }

    set_edit_area (edit_area) {
        this.edit_area = edit_area;
    }

};