function BoggleApp() {

	var context = null;

	this.init = function () {
		var canvas = document.getElementById('canvas');
		context = canvas.getContext('2d');	
		clear();
		console.println('Boggle will be coming soon!');
	};

	function clear() {
		context.fillStyle = "white";
		context.fillRect (0, 0, CANVAS_WIDTH, CANVAS_HEIGHT);
	}
}
