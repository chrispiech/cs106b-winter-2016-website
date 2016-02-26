
#include <cctype>
#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include "console.h"
#include "filelib.h"
#include "grid.h"
#include "gwindow.h"
#include "simpio.h"
#include "pqueue.h"
#include "basicgraph.h"

using namespace std;

void loadEgoNetwork(BasicGraph & graph) {
    cout << "Loading facebook connections " << endl;
    ifstream fileStream;
    openFile(fileStream, "348.edges");
    string line;
    // one line at a time
    while(getline(fileStream, line)) {
        Vector<string> parts = stringSplit(line, " ");
        string a = parts[0];
        string b = parts[1];

        if(!graph.containsNode(a)) {
            graph.addNode(a);
        }
        if(!graph.containsNode(b)){
            graph.addNode(b);
        }

        graph.addEdge(a, b);
        graph.addEdge(b, a);
    }
    cout << "Graph built" << endl;
}

int getDispersion(BasicGraph & egoGraph, Vertex * amigo) {
    // 1. find the set of mutal friends
    Set<Vertex *> mutualFriends = egoGraph.getNeighbors(amigo);

    // 2. count number of pairs of mutual friends.... that don't
    // know each other
    int count = 0;
    for(Vertex * a : mutualFriends) {
        for(Vertex * b : mutualFriends) {
            if(a == b) continue;
            if(!egoGraph.containsEdge(a, b)) {
                count++;
            }
        }
    }
    return count;
}

int main() {
    setConsoleFont("courier-24");
    BasicGraph egoGraph;
    loadEgoNetwork(egoGraph);

    cout << "Num nodes: " << egoGraph.getNodeSet().size() << endl;
    cout << "Num edges: " << egoGraph.getEdgeSet().size() << endl;

    PriorityQueue<string> dispersest;
    for(Vertex * v : egoGraph) {
        int score = getDispersion(egoGraph, v);
        dispersest.enqueue(v->name, -score);
    }
    for(int i = 0; i < 10; i++) {
        int dispersion = -dispersest.peekPriority();
        string id = dispersest.dequeue();
        cout << id << "\t" << dispersion << endl;
    }
    cout << "Thanks" << endl;
    return 0;
}
