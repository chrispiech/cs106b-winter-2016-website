function BinaryExplodeApp() {

	this.init = function () {
		console.println("Warmup Problem 0a Binary Encoding:");
		console.println("The program prints all bit patterns that can be represented using a given number of bits.");
		console.readInt("Number of bits: ", generateBinaryCode);
	};
	
	function generateBinaryCode(nBits) {
		if (nBits < 0) {
			console.println("No binary codes for negative digits...");
		} else {
			generateBinaryCodeRecursive(nBits, '');
		}
		console.println('');
		console.readInt("Number of bits: ", generateBinaryCode);
	}
	
	function generateBinaryCodeRecursive(nBits, soFar) {
		if(nBits == 0) {
			if (soFar != '') console.println(soFar);
		} else {
			generateBinaryCodeRecursive(nBits - 1, soFar + '0');
			generateBinaryCodeRecursive(nBits - 1, soFar + '1');
		}
	}	
}
