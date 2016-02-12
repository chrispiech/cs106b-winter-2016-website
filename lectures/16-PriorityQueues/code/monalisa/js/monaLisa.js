function ImageSpecies() {
	var POLYGONS = 50;

	// Each polygon has this many vertices
	var POINTS_PER_POLYGON = 5;

	// Each vertice has an x and a y componenet
	var NUMS_PER_POINT = 2;

	// Colors are composed of RGB and alpha
	var NUMS_PER_COLOR = 4;

	// How many numbers does it take to represent a single polygon?
	var NUMS_PER_POLYGON = (NUMS_PER_POINT*POINTS_PER_POLYGON + NUMS_PER_COLOR);

	// How many numbers go into an individuals DNA?
	var NUMS_PER_DNA = POLYGONS * NUMS_PER_POLYGON;

	var MUTATION_AMOUNT = 0.15;

	this.dna = new Array();
	var fitness = 0;

	this.generateRandomDNA = function() {
		for (var i = 0; i < NUMS_PER_DNA; i += NUMS_PER_POLYGON) {
			// rgba
			this.dna.push(Math.random());
			this.dna.push(Math.random());
			this.dna.push(Math.random());
			this.dna.push(Math.max(0.2,Math.random()*Math.random()));

			var px = Math.random();
			var py = Math.random();

			for (var j = 0; j < NUMS_PER_POLYGON; j++) {
				this.dna.push(px + (Math.random()-0.5));
				this.dna.push(py + (Math.random()-0.5));
			}
		}
	};

	this.calculateFitness = function(context, size, pos, monaLisaData) {
		this.draw(context, size, pos);
		var data = context.getImageData(pos.getX(), pos.getY(), size, size).data;
		var dif = 0;

		for (var i = 0; i < monaLisaData.length; i += NUMS_PER_COLOR) {
			dif += difference(monaLisaData[i+0], data[i+0]); // red
			dif += difference(monaLisaData[i+1], data[i+1]); // green
			dif += difference(monaLisaData[i+2], data[i+2]); // blue
			// skip alpha
		}
		fitness = (1 - dif / (size*size*3*256));
		return fitness;
	};

	this.draw = function(context, size, pos) {
		context.save();
		var x = pos.getX();
		var y = pos.getY();
		context.beginPath();
		context.moveTo(pos.getX(), pos.getY());
		context.lineTo(pos.getX() + size, pos.getY());
		context.lineTo(pos.getX() + size, pos.getY() + size);
		context.lineTo(pos.getX(), pos.getY() + size);
		context.closePath();
		context.clip();
		context.fillStyle = "white";
		context.fillRect(x, y, size, size);

		for (var i = 0; i < NUMS_PER_DNA; i += NUMS_PER_POLYGON) {

			context.beginPath();
			context.moveTo(x + this.dna[i+4] * size, y + this.dna[i+5] * size);

			for (var j=0; j < POINTS_PER_POLYGON - 1; j++) {
				context.lineTo(x + this.dna[i+6+j*2] * size, y + this.dna[i+7+j*2] * size);
			}

			context.fillStyle = "rgba(" + ((this.dna[i]*255)>>0) + "," + ((this.dna[i+1]*255)>>0) + "," + ((this.dna[i+2]*255)>>0) + "," + this.dna[i+3] + ")";
			context.fill();	
		}
		context.restore();

	};

	this.update = function(context, size, pos, monaLisaData) {
		var indexChanged = Math.floor(Math.random()*NUMS_PER_DNA);
		var oldValue = this.dna[indexChanged];
		var oldFitness = fitness;
		this.dna[indexChanged] += Math.random() * MUTATION_AMOUNT - (MUTATION_AMOUNT/2);

		var newFitness = this.calculateFitness(context, size, pos, monaLisaData);
		if (newFitness < oldFitness) {
			fitness = oldFitness;
			this.dna[indexChanged] = oldValue;
		} 
		return newFitness > oldFitness;
	};

	function difference(a, b) {
		return Math.abs(a - b);
	};
}

function MonaLisaApp() {
	var MONA_LISA_X = 100;
	var EXPERIMENT_Y = 265;
	var SPECIES_X = 400;
	var IMAGE_SIZE = 200;
	var HEART_BEAT = 5;
	var BORDER_SIZE = 5;

	var context = null;
	var monaLisa = new Image();
	monaLisa.src = 'images/monalisa.png';
	var monaLisaPos = new Point(MONA_LISA_X, EXPERIMENT_Y);
	var speciesPos = new Point(SPECIES_X, EXPERIMENT_Y);
	var bestPos = new Point((CANVAS_WIDTH - IMAGE_SIZE) / 2, 25);
	var monaLisaData = null;

	var fittest = new ImageSpecies();
	var timeout = null;

	this.finish = function() {
		if(timeout) {
			clearTimeout(timeout);
		}
	};

	this.init = function () {
		var canvas = document.getElementById('canvas');
		context = canvas.getContext('2d');
		clear();
		loadImage();
		console.println("Evolutionary Art!");
		console.println("The goal of this program is to recreate an image using only 50 colored polygons. " +
				"This algorithm searches for a global maximum in a very high dimensional space!" +
				"It can take up to 15 minutes for the " +
				"random polygons to start to resemble the original. The top image is the best image made so far, " +
				"the left image is the original and the right image is the last image created.");
		console.println("You can load monalisa.png, mondrian.png or firefox.jpg");
		console.readImagename("Enter the file you would like to evolve:", evolve);
	};
	
	function evolve(filename) {
		if (timeout) clearTimeout(timeout);
		clear();
		monaLisa.src = 'images/' + filename;
		fittest = new ImageSpecies();
		loadImage();
		console.readImagename("Enter the file you would like to evolve:", evolve);
	}

	function loadImage() {
		if (monaLisa.complete) {
			fittest.generateRandomDNA();
			context.drawImage(monaLisa, monaLisaPos.getX(), monaLisaPos.getY());	
			monaLisaData = context.getImageData(monaLisaPos.getX(), monaLisaPos.getY(), IMAGE_SIZE, IMAGE_SIZE).data;
			fittestFitness = fittest.calculateFitness(context, IMAGE_SIZE, speciesPos, monaLisaData);
			timeout = setTimeout(update, HEART_BEAT);
		} else {
			timeout = setTimeout(loadImage, 100 ) ;	  
		}
	}

	function update() {
		if(fittest.update(context, IMAGE_SIZE, speciesPos, monaLisaData)) {
			fittest.draw(context, IMAGE_SIZE, bestPos);
		}
		timeout = setTimeout(update, HEART_BEAT);
	}


	function clear() {
		context.fillStyle = "white";
		context.fillRect (0, 0, CANVAS_WIDTH, CANVAS_HEIGHT);
		context.fillStyle = "black";
		var imagePositions = [monaLisaPos, bestPos, speciesPos];
		for (index in imagePositions){
			var pos = imagePositions[index];
			context.fillRect(pos.getX() - BORDER_SIZE,
					pos.getY() - BORDER_SIZE, 
					IMAGE_SIZE + 2 * BORDER_SIZE,
					IMAGE_SIZE + 2 * BORDER_SIZE);
		}
	}
}
