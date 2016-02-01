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

const double GOLDEN_RATIO = (1 + sqrt(5)) / 2;

/* FIB3
 * -----
 * The mind blowing closed form version of
 * fibonacci!
 */
int fib3(int n) {
    n = n + 1;
    double a = pow(GOLDEN_RATIO, n);
    double b = pow(1 - GOLDEN_RATIO, n);
    return round((a - b) / sqrt(5));
}

/* FIB2
 * -----
 * The fase, memoized version of fibonacci
 */
int fibFast(Map<int, int>&cache, int n) {
    if(cache.containsKey(n)) return cache[n];
    if(n <= 1) return 1;

    int result = fibFast(cache, n - 1) + fibFast(cache, n - 2);
    cache[n] = result;
    return result;
}

int fib2(int n) {
    Map<int, int> cache;
    return fibFast(cache, n);
}


/* FIB1
 * -----
 * The slow, non-memoized version of fibonacci
 */
int fib1(int n) {
    if(n <= 1) {
        return n;
    } else {
        return fib1(n - 1) + fib1(n - 2);
    }
}

/* Main program
 * ------------
 * Runs different flavors of Fibonacci.
 */
int main() {
    int maxN = 45;  //100000
    int maxTime = 10000;  //500
    Graph g("BigO", maxN, maxTime);
    int delta = maxN < 100 ? 1 : maxN/10;

    cout << "n \ttime \tanswer" << endl;
    for(int n = 0; n <= maxN; n+=delta) {
        Timer timer;
        timer.start();
        int answer = fib2(n);
        int time = timer.stop();
        g.addPoint(n, time);
        cout << n << "\t" << time;
        if(n <= 45) cout << "\t" << answer;
        cout << endl;
    }

    return 0;
}
