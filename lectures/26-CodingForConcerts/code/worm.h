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

class WormEffect : public Effect {
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
    int getRandomGoal();
    void decayParticles();

private:
    LightGraph * graph;
    Searcher * searcher;

    int currNode;
    vector<int> path;

    map<int, int> particles;
};









