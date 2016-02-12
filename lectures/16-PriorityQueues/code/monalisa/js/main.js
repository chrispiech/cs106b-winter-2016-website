var CANVAS_WIDTH = 700;
var SMALL_DEFAULT_HEIGHT = 600;
var LARGE_DEFAULT_HEIGHT = 800;
var CANVAS_HEIGHT = SMALL_DEFAULT_HEIGHT;
var application = null;
var console = new Console();

/****************************************************
 *                    MAIN                          *
 ****************************************************/
window.onload = function() {
	$(document).ready(function(){
		$("a").click(function(){
			initProgram(this.id);
			return false;
		});
	});
	initGraphicsConsoleProgram();
	application = new MonaLisaApp();
	application.init();
};

function initProgram(id) {
	if (application && application.finish) application.finish();
	switch(id) {
	case 'boggle': initGraphicsConsoleProgram(); break;
	case 'monaLisa': initGraphicsConsoleProgram(); break;
	case 'breakout': initGraphicsProgram(); break;
	case 'recursiveTrees': initGraphicsProgram(); break;
	default: initConsoleProgram();
	}
	switch(id) {
	case 'breakout':  application = new BreakoutApp(); break;
	case 'balanceParens': application = new BalanceParensApp(); break;
	case 'binaryExplode': application = new BinaryExplodeApp(); break;
	case 'recursiveTrees': application = new RecursiveTreesApp(); break;
	case 'monaLisa': application = new MonaLisaApp(); break;
	case 'boggle': application = new BoggleApp(); break;
	case 'songPath': application = new SongPathApp(); break;
	case 'worldMusic':application = new WorldMusicApp(); break;
	default: alert('unknown id: \"' + id +'\"');
	}
	application.init();
}

function initGraphicsConsoleProgram() {
	canvas = document.getElementById('canvas');
	if(canvas && canvas.getContext) {
		CANVAS_HEIGHT = SMALL_DEFAULT_HEIGHT; 
		console.init();
		$('#canvas').show();
		$('#console').show();
		$('#canvas').height(SMALL_DEFAULT_HEIGHT);
		$('#console').height(LARGE_DEFAULT_HEIGHT - SMALL_DEFAULT_HEIGHT);
		canvas.height = CANVAS_HEIGHT;
		canvas.width = CANVAS_WIDTH;
	} else {
		alert("canvas not supported by your browser");	
	}
}

function initGraphicsProgram() {
	canvas = document.getElementById('canvas');
	if(canvas && canvas.getContext) {
		CANVAS_HEIGHT = LARGE_DEFAULT_HEIGHT;
		$('#canvas').show();
		$('#console').hide();
		$('#canvas').height(LARGE_DEFAULT_HEIGHT);
		canvas.width = CANVAS_WIDTH;
		canvas.height = CANVAS_HEIGHT;
	} else {
		alert("canvas not supported by your browser");	
	}
}

function initConsoleProgram() {
	console.init();
	$('#canvas').hide();
	$('#console').show();
	$('#console').height(CANVAS_HEIGHT);
}
