/**

 * This is what breakout looks like in JavaScript!

 * I don't have time to comment! <- Typical Student

 **/

function BreakoutApp() {

	// constants
	var HEART_BEAT = 2;	
	var PADDLE_WIDTH = 100;
	var PADDLE_HEIGHT = 10;
	var PADDLE_Y = CANVAS_HEIGHT - 20;
	var MAX_PADDLE_X = CANVAS_WIDTH - PADDLE_WIDTH;
	var NUM_BRICK_ROWS = 10;
	var NUM_BRICK_COLS = 10;
	var BRICK_HEIGHT = 10;
	var BRICK_SPACING = 8;
	var BRICK_WIDTH = ((CANVAS_WIDTH - BRICK_SPACING) / NUM_BRICK_COLS) - BRICK_SPACING;
	var BRICK_Y_SPACING = 40; 
	var BALL_RADIUS = 10;

	// instance variables
	var context = null;
	var paddleX = 0;
	var ball = new Point(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2);
	var ballVelocity = new Point(2, 3);
	var bricks = new Array();
	var heartbeatInterval = null;

	this.finish = function () {
		if(heartbeatInterval) {
			clearInterval(heartbeatInterval);
		}
	};

	this.init = function () {

		var canvas = document.getElementById('canvas');

		context = canvas.getContext('2d');

		canvas.addEventListener('mousemove', application.mouseMoved, false);

		for (var i = 0; i < NUM_BRICK_ROWS; i++) {

			bricks[i] = new Array();

			for (var j = 0; j < NUM_BRICK_COLS; j++) {

				bricks[i][j] = true;

			}

		}

		heartbeatInterval = setInterval(application.heartbeat, HEART_BEAT);

	};



	this.mouseMoved = function(ev) {

		var mouse = getMousePoint(ev);

		paddleX = mouse.getX() - PADDLE_WIDTH / 2.0;

		if (paddleX < 0) paddleX = 0;

		if (paddleX > MAX_PADDLE_X) paddleX = MAX_PADDLE_X;

	};



	this.heartbeat = function() {

		update();

		draw();

	};



	function update() {

		ball.setX(ball.getX() + ballVelocity.getX());

		ball.setY(ball.getY() + ballVelocity.getY());



		if (ball.getX() < 0 || ball.getX() > CANVAS_WIDTH) {

			ballVelocity.setX(-ballVelocity.getX());

		} else if (ball.getY() < 0 || ball.getY() > CANVAS_HEIGHT) {

			ballVelocity.setY(-ballVelocity.getY());

		}



		if (collidesWithPaddle()) {

			ballVelocity.setY(-Math.abs(ballVelocity.getY()));

		}

		if (collidesWithBrick()) {

			ballVelocity.setY(-ballVelocity.getY());

		} 

	}



	function draw() {

		clear();

		drawPaddle();

		drawBricks();

		drawBall();

	}



	function drawBall() {

		context.fillStyle = "blue";

		context.beginPath();

		context.arc(ball.getX(), ball.getY(), BALL_RADIUS, 0, Math.PI*2, true); 

		context.closePath();

		context.fill();

	}



	function drawBricks() {

		for (var row = 0; row < NUM_BRICK_ROWS; row++) {

			for (var col = 0; col < NUM_BRICK_COLS; col++) {  

				context.fillStyle = getRowColor(row);  

				if (bricks[row][col]) {

					var y = getBrickY(row);

					var x = getBrickX(col);

					context.fillRect(x, y, BRICK_WIDTH, BRICK_HEIGHT);

				}

			}

		}

	}



	function getBrickY(row) {

		return BRICK_Y_SPACING + row * (BRICK_HEIGHT + BRICK_SPACING);

	}



	function getBrickX(col) {

		return BRICK_SPACING + col * (BRICK_WIDTH + BRICK_SPACING);

	}



	function getRowColor(row){

		switch(row % 5){

		case 0: return "red";

		case 1: return "orange";

		case 2: return "lightgreen";

		case 3: return "lightblue";

		case 4: return "pink";

		}

	}



	function pointCollidesWithBrick(point) {

		var collided = false;

		for (var i = 0; i < NUM_BRICK_ROWS; i++) {

			for (var j = 0; j < NUM_BRICK_COLS; j++) {

				var brickX = getBrickX(j);

				var brickY = getBrickY(i);

				if (bricks[i][j]) {

					if (point.getX() > brickX && point.getX() < brickX + BRICK_WIDTH){

						if (point.getY() > brickY && point.getY() < brickY + BRICK_HEIGHT) {

							bricks[i][j] = false;

							collided = true;

						}

					}

				}

			}

		}

		return collided;

	}



	function getCollisionPoints() {

		points = new Array();

		points[0] = new Point(ball.getX(), ball.getY() - BALL_RADIUS);

		points[1] = new Point(ball.getX() + BALL_RADIUS, ball.getY());

		points[2] = new Point(ball.getX(), ball.getY() - BALL_RADIUS);

		points[3] = new Point(ball.getX() - BALL_RADIUS, ball.getY());

		return points;

	}



	function collidesWithBrick() {

		for (i in getCollisionPoints()) {

			if (pointCollidesWithBrick(points[i])) return true;

		}

		return false;

	}



	function collidesWithPaddle() {

		for (i in getCollisionPoints()) {

			if (pointCollidesWithPaddle(points[i])) return true;

		}

		return false;

	}



	function pointCollidesWithPaddle(point){

		if (point.getY() > PADDLE_Y) {

			if (point.getX() > paddleX && point.getX() < paddleX + PADDLE_WIDTH) {

				return true;

			}

		}

		return false;

	}



	function drawPaddle() {

		context.fillStyle = "black";

		context.fillRect(paddleX, PADDLE_Y, PADDLE_WIDTH, PADDLE_HEIGHT);

	}



	function clear() {

		context.fillStyle = "white";

		context.fillRect(0, 0, CANVAS_WIDTH, CANVAS_HEIGHT);

	}

}