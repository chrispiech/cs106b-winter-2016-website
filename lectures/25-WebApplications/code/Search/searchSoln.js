// constants
CANVAS_HEIGHT = 500
CANVAS_WIDTH = 730
ANIMATION_PAUSE = 10

// instance variables
points = {}
graph = {}
weights = {}
startId = null;
endId = null;
canvas = null;
drawingContext = null;

// point class
function Point(x, y){
  this.x = x || 0;
  this.y = y || 0;
};

window.onload = init;

function init() {
  initCanvas();
  randomGraph(500, 40);
  drawGraph();
  document.getElementById("bfsButton").onclick = runBFS;
}

function runBFS() {
  var path = findPath();
  if(path != null) {
    highlightPath(path);
    document.getElementById("hopsNum").innerHTML = path.length;
  }
}

function findPath() {
  var queue = new Queue();
  var seen = {}
  queue.enqueue([startId]);
  while(!queue.isEmpty()) {
    var currPath = queue.dequeue();
    var nextId = currPath[currPath.length - 1];
    if(nextId in seen) continue;
    drawPath(currPath);
    if(nextId == endId) {
      return currPath;
    }
    seen[nextId] = true;
    for(var i = 0; i < graph[nextId].length; i++) {
      var child = graph[nextId][i];
      var newPath = deepCopy(currPath);
      newPath.push(child);
      queue.enqueue(newPath);
    }
  }
  return null;
}

/************************************************************
 *                   GRAPH METHODS                          *
 ************************************************************/

function randomGraph(nPoints, edgeDist) {
  points = []
  graph = {}
  for(var i = 0; i < nPoints; i++) {
    var centerX = (canvas.width) * Math.random();
    var centerY = (canvas.height) * Math.random();
    var point = new Point(centerX, centerY);
    points.push(point);
    graph[i] = []
  }

  startId = randomIndex(points);
  endId = randomIndex(points);

  for(var i = 0; i < nPoints; i++) {
    for(var j = 0; j < i; j++) {
      if(getDist(points[i], points[j]) < edgeDist) {
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
  drawCircle(points[startId], 10, "green")
  drawCircle(points[endId], 10, "red")
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
  $("#hopsNum").html(path.length);
}

function initCanvas() {
  canvas = $('#graphCanvas')[0]
  drawingContext = canvas.getContext("2d");
  $('#canvas').height(CANVAS_HEIGHT);
  canvas.width = CANVAS_WIDTH;
  canvas.height = CANVAS_HEIGHT;
}