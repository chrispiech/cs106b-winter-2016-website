window.onload = init;

function init() {
	console.log("page loaded...")
	serverRequest("http://localhost:8888/getSongs", {}, populateSongs);
}

function populateSongs(response) {
	console.log(response)
	var data = eval(response);
	var songListDiv = document.getElementById("songList")
	songListDiv.innerHTML = "";
	for(var i = 0; i < data.length; i++) {
		var songDiv = document.createElement('div');
		songDiv.setAttribute("class", "well");

		var songName = data[i]["songName"];
		var artist = data[i]["artist"]
		var html = artist + " - " + songName; 
		songDiv.innerHTML = html;
		
		songListDiv.appendChild(songDiv);
	}
}

function addSong() {
	var artist = document.getElementById('artistInput').value
	var songName = document.getElementById('songNameInput').value
	var songData = {};
	songData["artist"] = artist;
	songData["songName"] = songName;
	serverRequest("http://localhost:8888/addSong", songData, init);
}

function serverRequest(uri, data, callback) {
	$.get(uri, data, callback);
}