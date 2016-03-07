// constants
CANVAS_HEIGHT = 500
CANVAS_WIDTH = 730
COLORS = ["red", "blue", "magenta", "green", "orange", "yellow"];

// instance variables
canvas = null;
drawingContext = null;

// set up the main function
window.onload = init;

function init() {
  initCanvas();
  console.log("this is a test")
}

/**
 * Function: Draw Circle
 * ---------------------
 * Drawing circles using the "native" methods is a little
 * clunky so I wrote this helper funciton. Color is a string
 */ 
function drawCircle(x, y, radius, color) {
  drawingContext.fillStyle = color;
  drawingContext.beginPath();
  drawingContext.arc(x, y, radius, 0, 2 * Math.PI, false);
  drawingContext.fill();
}

/**
 * Function: Init Canvas
 * ---------------------
 * Sets up the canvas to be the right size and assigns global
 * variables "canvas" and "drawingContext"
 */ 
function initCanvas() {
  canvas = document.getElementById('graphCanvas')
  drawingContext = canvas.getContext("2d");
  canvas.style.height = CANVAS_HEIGHT + "px";
  canvas.width = CANVAS_WIDTH;
  canvas.height = CANVAS_HEIGHT;
}