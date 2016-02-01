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
#include "graph.h"
using namespace std;

/* Calculate Diff
 * ------------
 * Just your run of the mill L1-Norm.
 */
double calculateDiff(double a, double b) {
    return fabs(a - b);
}

/* Compare All
 * ------------
 * Compares every element in the vector to every other
 * element in the vector.
 */
Grid<double> compareAll(Vector<double>& data) {
    Grid<double> similarity(data.size(), data.size());
    for(int i = 0; i < data.size(); i++) {
        for(int j = 0; j < i; j++) {
            double diff = calculateDiff(data[i], data[j]);
            similarity[i][j] = diff;
            similarity[j][i] = diff;
        }
    }
    return similarity;
}

/* Test Compare
 * ------------
 * Creates a random vector of size n and then runs
 * compareAll. Returns how many milli seconds it took
 */
int testCompare(int n) {
    Timer timer;
    timer.start();
    Vector<double> data;
    for(int i = 0; i < n; i++) {
        data.add(randomReal(0, 1));
    }
    compareAll(data);
    return timer.stop();
}

// Lovin' these constants!
const int MAX_N = 4000;
const int MAX_MS = 5000;
const int DELTA_N = 500;

/* Main
 * -----
 * Runs a time test on compare all and graphs results
 */
int main() {
    Graph graph("BigO", MAX_N, MAX_MS);

    for(int n = 0; n <= MAX_N; n += DELTA_N) {
        int time = testCompare(n);
        graph.addPoint(n, time);
        cout << n << "\t" << time << endl;
    }

    return 0;
}
