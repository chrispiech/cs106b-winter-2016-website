function BalanceParensApp() {
	var PAREN_CHARS = "[](){}";

	this.init = function () {
		console.println("Balanced Paren Program");
		console.println("Checks if a string has balanced parentheses.");
		start();
	};

	function start() {
		console.readLine("Enter a string: ", balanceParensWrapper);
	}

	function balanceParensWrapper(text) {
		parenString = getParenString(text);
		console.println(balanceParens(parenString) ? "Balanced!" : "Not Balanced!");
		start();
	}

	function balanceParens(string) {
		if (string == '') return true;
		reduced = string.replace('[]', '');
		reduced = reduced.replace('{}', '');
		reduced = reduced.replace('()', '');
		if (reduced == string) return false;
		return balanceParens(reduced);
	}

	function getParenString(text) {
		var parenString = '';
		for (var i = 0; i < text.length; i++) {
			if (isParenChar(text[i])) {
				parenString += text[i];
			}
		}
		return parenString;
	}

	function isParenChar(ch) {
		return PAREN_CHARS.indexOf(ch) != -1;
	};
}