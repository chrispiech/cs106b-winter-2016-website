// constants
CANVAS_HEIGHT = 500
CANVAS_WIDTH = 730
N_POINTS = 1000;
EDGE_DIST = 25;

// instance variables
points = {}
graph = {}
weights = {}
startNode = null;
endNode = null;
canvas = null;
drawingContext = null;

// point class
function Point(x, y){
  this.x = x || 0;
  this.y = y || 0;
};

// set up the main function
window.onload = init;

function init() {
  initCanvas();
}

/************************************************************
 *                   GRAPH METHODS                          *
 ************************************************************/

function randomGraph() {
  points = []
  graph = {}

  // Make the points
  for(var i = 0; i < N_POINTS; i++) {
    var centerX = (canvas.width) * Math.random();
    var centerY = (canvas.height) * Math.random();
    var point = new Point(centerX, centerY);
    points.push(point);
  }

  // Chose the start and the end
  startNode = randomIndex(points);
  endNode = randomIndex(points);

  // Connect close points and make graph
  for(var i = 0; i < N_POINTS; i++) {
    graph[i] = []
    for(var j = 0; j < i; j++) {
      if(getDist(points[i], points[j]) < EDGE_DIST) {
        graph[i].push(j);
        graph[j].push(i);
      }
    }
  }
}

function drawGraph() {
  drawingContext.clearRect(0, 0, canvas.width, canvas.height);

  // draw edges
  for(nodeId in graph) {
    for(var i = 0; i < graph[nodeId].length; i++) {
      var nextId = graph[nodeId][i];
      drawLine(points[nodeId], points[nextId], "#AAAAAA");
    }
  }

  // draw points
  for(var i = 0; i < points.length; i++) {
    drawCircle(points[i], 2, "black")
  }

  // draw start / end
  drawCircle(points[startNode], 10, "green")
  drawCircle(points[endNode], 10, "red")
}

/************************************************************
 *                  HELPER METHODS                          *
 ************************************************************/

function getDist(point1, point2) {
  var dx = point1.x - point2.x;
  var dy = point1.y - point2.y;
  return Math.sqrt(dx * dx + dy * dy);
}

function randomIndex(arr) {
  return Math.floor(arr.length * Math.random())
}

function randomChoice(arr) {
  return arr[randomIndex(arr)];
}

function deepCopy(arr) {
  var newArr = []
  for(var i = 0; i < arr.length; i++) {
    newArr.push(arr[i]);
  }
  return newArr;
}

function drawCircle(pt, radius, color) {
  drawingContext.fillStyle=color;
  drawingContext.beginPath();
  drawingContext.arc(pt.x, pt.y, radius, 0, 2 * Math.PI, false);
  drawingContext.fill();
}

function drawLine(pt1, pt2, color) {
  drawingContext.strokeStyle = color;
  drawingContext.beginPath();
  drawingContext.moveTo(pt1.x, pt1.y);
  drawingContext.lineTo(pt2.x, pt2.y);
  drawingContext.stroke();
}

function drawPath(path) {
  if(path.length >= 2) {
    var id1 = path[path.length-2]
    var id2 = path[path.length-1]
    drawLine(points[id1], points[id2], "blue");
  }
  var lastId = path[path.length - 1]
  drawCircle(points[lastId], 4, "blue");
}

function highlightPath(path) {
  for(var i = 0; i < path.length; i++) {
    var nodeId = path[i];
    drawCircle(points[nodeId], 6, "red");
    if(i < path.length - 1) {
      var nextId = path[i + 1];
      drawLine(points[nodeId], points[nextId], "red");
    }
  }
}

function initCanvas() {
  canvas = $('#graphCanvas')[0]
  drawingContext = canvas.getContext("2d");
  $('#canvas').height(CANVAS_HEIGHT);
  canvas.width = CANVAS_WIDTH;
  canvas.height = CANVAS_HEIGHT;
}