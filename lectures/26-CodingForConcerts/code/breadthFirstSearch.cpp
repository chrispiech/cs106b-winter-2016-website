// Simple example effect:
// Draws a noise pattern modulated by an expanding sine wave.

#include <math.h>
#include <map>
#include <queue>
#include <set>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include "lib/color.h"
#include "lib/effect.h"
#include "lib/effect_runner.h"
#include "lib/noise.h"
#include "lib/lightGraph.h"
#include "breadthFirstSearch.h"

using namespace std;

// Do more than one BFS step each frame
const int LOOPS_PER_TIMESTEP = 5;

/**
 * Method: On Start
 * ----------------
 * Called once. Passes in all pixel information
 */
void BFSEffect::onStart(const vector<PixelInfo> & pixelInfoVec) {
    // construct a graph out of all the pixels.
    graph = new LightGraph(pixelInfoVec);

    // try to reach the very last light
    vector<int> nodes = graph->getAllNodes();
    endNode = pixelInfoVec.size() - 800;

    // make that initial path for BFS
    vector<int> startPath;

    // start at node 0 (initial path is just [0])
    startPath.push_back(0);
    bfsQueue.push(startPath);

    // keep track of how many BFS steps we have taken.
    timeStep = 0;
    cout << "starting.." << endl;
}

/**
 * Method: Begin Frame
 * ----------------
 * Called once each heartbeat. Do your algorithm work here.
 */
void BFSEffect::beginFrame(const FrameInfo &f) {
    // Take many BFS steps in each frame for speed reasons.
    for(int i = 0; i < LOOPS_PER_TIMESTEP; i++) {
        bfsStep();
    }
}

/**
 * Method: Shader
 * ----------------
 * Called once each heartbeat on *each* pixel. Set the
 * rbg value (passed by reference) to modify the pixel.
 */
void BFSEffect::shader(Vec3 & rgb, const PixelInfo &p) const {
    // If the pixel has been visited, color it.
    if(timeMap.find(p.index) != timeMap.end()) {
        // get the timestep it was visited
        double age = timeMap.at(p.index);

        // calculate a color based on the timeStep
        double hue = age / graph->getAllNodes().size() / 2.0;

        // color the pixel.
        hsv2rgb(rgb, hue, 0.6, 1.0);
    }

    // If we have found a bestPath and the pixel is on it..
    if(bestPath.find(p.index) != bestPath.end()) {
        rgb[0] = 1; // white
        rgb[1] = 1;
        rgb[2] = 1;
    }
}

/**
 * Method: BFS Step
 * ----------------
 * Processes one step of the Breadth First Search algorithm.
 * Dequeues a path and if it isn't the goal, make a new path
 * for each neighbor and enqueue it.
 */
void BFSEffect::bfsStep() {
    // If you found the solution, stop
    if(!bestPath.empty()) return;

    while(!bfsQueue.empty()) {
        // get the next path and its last node
        vector<int> currPath = bfsQueue.front();
        bfsQueue.pop();
        int currNode = currPath[currPath.size() - 1];

        // check and update the seen set
        if(seen.find(currNode) != seen.end()) continue;
        timeMap[currNode] = timeStep; // keep track of time
        if(currNode == endNode) {
            // you found a path! Update the best path 
            for(int node : currPath) {
                bestPath.insert(node);
            }
            // and go home!
            return;
        }
        seen.insert(currNode);

        // add all neighbors
        for(LightEdge * edge : graph->getEdges(currNode)) {
            int neighbor = edge->nodeB;
            vector<int> newPath = currPath;
            newPath.push_back(neighbor);
            bfsQueue.push(newPath);
        }

        // only do a single step each frame!
        break;
    }
    timeStep++;
}

/**
 * Function: main
 * ----------------
 * Start a "runner" which broadcasts pixel information. Attach
 * our effect!
 */
int main(int argc, char **argv) {
    EffectRunner runner;

    BFSEffect effect;
    runner.setEffect(&effect);

    // Defaults, overridable with command line options
    runner.setMaxFrameRate(50);
    runner.setLayout("../layouts/openpixelcontrol-layout.json");

    effect.onStart(runner.getPixelInfo());
    return runner.main(argc, argv);
}