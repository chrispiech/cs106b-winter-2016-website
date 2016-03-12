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
#include "lib/search.h"
#include "worms.h"

using namespace std;

const int PARTICLE_TTL = 40;
const int N_WORMS = 15;

void WormsEffect::onStart(const vector<PixelInfo> & pixelInfoVec){
    graph = new LightGraph(pixelInfoVec);
    searcher = new Searcher(graph);

    for(int i = 0; i < N_WORMS; i++) {
        int startNode = getRandomNode();
        int endNode = getRandomNode();
        vector<int> nextPath = searcher->shortestPath(startNode, endNode);
        wormPaths.push_back(nextPath);
    }
}

void WormsEffect::beginFrame(const FrameInfo &f) {
    // update all particles
    map<int, int> newParticles;
    for(auto& keyValue : particles) {
        int node = keyValue.first;
        int newAge = keyValue.second - 1;
        if(newAge > 0) {
            newParticles[node] = newAge;
        }
    }
    particles = newParticles;

    // take a step on the path
    for(int i = 0; i < N_WORMS; i++) {
        int currNode = wormPaths[i].front();
        while(wormPaths[i].size() <= 1) {
            int goal = getRandomNode();
            wormPaths[i] = searcher->shortestPath(currNode, goal);
        }
        wormPaths[i].erase(wormPaths[i].begin());
        particles[currNode] = PARTICLE_TTL;
    }
}

int WormsEffect::getRandomNode() {
    return rand() % graph->getAllNodes().size() - 1;
}


void WormsEffect::shader(Vec3 & rgb, const PixelInfo &p) const {
    hsv2rgb(rgb, 0, 0, 0);
    if(particles.find(p.index) != particles.end()) {
        double timeToLive = particles.at(p.index);
        double value = sqrt(timeToLive / PARTICLE_TTL);
        hsv2rgb(rgb, 0.5, 0.5, value);
    }
}

int main(int argc, char **argv) {
    EffectRunner runner;

    WormsEffect effect;
    runner.setEffect(&effect);

    // Defaults, overridable with command line options
    runner.setMaxFrameRate(100);
    runner.setLayout("../layouts/openpixelcontrol-layout.json");

    effect.onStart(runner.getPixelInfo());
    return runner.main(argc, argv);
}