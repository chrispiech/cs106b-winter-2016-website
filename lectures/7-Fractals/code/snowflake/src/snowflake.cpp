

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

// useful math constants
static const double COS_60 = 0.5;            //value of cos(60 degrees)
static const double SIN_60 = sqrt(3)*0.5;    //value of sin(60 degrees)

// display constants
static const int SCREEN_WIDTH = 500;
static const int SCREEN_HEIGHT = SCREEN_WIDTH;
static const int BASE_Y = 330;
static const int BASE_LEFT_X = 100;
static const int BASE_RIGHT_Y = 400;

GPoint interpolate(GPoint p1, GPoint p2, double fraction) {
    double deltaX = p2.getX() - p1.getX();
    double deltaY = p2.getY() - p1.getY();
    double x = p1.getX() + fraction * deltaX;
    double y = p1.getY() + fraction * deltaY;
    GPoint newPoint(x, y);
    return newPoint;
}

GPoint equilatoralTip(GPoint p1, GPoint p2) {
    double deltaX = (p2.getX() - p1.getX());
    double deltaY = (p2.getY() - p1.getY());
    double x = p1.getX() + (deltaX*COS_60 + deltaY*SIN_60);
    double y = p1.getY() + (deltaY*COS_60 - deltaX*SIN_60);
    GPoint tip(x, y);
    return tip;
}

void drawFlakeLine(GWindow & window, int level, GPoint start, GPoint end) {

}



/**
 *         Top
 *          X
 *         / \
 *        /   \
 *       /     \
 *      X-------X
 *BottomLeft   BottomRight
 */
int main() {
    int depth = 4;

    GWindow w(SCREEN_WIDTH, SCREEN_HEIGHT);
    GPoint bottomLeft(BASE_LEFT_X, BASE_Y);
    GPoint bottomRight(BASE_RIGHT_Y, BASE_Y);
    GPoint top = equilatoralTip(bottomLeft, bottomRight);
    drawFlakeLine(w, depth, bottomLeft, top);
    drawFlakeLine(w, depth, top, bottomRight);
    drawFlakeLine(w, depth, bottomRight, bottomLeft);
    return 0;
}



/**
    if(level <= 0) {
        window.drawLine(start, end);
    } else {
        //window.drawLine(start, end);
        GPoint p1 = interpolate(start, end, 1.0 / 3.0);
        GPoint p2 = interpolate(start, end, 2.0 / 3.0);
        GPoint tip = equilatoralTip(p1, p2);

        drawFlakeLine(window, level - 1, start, p1);
        drawFlakeLine(window, level - 1, p1, tip);
        drawFlakeLine(window, level - 1, tip, p2);
        drawFlakeLine(window, level - 1, p2, end);

    }
 **/

