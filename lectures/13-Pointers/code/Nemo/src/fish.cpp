#include "fish.h"
#include <iostream>
#include <math.h>
#include "gwindow.h"
#include "gobjects.h"
using namespace std;

const double GOAL_WIDTH = 200;
const double GOAL_HEIGHT = 120;

Fish::Fish(string filename, GWindow * window) {
    image = new GImage(filename);
    double scaleW = GOAL_WIDTH / image->getWidth();
    double scaleH = GOAL_HEIGHT / image->getHeight();
    double scale = min(scaleW, scaleH);
    image->scale(scale);
    int maxX = window->getWidth() - image->getWidth();
    int maxY = window->getHeight() - image->getHeight();
    x = randomInteger(0, maxX);
    y = randomInteger(0, maxY);
    window->add(image, x, y);
    tank = window;
    choseNewDirection();
}

void Fish::swim() {
    double oldX = x;
    double oldY = y;
    x += dx;
    y += dy;
    bool collision = false;
    if(x < 0 || x > tank->getWidth() - image->getWidth()) {
        collision = true;
    }
    if(y < 0 || y > tank->getHeight() - image->getHeight()) {
        collision = true;
    }
    if(collision) {
        x = oldX;
        y = oldY;
        choseNewDirection();
    }

    image->setLocation(x, y);
}

void Fish::choseNewDirection() {
    dx = randomInteger(2, 4);
    dy = randomInteger(2, 4);
    if(randomBool()) dx *= -1;
    if(randomBool()) dy *= -1;
}

Fish::~Fish() {
    delete image;
}

