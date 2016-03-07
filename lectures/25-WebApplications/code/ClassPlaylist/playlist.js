window.onload = init;

function init() {
}

/**
 * Function: Server Request
 * ------------------------
 * Uses the JQuery get method to make a server request
 * to the given uri with the provided data
 */
function serverRequest(uri, data, callback) {
	$.get(uri, data, callback);
}