// Simple example effect:
// Draws a noise pattern modulated by an expanding sine wave.

#include "lib/color.h"
#include "lib/effect.h"
#include "lib/effect_runner.h"
#include "lib/noise.h"
#include "aStar.h"

void AStarEffect::onStart(const vector<PixelInfo> & pixelInfoVec) {
	this->pixelInfoVec = pixelInfoVec;
	graph = new LightGraph(pixelInfoVec);
    startNode = 200;
    endNode = 2000;
    vector<int> startPath;
    startPath.push_back(startNode);
    pair<vector<int>, double> startPair;
    startPair.first = startPath;
    startPair.second = 0;
    aStarQueue.push(startPair);
    timeStep = 0;
    cout << "starting.." << endl;
}

void AStarEffect::beginFrame(const FrameInfo &f)  {
    for(int i = 0; i < LOOPS_PER_TIMESTEP; i++) {
        aStarStep();
    }
}

double AStarEffect::getPriority(vector<int> v) {
    int lastNode = v[v.size() - 1];
    return v.size() + heuristic(lastNode);
}

double AStarEffect::heuristic(int node) {
    Vec3 pointA = pixelInfoVec[node].point;
    Vec3 pointB = pixelInfoVec[endNode].point;
    double distance = len(pointA - pointB);
    double heuristic = distance / MAX_EDGE_DIST;
    cout << heuristic << endl;
    return heuristic;
}

void AStarEffect::aStarStep() {
    if(!bestPath.empty()) return;
    while(!aStarQueue.empty()) {
        // get the next path and node
        pair<vector<int>, double> currPair = aStarQueue.top();
        vector<int> currPath = currPair.first;
        aStarQueue.pop();
        int currNode = currPath[currPath.size() - 1];

        // check and update the seen set
        if(seen.find(currNode) != seen.end()) continue;
        timeMap[currNode] = (double(timeStep) / graph->getAllNodes().size()) / 2.0;
        if(currNode == endNode) {
            for(int node : currPath) {
                bestPath.insert(node);
            }
            return;
        }
        seen.insert(currNode);

        // add all neighbors
        for(LightEdge * edge : graph->getEdges(currNode)) {
            int neighbor = edge->nodeB;
            vector<int> newPath = currPath;
            newPath.push_back(neighbor);

            pair<vector<int>, double> newPair;
            newPair.first = newPath;
            newPair.second = getPriority(newPath);
            aStarQueue.push(newPair);
        }
        break;
    }
    timeStep++;
}

void AStarEffect::shader(Vec3 & rgb, const PixelInfo &p) const {
    if(timeMap.find(p.index) != timeMap.end()) {
        double age = timeMap.at(p.index);
        hsv2rgb(rgb, age, 0.5, 1.0);
    }
    if(bestPath.find(p.index) != bestPath.end()) {
        rgb[0] = 1;
        rgb[1] = 0;
        rgb[2] = 0;
    }
}

int main(int argc, char **argv) {
    EffectRunner runner;

    AStarEffect effect;
    runner.setEffect(&effect);

    // Defaults, overridable with command line options
    runner.setMaxFrameRate(100);
    runner.setLayout("../layouts/openpixelcontrol-layout.json");

    effect.onStart(runner.getPixelInfo());
    return runner.main(argc, argv);
}