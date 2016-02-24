function AStarSearchNode(artistName, previousNode, cost, heuristic, match) {
	artistName = artistName.toLowerCase();

	this.getArtist = function() {
		return artistName;
	};

	this.getPreviousNode = function() {
		return previousNode;
	};

	this.getCost = function() {
		return cost + heuristic;
	};

	this.getKey = function() {
		return artistName;
	};
	
	this.getMatch = function() {
		return match;
	};
}

function SongPathApp() {
	var LIMIT = 100;

	
	var startSongArtist = 'smash mouth';
	var endSongArtist = 'ke$ha';
	var lastfm;
	var fringe;
	var visited;

	this.init = function() {
		lastfm = new LastFM({
			apiKey : '08b6a3cf6967e3bc0bea3efebc076af0',
			apiSecret : 'c8496a6c830f277bc781e82abdf59148'
		});
		console.println("Artist Graph Path");
		console.println("This program aims to find the shortest path " +
				"between two artists. Due to the large number of artists " +
				"and the lack of a heuristic function this algorithm only " +
				"works to a shallow depth.");	
		

		console.readLine("Enter the start artist: ", startEntered);
	};
	
	function startEntered(artist) {
		startSongArtist = artist.toLowerCase();
		console.readLine("Enter the end artist: ", endEntered);
	}
	
	function endEntered(artist) {
		endSongArtist = artist.toLowerCase();
		findPath();
	}

	function findPath() {
		fringe = PriorityQueue({
			low : true
		});
		var startNode = new AStarSearchNode(startSongArtist, null, 0, 0, 0);
		fringe.push(startNode, startNode.getCost());
		visited = {};
		searchNode();
	}
	
	function searchNode() {
		var node = fringe.pop();
		if (isGoalState(node)) {
			return getPathToNode(node);
		} else if (!(node.getKey() in visited)) {
			console.println(node.getKey());
			visited[node.getKey()] = node;
			expand(node);
		} else if (!fringe.empty()) {
			searchNode();
		} else {
			console.println("NO PATH!");
		}
	}

	function isGoalState(node) {
		return node.getArtist() == endSongArtist;
	}
	
	function getPathToNode(node){
		if (node == null) console.printError("no path");
		console.println("PATH FOUND!");
		console.println("");
		var path = node.getArtist();
		var currentNode = node;
		while (true) {
			var match = currentNode.getMatch();
			currentNode = currentNode.getPreviousNode();
			if (currentNode == null) break;
			path = currentNode.getArtist() + ' ('+match+') ' + path;
		}
		console.println(path);
	}

	function expand(parent) {
		lastfm.artist.getSimilar({ 
			artist : parent.getArtist(),
			limit : LIMIT}, {
				success : function(data) {
					var similarArtists = data['similarartists']['artist'];
					for (artistIndex in similarArtists) {
						var artist = similarArtists[artistIndex];
						if (artist.match > 0) {
							var arcCost = 1 - artist.match;
							var child = new AStarSearchNode(artist.name,
									parent, parent.getCost() + arcCost, 
									getHeuristic(artist.name), artist.match);
							fringe.push(child, child.getCost());
							//console.println(parent.getKey() + '->' + child.getKey());
						}
					}
					if (!fringe.empty()) searchNode();
					else console.println("NO PATH!");
				},
				error : function(code, message) {
					alert('Error: ' + message);
				}
			});
	}
	
	function getHeuristic(artist) {
		return 0;
	}
}
