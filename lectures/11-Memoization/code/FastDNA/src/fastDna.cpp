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
#include "filelib.h"
#include "grid.h"
#include "strlib.h"
#include "graph.h"
using namespace std;

string tail(string str) {
    return str.substr(1, str.length() - 1);
}

int fastAlign(Map<string, int>& cache, string s1, string s2) {
    // key = combo of s1 and s2
    string key = s1 + ":" + s2;

    // base case
    if(cache.containsKey(key)) return cache[key];
    if(s1.empty()) return s2.length();
    if(s2.empty()) return s1.length();

    // try every branch in the decision tree...
    // branch1: match first letter
    int matchScore = s1[0] == s2[0] ? 0 : 1;
    int matchOption = matchScore + fastAlign(cache, tail(s1), tail(s2));

    // branch2: gap at start of second string
    int gapStr2 = 1 + fastAlign(cache, tail(s1), s2);

    // branch3: gap at start of first string
    int gapStr1 = 1 + fastAlign(cache, s1, tail(s2));

    // which branch was best?
    int score = min(matchOption, min(gapStr2, gapStr1));
    cache[key] = score;
    return score;
}

int align(string s1, string s2) {
    Map<string, int> cache;
    return fastAlign(cache, s1, s2);
}

/* Main program */
int main() {
    string s1 = readEntireFile("cancer1.txt");
    string s2 = readEntireFile("cancer2.txt");
    cout << s1 << endl;
    cout << s2 << endl;
    cout << "starting..." << endl;
    Timer timer;
    timer.start();
    int similarity = align(s1, s2);
    cout << "done!\t" << timer.stop() << endl;
    cout << similarity << endl;
    return 0;
}
