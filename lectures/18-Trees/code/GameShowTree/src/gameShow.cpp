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
    string value;
    Tree * left;
    Tree * right;
};

void introduction() {
    cout << "Welcome to the second episode of the CS106B ";
    cout << "Gameshow. Pick a door and maybe you will win ";
    cout << "a prize!"<< endl;
}

void suspense() {
    cout << "Building suspense..." << endl;
    for(int i = 0; i < 10; i++) {
        cout << "..." << endl;
        pause(1000);
    }
}

int getUserChoice() {
    while(true) {
        int choice = getInteger("Door? ");
        if(choice >= 1 && choice <= 3) {
            return choice;
        }
        cout << "Illegal door." << endl;
    }
}

Tree * initTree() {
    Tree * root = new Tree;
    root->value = "very";

    root->left = new Tree;
    root->left->value = "win";

    root->left->left = new Tree;
    root->left->left->value = "you";
    root->left->left->left = NULL;
    root->left->left->right = NULL;

    root->left->right = new Tree;
    root->left->right->value = "a";
    root->left->right->left = NULL;
    root->left->right->right = NULL;

    root->right = new Tree;
    root->right->value = "big";
    root->right->left = NULL;

    root->right->right = new Tree;
    root->right->right->value = "prize";
    root->right->right->left = NULL;
    root->right->right->right = NULL;

    return root;
}

void doorOne(Tree * tree) {
    if(tree == NULL) return;
    cout << tree->value << endl;
    doorOne(tree->left);
    doorOne(tree->right);
}

void doorTwo(Tree * tree) {
    if(tree == NULL) return;
    doorTwo(tree->left);
    cout << tree->value << endl;
    doorTwo(tree->right);
}

void doorThree(Tree * tree) {
    if(tree == NULL) return;
    doorThree(tree->left);
    doorThree(tree->right);
    cout << tree->value << endl;
}

int main() {
    setConsoleFont("courier-32");
    introduction();
    Tree * tree = initTree();
    int choice = getUserChoice();
    suspense();
    switch (choice) {
        case 1: doorOne(tree); break;
        case 2: doorTwo(tree); break;
        case 3: doorThree(tree); break;
    }
    return 0;
}
