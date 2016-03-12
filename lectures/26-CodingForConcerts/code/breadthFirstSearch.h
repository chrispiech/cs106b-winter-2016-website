#pragma once
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

using namespace std;

class BFSEffect : public Effect {
public:
    /**
     * Method: On Start
     * ----------------
     * Called once. Passes in all pixel information
     */
    void onStart(const vector<PixelInfo> & pixelInfoVec);

    /**
     * Method: Begin Frame
     * ----------------
     * Called once each heartbeat. Do your algorithm work here.
     */
    virtual void beginFrame(const FrameInfo &f);

    /**
     * Method: Shader
     * ----------------
     * Called once each heartbeat on *each* pixel. Set the
     * rbg value (passed by reference) to modify the pixel.
     */
    virtual void shader(Vec3 & rgb, const PixelInfo &p) const;

private:
    /**
     * Method: BFS Step
     * ----------------
     * Processes one step of the Breadth First Search algorithm.
     * Dequeues a path and if it isn't the goal, make a new path
     * for each neighbor and enqueue it.
     */
    void bfsStep();

private:

    // The Breadth First Search queue
    queue<vector<int> > bfsQueue;

    // Which nodes have been seen
    set<int> seen;

    // The graph we operate on
    LightGraph * graph;

    // The node that we hope to reach
    int endNode;

    // For display reasons, keep track of when we touched a node
    // what the currentTimeStep is and the best path (once its found)
    map<int, double> timeMap;
    int timeStep;
    set<int> bestPath;
};