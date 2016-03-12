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
#include "worm.h"

using namespace std;

const int PARTICLE_TTL = 50;

void WormEffect::onStart(const vector<PixelInfo> & pixelInfoVec){
    graph = new LightGraph(pixelInfoVec);
    searcher = new Searcher(graph);

    int currNode = 0;
    int endNode = getRandomGoal();
    path = searcher->shortestPath(currNode, endNode);
}

void WormEffect::beginFrame(const FrameInfo &f) {
    decayParticles();

    // take a step on the path
    while(path.empty()) {
        int goal = getRandomGoal();
        path = searcher->shortestPath(currNode, goal);
    }
    currNode = path.front();
    path.erase(path.begin());
    particles[currNode] = PARTICLE_TTL;
}

void WormEffect::shader(Vec3 & rgb, const PixelInfo &p) const {
    hsv2rgb(rgb, 0, 0, 0);
    if(particles.find(p.index) != particles.end()) {
        double timeToLive = particles.at(p.index);
        double value = sqrt(timeToLive / PARTICLE_TTL);
        hsv2rgb(rgb, 0.5, 0.5, value);
    }
}

int WormEffect::getRandomGoal() {
    return rand() % graph->getAllNodes().size() - 1;
}

void WormEffect::decayParticles() {
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
}

int main(int argc, char **argv) {
    EffectRunner runner;

    WormEffect effect;
    runner.setEffect(&effect);

    // Defaults, overridable with command line options
    runner.setMaxFrameRate(100);
    runner.setLayout("../layouts/openpixelcontrol-layout.json");

    effect.onStart(runner.getPixelInfo());
    return runner.main(argc, argv);
}