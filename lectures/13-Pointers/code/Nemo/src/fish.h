#ifndef FISH
#define FISH
#include <iostream>
#include "gwindow.h"
#include "gobjects.h"
using namespace std;

class Fish {
public:
    // make a new fish
    Fish(string fileName, GWindow * window);
    ~Fish();

    // animate one frame of swimming
    void swim();

private:
    // sometimes you have to rethink it.
    void choseNewDirection();

private:
    // where is this fish now?
    double x;
    double y;

    // where is this fish going?
    double dx;
    double dy;

    // all fish point to the same GWindow
    GWindow * tank;

    // GImages are always stored on the heap
    GImage * image;
};

#endif // FISH
