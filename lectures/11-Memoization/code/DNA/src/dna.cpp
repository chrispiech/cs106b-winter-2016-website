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

int align(string s1, string s2) {
    // base cases
    if(s1.empty()) return s2.length();
    if(s2.empty()) return s1.length();

    // try every branch in the decision tree...
    // branch1: match first letter
    int matchScore = s1[0] == s2[0] ? 0 : 1;
    int matchOption = matchScore + align(tail(s1), tail(s2));

    // branch2: gap at start of second string
    int gapStr2 = 1 + align(tail(s1), s2);

    // branch3: gap at start of first string
    int gapStr1 = 1 + align(s1, tail(s2));

    // which branch was best?
    return min(matchOption, min(gapStr2, gapStr1));
}

/* Main program */
int main() {
    //string s1 = "GAATTC";
    //string s2 = "GATTA";
    string s1 = readEntireFile("cancer1.txt");
    string s2 = readEntireFile("cancer2.txt");
    cout << s1 << endl;
    cout << s2 << endl;
    cout << "starting..." << endl;
    int similarity = align(s1, s2);
    cout << "done!" << endl;
    cout << similarity << endl;
    return 0;
}
