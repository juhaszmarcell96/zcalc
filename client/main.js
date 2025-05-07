/* Copyright (C) 2025 Marcell Juhasz. Licensed for non-commercial use. See LICENSE. */

import { CScene } from "./src/scene";
import { CMenu } from "./src/menu";
import { CEditArea } from "./src/edit_area";

var playground = document.getElementById('playground');
var menuCanvas = document.getElementById('menu');
var editAreaCanvas = document.getElementById('edit_area');
var editAreaInput = document.getElementById('editAreaInput');

playground.style.position = 'absolute';
playground.style.left = 0 + 'px';
playground.style.top = 0 + 'px';
playground.width = 3.0/4.0 * window.innerWidth;
playground.height = window.innerHeight;

menuCanvas.style.position = 'absolute';
menuCanvas.style.left = 3.0/4.0 * window.innerWidth + 'px';
menuCanvas.style.top = 0 + 'px';
menuCanvas.width = 1.0/4.0 * window.innerWidth;
menuCanvas.height = 8.0/10.0 * window.innerHeight;

editAreaCanvas.style.position = 'absolute';
editAreaCanvas.style.left = 3.0/4.0 * window.innerWidth + 'px';
editAreaCanvas.style.top = 8.0/10.0 * window.innerHeight + 'px';
editAreaCanvas.width = 1.0/4.0 * window.innerWidth;
editAreaCanvas.height = 2.0/10.0 * window.innerHeight;

var scene = new CScene(playground);
var menu = new CMenu(3.0/4.0 * window.innerWidth, 0, menuCanvas, scene);
var edit_area = new CEditArea(3.0/4.0 * window.innerWidth, 8.0/10.0 * window.innerHeight, editAreaCanvas, scene, editAreaInput);
scene.set_edit_area(edit_area);

scene.redraw();
menu.redraw();
edit_area.redraw();