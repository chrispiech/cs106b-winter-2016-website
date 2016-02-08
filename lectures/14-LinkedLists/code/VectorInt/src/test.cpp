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
#include <assert.h>
#include <cmath>
#include "console.h"
#include "error.h"
#include "simpio.h"
#include "map.h"
#include "timer.h"
#include "vecint.h"
#include "grid.h"
#include "strlib.h"
using namespace std;

int main() {
    VecInt v;
    for(int i = 0; i < 1000; i++) {
        cout << "add " << i << endl;
        v.add(i);
    }

    for(int i = 0; i < 500; i++) {
        int maxIndex = v.size() - 1;
        int index = randomInteger(0, maxIndex);
        assert(v.get(index) == index);
        cout << "passed " << index << endl;
    }

    return 0;
}
