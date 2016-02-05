/*
 * File: Nim.cpp
 * -------------
 * This program simulates a simple variant of the game of Nim.  In this
 * version, the game starts with a pile of 13 coins on a table.  Players
 * then take turns removing 1, 2, or 3 coins from the pile.  The player
 * who takes the last coin loses.
 */

#include <iostream>
#include <string>
#include <cmath>
#include "console.h"
#include "error.h"
#include "simpio.h"
#include "map.h"
#include "timer.h"
#include "vector.h"
#include "grid.h"
#include "strlib.h"
#include "fish.h"
using namespace std;

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const int N_FISH = 10;
const int PAUSE_MS = 40;

void addBackground(GWindow * window) {
    GImage * bkg = new GImage("ocean.jpg");
    double wScale = window->getWidth() / bkg->getWidth();
    double hScale = window->getHeight() / bkg->getHeight();
    double scale = max(wScale, hScale);
    bkg->scale(scale);
    window->add(bkg);
}

string getRandomFishFile() {
    int index = randomInteger(0, 3);
    if(index == 0) return "nemo.png";
    if(index == 1) return "dory.png";
    if(index == 2) return "pearl.png";
    if(index == 3) return "tad.png";
    return "";
}

int main() {
    GWindow * window = new GWindow(WINDOW_WIDTH, WINDOW_HEIGHT);
    addBackground(window);

    Vector<Fish*> allFish;
    for(int i = 0; i < N_FISH; i++) {
        Fish * newFish = new Fish(getRandomFishFile(), window);
        allFish.add(newFish);
    }

    while(true) {
        Timer timer;
        timer.start();
        for(Fish *f : allFish) {
            f->swim();
        }
        pause(PAUSE_MS - timer.stop());
    }

    return 0;
}
