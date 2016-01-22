

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
static const int SCREEN_WIDTH = 600;
static const int SCREEN_HEIGHT = SCREEN_WIDTH;



void drawCenteredCircle(GWindow & w, GPoint center, double radius) {
    w.drawOval(center.getX() - radius, center.getY() - radius, 2 * radius, 2 * radius);
}

GPoint addPolar(GPoint start, double length, double angleDegrees) {
    double radiansPerDegree = 2. * M_PI / 360;
    double radians = angleDegrees * radiansPerDegree;
    double dx = length * cos(radians);
    double dy = length * sin(radians);
    GPoint next(start.getX() + dx, start.getY() - dy);
    return next;
}

void drawRecursiveCircle(GWindow & w, int depth, GPoint center, double radius) {
    if(depth > 0) {
        drawCenteredCircle(w, center, radius);
        drawRecursiveCircle(w, depth - 1, center, radius / 3);
        double length = 2.0 / 3 * radius;
        for(int i = 0; i < 6; i++) {
            double angle = 60 * i;
            GPoint right = addPolar(center, length, angle);
            drawRecursiveCircle(w, depth - 1, right, radius / 3);
        }
        /*for(int i = 0; i < 6; i++) {
            double angleDegrees = (i / 6.0) * 360;
            double length = 2.0 / 3 * radius;
            GPoint newCenter = addPolar(center, length, angleDegrees);
            drawRecursiveCircle(w, depth - 1, newCenter, radius / 3);
        }*/
    }
}

int main() {
    int depth = 7;

    GWindow w(SCREEN_WIDTH, SCREEN_HEIGHT);
    GPoint center(SCREEN_WIDTH/2, SCREEN_HEIGHT/2);
    drawRecursiveCircle(w, depth, center, SCREEN_WIDTH/2);
    return 0;
}

