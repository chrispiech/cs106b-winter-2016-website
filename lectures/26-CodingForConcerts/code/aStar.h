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

const int LOOPS_PER_TIMESTEP = 5;
const double MAX_EDGE_DIST = 0.015;

class AStarEffect : public Effect {
public:

    void onStart(const vector<PixelInfo> & pixelInfoVec);

    virtual void beginFrame(const FrameInfo &f);

    double getPriority(vector<int> v);

    double heuristic(int node);

    void aStarStep();

    virtual void shader(Vec3 & rgb, const PixelInfo &p) const;

private:
    struct PairCompare {
      bool operator()(pair<vector<int>, double> & lhs, pair<vector<int>, double> & rhs) const {
        return lhs.second > rhs.second;
      }
    };

    vector<PixelInfo> pixelInfoVec;
    priority_queue<pair<vector<int>, double>, vector<pair<vector<int>, double> >, PairCompare> aStarQueue;
    set<int> seen;
    LightGraph * graph;
    int startNode;
    int endNode;

    map<int, double> timeMap;
    int timeStep;
    set<int> bestPath;
};