

#include <fstream>
#include <iostream>
#include <iomanip>
#include <math.h>
#include "console.h"
#include "timer.h"
#include "hashset.h"
#include "lexicon.h"
#include "queue.h"
#include "set.h"
#include "vector.h"
#include "grid.h"
#include "filelib.h"
#include "gwindow.h"
#include "gobjects.h"
#include "simpio.h"
#include "point.h"

using namespace std;

// display constants
static const int SCREEN_WIDTH = 500;
static const int SCREEN_HEIGHT = 150;
static const int LEVEL_HEIGHT = 20;
static const int RECT_HEIGHT = 10;
static const int INSET = 20;

GPoint interpolate(GPoint p1, GPoint p2, double fraction) {
    double deltaX = p2.getX() - p1.getX();
    double deltaY = p2.getY() - p1.getY();
    double x = p1.getX() + fraction * deltaX;
    double y = p1.getY() + fraction * deltaY;
    GPoint newPoint(x, y);
    return newPoint;
}

void drawRectangle(GWindow & w, GPoint left, GPoint right) {
    double width = right.getX() - left.getX();
    GRect * rect = new GRect(width, RECT_HEIGHT);
    rect->setFilled(true);
    w.add(rect, left.getX(), left.getY() - RECT_HEIGHT/2);
}

GPoint lower(GPoint point) {
    GPoint next(point.getX(), point.getY() + LEVEL_HEIGHT);
    return next;
}


void drawCantor(GWindow & w, int level, GPoint left, GPoint right) {
    if(level > 0) {
        drawRectangle(w, left, right);

        GPoint a = interpolate(left, right, 0.33);
        GPoint b = interpolate(left, right, 0.67);

        drawCantor(w, level - 1, lower(left), lower(a));
        drawCantor(w, level - 1, lower(b), lower(right));

    }
}


int main() {
    int depth = 6;

    GWindow w(SCREEN_WIDTH, SCREEN_HEIGHT);
    GPoint left(INSET, INSET);
    GPoint right(SCREEN_WIDTH - INSET, INSET);
    drawCantor(w, depth, left, right);
    return 0;
}

