function WorldMusicApp() {

	var countriesTopSongs = {};
	var countryList = [];
	var countryIndex = 0;
	var halted = false;
	
	this.init = function() {
		lastfm = new LastFM({
			apiKey : '08b6a3cf6967e3bc0bea3efebc076af0',
			apiSecret : 'c8496a6c830f277bc781e82abdf59148'
		});
		console.println("World Music Graph");
		console.println("This program aims to create a graph of the world " +
				"where countries are nodes and the edges denote similar music taste. " +
				"Similar music taste is calculated using the Jaccard Coefficient of " +
				"the sets of current chart topping artists (thank you last.fm).");	

		lastfm.geo.getMetros({}, {
			success : handleMetroData,
			error : function(code, message) {
				alert('Error: ' + message);
			}
		});
	};
	
	this.finish = function() {
		halted = true;
	};
	
	function handleMetroData(data) {
		var metros = data['metros']['metro'];
		var metroIndex = 0;
		for (metroIndex in metros) {
			var metro = metros[metroIndex];
			countriesTopSongs[metro.country] = [];
		}
		for (country in countriesTopSongs) {
			countryList.push(country);
		}
		countryIndex = 0;
		getCountrySongs();
	}
	
	function getCountrySongs() {
		if (halted) return;
		if (countryIndex >= countryList.length) {
			console.println("Done looking up charts!");
			console.println('');
			console.println('Jaccard similarity coefficients');
			scoreArcs();
		} else {
			var countryName = countryList[countryIndex];
			lastfm.geo.getTopArtists({country:countryName}, {
				success : handleTopTracks,
				error : function(code, message) {
					alert('Error: ' + message);
				}
			});
		}
	}
	
	function handleTopTracks(data) {
		if (halted) return;
		var countryName = countryList[countryIndex];
		console.println("Looking up "+countryName+"'s charts.");
		var artists = data['topartists']['artist'];
		for (index in artists) {
			var name = artists[index].name;
			countriesTopSongs[countryName].push(name);
		}
		countryIndex++;
		getCountrySongs();
	}
	
	function scoreArcs() {	
		queue = PriorityQueue();
		scoreMap = {};
		for (var i = 0; i < countryList.length; i++) {
			for (var j = i + 1; j < countryList.length; j++) {
				var countryA = countryList[i];
				var countryB = countryList[j];
				var tanimotoScore = getTanimotoScore(countriesTopSongs[countryA], 
						countriesTopSongs[countryB]);
				var score = Math.round(tanimotoScore * 100) / 100;
				var key = countryA + ', ' + countryB;
				queue.push(key, score);
				scoreMap[key] = score;
			}
		}
		while(!queue.empty()) {
			var key = queue.pop();
			console.println(key + ': ' + scoreMap[key]);
		}
		console.finished();
	}
	
	function getTanimotoScore(setA, setB) {
		var unionSize = getUnionSize(setA, setB);
		var intersectSize = setA.length + setB.length - unionSize;
		return unionSize / intersectSize;
	}
	
	function getUnionSize(setA, setB) {
		var size = 0;
		for (var i = 0; i < setA.length; i++) {
			for (var j = 0; j < setB.length; j++) {
				if (setA[i] == setB[j]) size++;
			}
		}
		return size / 2;
	}	




}
