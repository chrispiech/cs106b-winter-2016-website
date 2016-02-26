
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

void loadTwitter(BasicGraph & graph) {
    cout << "Loading twitter connections " << endl;
    ifstream fileStream;
    openFile(fileStream, "twitter_small.txt");
    string line;
    // read the entire file line by line
    while(getline(fileStream, line)) {
        Vector<string> parts = stringSplit(line, " ");
        string a = parts[0];
        string b = parts[1];

        if(!graph.containsNode(a)) {
            graph.addNode(a);
        }
        if(!graph.containsNode(b)) {
            graph.addNode(b);
        }

        graph.addEdge(b, a);

        // a is following b
    }
    cout << "Graph built" << endl;
}

int main() {
    setConsoleFont("courier-24");
    BasicGraph graph;
    loadTwitter(graph);
    cout << "Num nodes: " << graph.getNodeSet().size() << endl;
    cout << "Num edges: " << graph.getEdgeSet().size() << endl;

    PriorityQueue<string> coolness;

    // get each node in the graph one at a time.
    for(Vertex * node : graph) {
        Set<Vertex *> neighborsOfNeighbors;

        Set<Vertex * > neighbors = graph.getNeighbors(node);
        neighborsOfNeighbors += neighbors;

        for(Vertex * neighbor : neighbors) {
            neighborsOfNeighbors += graph.getNeighbors(neighbor);
        }

        int num = neighborsOfNeighbors.size();
        coolness.add(node->name, -num);
    }

    while(!coolness.isEmpty()) {
        int num = -coolness.peekPriority();
        string name = coolness.dequeue();
        cout << name << "\t" << num << endl;
    }

    return 0;
}
