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
#include "gwindow.h"
#include "timer.h"
#include "grid.h"
#include "strlib.h"
using namespace std;

struct Tree {
    char value;
    Tree * left; // WAPH RECURSION
    Tree * right; // @#$@# ZOMG MORE!
};

int main() {

    Tree * root = new Tree;
    root->value = 'A';

    Tree * leftTree = new Tree;
    leftTree->value = 'B';
    root->left = leftTree;

    Tree * rightTree = new Tree;
    rightTree->value = 'C';
    root->right = rightTree;

    cout << root->left->value << endl;


    return 0;
}
