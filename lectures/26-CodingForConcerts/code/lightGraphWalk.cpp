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
#include "lightGraphWalk.h"

using namespace std;

const int PARTICLE_TTL = 50;

/**
 * Method: On Start
 * ----------------
 * Called once. Passes in all pixel information
 * // searcher->
 */
void LightWalkerEffect::onStart(const vector<PixelInfo> & pixelInfoVec){
    // build a graph of all the lights
    graph = new LightGraph(pixelInfoVec);
    // make a "searcher" that can run a-star on the graph
    searcher = new Searcher(graph);

}

/**
 * Method: Begin Frame
 * ----------------
 * Called once each heartbeat. Do your algorithm work here.
 * // path.front() path.erase() path.begin()
 */
void LightWalkerEffect::beginFrame(const FrameInfo &f) {
    
}

/**
 * Method: Shader
 * ----------------
 * Called once each heartbeat on *each* pixel. Set the
 * rbg value (passed by reference) to modify the pixel.
 */
void LightWalkerEffect::shader(Vec3 & rgb, const PixelInfo &p) const {
    if(p.index == currNode) {
        hsv2rgb(rgb, 0.5, 0.5, 1.0);
    }
}

/**
 * Method: Get Random Goal
 * ----------------
 * Returns a random node from the graph
 */
int LightWalkerEffect::getRandomGoal() {
    return rand() % graph->getAllNodes().size() - 1;
}

/**
 * Function: main
 * ----------------
 * Start a "runner" which broadcasts pixel information. Attach
 * our effect!
 */
int main(int argc, char **argv) {
    EffectRunner runner;

    LightWalkerEffect effect;
    runner.setEffect(&effect);

    // Defaults, overridable with command line options
    runner.setMaxFrameRate(100);
    runner.setLayout("../layouts/openpixelcontrol-layout.json");

    effect.onStart(runner.getPixelInfo());
    return runner.main(argc, argv);
}