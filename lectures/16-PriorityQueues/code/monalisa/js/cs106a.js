function Point(x,y) {
	this.x = x;
	this.y = y;

	this.setX = function(x) {
		this.x = x;
	};

	this.setY = function(y) {
		this.y = y;
	};

	this.setPos = function(x, y) {
		this.x = x;
		this.y = y;	
	};

	this.getX = function() {
		return this.x;
	};

	this.getY = function() {
		return this.y;
	};

	this.distance = function(other) {
		var dx = this.x - other.getX();
		var dy = this.y - other.getY();
		return Math.sqrt(dx*dx + dy*dy);
	};
}

function getMousePoint(ev) {
	return getMousePositionInElement(canvas, ev);
}

function getMousePositionInElement(element, e) {
	var elementPosition = getElementPosition(element);
	var mousePosition = getMousePosition(e);
	var x = mousePosition.x - elementPosition.x;
	var y = mousePosition.y - elementPosition.y;
	var position = new Point(x, y);
	return position;
}

function getMousePosition(e) {
	var x = (window.event) ? window.event.clientX : e.pageX;
	var y = (window.event) ? window.event.clientY : e.pageY;
	var mousePosition = new Point(x, y);
	return mousePosition;
}

function getElementPosition(element) {
	var posX = element.offsetLeft;
	var posY = element.offsetTop;
	try {
		while(element.offsetParent){
			posX += element.offsetParent.offsetLeft;
			posY += element.offsetParent.offsetTop;
			if(element == document.getElementsByTagName('body')[0]){
				break;
			}
			else{
				element = element.offsetParent;
			}
		}
	}
	catch(e) {
		alert(e.message);
	}
	var dims = new Point(posX, posY);
	return dims;
}



function Console() { 

	var _win; // a top-level context
	var question;
	var _in;
	var _out;
	var _console;
	var readValueCallback;
	var readIntCallback;
	var readIntPrompt;

	this.clear = function() {
		_out.innerHTML = '';
	};

	this.finished = function() {
		println(" ", "print");
		println("Program Finished", "print");
	};

	this.println = function(output) {
		if (output == '') output = ' ';
		println(output, "print");
	};

	this.readInt = function(prompt, callback) {
		readIntPrompt = prompt;
		readIntCallback = callback;
		readIntWrapper(prompt, callback);
	};
	
	this.readImagename = function(prompt, callback) {
		readLineWrapper(prompt, callback);
	};

	function readIntWrapper(prompt, callback) {
		readLineWrapper(prompt, readIntCheck);
	}

	function readIntCheck(text) {
		if (isNumeric(text)) {
			readIntCallback(text);
		} else {
			printError(text + " is not an int.");
			readIntWrapper(readIntPrompt, readIntCallback);
		}
	}

	this.readLine = function(prompt, callback) {
		readLineWrapper(prompt, callback);
	};

	function readLineWrapper(prompt, callback) {
		println(prompt, "prompt");
		readValueCallback = callback;
		_in = document.createElement('input');
		_in.setAttribute('class', 'consoleInput');
		_out.appendChild(_in);
		_console.scrollTop = _console.scrollHeight;
		_in.setAttribute('onKeyDown', 'console.inputKeyDown(event);');
		_in.focus();
	}

	this.init = function() {
		_out = document.getElementById("consoleOutput");
		_console = document.getElementById("console");
		_console.onclick = mouseDown;
		_win = window;
		this.clear();
	};

	function mouseDown() {
		if(_in) {
			_in.focus();
		}
	}

	function isNumeric(text) {
		if (text.length == 0) return false;
		if (text[0] == '-') return isNumeric(text.substring(1));
		var validChars = "0123456789";
		for (i = 0; i < text.length; i++) { 
			var ch = text.charAt(i); 
			if (validChars.indexOf(ch) == -1) {
				return false;
			}
		}
		return true;
	}

	function initTarget(){
		_win.Shell = window;
		_win.print = shellCommands.print;
	}

	function refocus() {
		_in.blur(); // Needed for Mozilla to scroll correctly.
		_in.focus();
	}

	// Unless the user is selected something, refocus the textbox.
	// (requested by caillon, brendan, asa)
	function keepFocusInTextbox(e) 
	{
		var g = e.srcElement ? e.srcElement : e.target; // IE vs. standard

		while (!g.tagName)
			g = g.parentNode;
		var t = g.tagName.toUpperCase();
		if (t=="A" || t=="INPUT")
			return;

		if (window.getSelection) {
			// Mozilla
			if (String(window.getSelection()))
				return;
		}
		else if (document.getSelection) {
			// Opera? Netscape 4?
			if (document.getSelection())
				return;
		}
		else {
			// IE
			if ( document.selection.createRange().text )
				return;
		}

		refocus();
	}

	this.inputKeyDown = function(e) {
		// Use onkeydown because IE doesn't support onkeypress for arrow keys

		//alert(e.keyCode + " ^ " + e.keycode);

		if (e.keyCode == 13) { // enter
			// execute the input on enter
			try { go(); } catch(er) { alert(er); };

		} 

		setTimeout(recalculateInputHeight, 0);

		//return true;
	};

	function caretInFirstLine(textbox)
	{
		// IE doesn't support selectionStart/selectionEnd
		if (textbox.selectionStart == undefined)
			return true;

		var firstLineBreak = textbox.value.indexOf("\n");

		return ((firstLineBreak == -1) || (textbox.selectionStart <= firstLineBreak));
	}

	function caretInLastLine(textbox)
	{
		// IE doesn't support selectionStart/selectionEnd
		if (textbox.selectionEnd == undefined)
			return true;

		var lastLineBreak = textbox.value.lastIndexOf("\n");

		return (textbox.selectionEnd > lastLineBreak);
	}

	function recalculateInputHeight()
	{
		var rows = _in.value.split(/\n/).length
		+ 1 // prevent scrollbar flickering in Mozilla
		+ (window.opera ? 1 : 0); // leave room for scrollbar in Opera

		if (_in.rows != rows) // without this check, it is impossible to select text in Opera 7.60 or Opera 8.0.
			_in.rows = rows;
	}

	function println(s, type) {
		if((s=String(s)))
		{
			var textNode = document.createTextNode(s);
			var newdiv = document.createElement("div");
			newdiv.appendChild(textNode);
			newdiv.className = type;
			//alert(textNode.textContent);
			//var width = (test.clientWidth + 1) + "px";


			_out.appendChild(newdiv);
			//alert(newdiv.clientWidth);
			_console.scrollTop = _console.scrollHeight;
			return newdiv;
		}
	}

	function printWithRunin(h, s, type)
	{
		var div = println(s, type);
		var head = document.createElement("strong");
		head.appendChild(document.createTextNode(h + ": "));
		div.insertBefore(head, div.firstChild);
	}


	var shellCommands = 
	{
			load : function(url)
			{
				var s = _win.document.createElement("script");
				s.type = "text/javascript";
				s.src = url;
				_win.document.getElementsByTagName("head")[0].appendChild(s);
				println("Loading " + url + "...", "message");
			},

			clear : function()
			{
				var CHILDREN_TO_PRESERVE = 3;
				while (_out.childNodes[CHILDREN_TO_PRESERVE]) 
					_out.removeChild(_out.childNodes[CHILDREN_TO_PRESERVE]);
			},

			print : function(s) { println(s, "print"); },

			// the normal function, "print", shouldn't return a value
			// (suggested by brendan; later noticed it was a problem when showing others)
			pr : function(s) 
			{ 
				shellCommands.print(s); // need to specify shellCommands so it doesn't try window.print()!
				return s;
			},

			ans : undefined
	};

	function printQuestion(q)
	{
		println(q, "userInput");
	}

	function printError(er) { 
		println("Error: " + er, "error"); // Because security errors in Moz /only/ have toString.
	}

	function go(s)
	{
		_in.value = question = s ? s : _in.value;

		//if (question == "")
		//return;

		// Unfortunately, this has to happen *before* the JavaScript is run, so that 
		// print() output will go in the right place.
		_in.value='';
		recalculateInputHeight();
		printQuestion(question);

		if (_win.closed) {
			printError("Target window has been closed.");
			return;
		}

		if (readValueCallback) {
			_out.removeChild(_in);
			var callback = readValueCallback;
			readValueCallback = null;
			callback(question);

		}
	}
}


