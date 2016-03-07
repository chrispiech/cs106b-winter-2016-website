window.onload = init();


function init() {
	console.log("page loaded...")
	$.get("http://localhost:8888/getSongs", populateSongs);
}

function populateSongs(response) {
	console.log(response)
	var data = eval(response);
	var songListDiv = document.getElementById("songList")
	songListDiv.innerHTML = "";
	for(var i = 0; i < data.length; i++) {
		var songDiv = document.createElement('div');
		songDiv.setAttribute("class", "well");

		var left = document.createElement("div");
		left.setAttribute("class", "media-left");
		songDiv.appendChild(left);

		var img = document.createElement("img");
		img.setAttribute("class", "media-object")
		left.appendChild(img);

		var right = document.createElement("div");
		right.setAttribute("class", "media-body");
		songDiv.appendChild(right);

		var title = document.createElement("h4");
		title.setAttribute("class", "media-heading");
		right.appendChild(title);

		var songName = data[i]["songName"];
		var artist = data[i]["artist"]
		var html = artist + " - " + songName; 
		title.innerHTML = html;
		
		songListDiv.appendChild(songDiv);
		spotifySearch(artist, songName, img);
	}
}

function addSong() {
	console.log("add song button")
	var artist = $('#artistInput').val()
	var songName = $('#songNameInput').val()

	var addData = {};
	addData["artist"] = artist;
	addData["songName"] = songName;
	$.get("http://localhost:8888/addSong", addData, finishedAdding);
}

function finishedAdding() {
	console.log("finished adding");
	init();
}

// EG: https://api.spotify.com/v1/search?q=artist:kygo&type=track
function spotifySearch(artist, track, img) {
	var queryString = ""
	var uri = ""
	uri += "https://api.spotify.com/v1/search?q="
	uri += "artist:" + encodeURI(artist);
	uri += "+AND+";
	uri += "track:" + encodeURI(track);
	uri += "&type=track";
	
	$.get(uri, function(response) {
		var searchData = eval(response)
		var song = searchData["tracks"]["items"][0];
		var albumImgUrl = song["album"]["images"][0]["url"];
		console.log(albumImgUrl)
		img.src = albumImgUrl
		img.setAttribute("style", "width:40px;height:40px")
	})
}