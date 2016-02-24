function RecursiveTreesApp() {
	var INITIAL_LENGTH = 275;
	var BRANCH_LENGTH_DECREASE = 0.65;
	var BRANCH_ANGLES = [Math.PI/4, Math.PI/6, Math.PI/12, -Math.PI/12, -Math.PI/6, -Math.PI/4];
	var MAX_DEPTH = 5;
	var GREEN_DEPTH = 4;
	var LINE_THICKNESS = 5;
	var SPARCITY = 0.7;
	
	var context = null;

	this.init = function () {
		var canvas = document.getElementById('canvas');
		context = canvas.getContext('2d');
		context.lineWidth  = LINE_THICKNESS;
		canvas.addEventListener('click', application.mouseClicked, false);
		drawTree(new Point(CANVAS_WIDTH / 2, CANVAS_HEIGHT), INITIAL_LENGTH, Math.PI / 2, 0, 1);	
	};

	this.mouseClicked = function(ev) {
		clear();
		drawTree(new Point(CANVAS_WIDTH / 2, CANVAS_HEIGHT), INITIAL_LENGTH, Math.PI / 2, 0, SPARCITY);
		return false;
	};
	
	function drawTree(base, length, angle, depth, sparcity) {
		if (depth == MAX_DEPTH) return;
		var color = depth >= GREEN_DEPTH ? 'green' : 'brown';
		var endPoint = drawPolar(base, length, angle, color);
		var branchLength = length * BRANCH_LENGTH_DECREASE;
		for (index in BRANCH_ANGLES) {
			var branchAngle = angle + BRANCH_ANGLES[index];
			if (Math.random() < sparcity) {
				drawTree(endPoint, branchLength, branchAngle, depth + 1, sparcity);
			}
		}
	}
	
	function drawPolar(start, length, angle, color) {
		var dx = length * Math.cos(angle);
		var dy = - (length * Math.sin(angle));
		var end = new Point(start.getX() + dx, start.getY() + dy);
		context.beginPath();
		context.moveTo(start.getX(), start.getY());
		context.lineTo(end.getX(), end.getY());
		context.strokeStyle = color; 
		context.stroke();
		return end;
	}

	function clear() {
		context.fillStyle = "white";
		context.clearRect (0, 0, CANVAS_WIDTH, CANVAS_HEIGHT);
	}
}
