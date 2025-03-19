/* Copyright (C) 2025 Marcell Juhasz. Licensed for non-commercial use. See LICENSE. */

import { CScene } from "./src/scene";
import { CMenu } from "./src/menu";

var playground = document.getElementById('playground');
var menuCanvas = document.getElementById('menu');

playground.style.position = 'absolute';
playground.style.left = 0 + 'px';
playground.style.top = 0 + 'px';
playground.width = 3.0/4.0 * window.innerWidth;
playground.height = window.innerHeight;

menuCanvas.style.position = 'absolute';
menuCanvas.style.left = 3.0/4.0 * window.innerWidth + 'px';
menuCanvas.style.top = 0 + 'px';
menuCanvas.width = 1.0/4.0 * window.innerWidth;
menuCanvas.height = window.innerHeight;

var scene = new CScene(playground);
var menu = new CMenu(3.0/4.0 * window.innerWidth, 0, menuCanvas, scene);

const resistor_img = new Image();
resistor_img.src = 'assets/svg/resistor.svg';
resistor_img.onload = function() { scene.redraw(); };
resistor_img.onerror = function() { console.error("failed to load resistor image"); };

scene.redraw();
menu.redraw();