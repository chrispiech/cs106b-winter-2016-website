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
#include <fstream>
#include "console.h"
#include "simpio.h"
#include "filelib.h"
#include "strlib.h"
using namespace std;

// new variable type called Tree
struct Tree {
    string label;
    Tree * left; // wwwwwooooah
    Tree * right;
};

/* Function: Load Binary Tree
 * ---------------------------
 * In the file, each tree will always be nodeName followed by
 * the left tree and then the right tree. Every tree must have
 * both children listed. Children can be NULL.
 */
Tree * loadBinaryTree(ifstream& fileStream) {
    string nextLine;
    getline(fileStream, nextLine);
    nextLine = trim(nextLine);

    if(nextLine == "NULL") return NULL;

    Tree * tree = new Tree;
    tree->label = nextLine;
    tree->left = loadBinaryTree(fileStream);
    tree->right = loadBinaryTree(fileStream);

    return tree;
}

/* Function: Load Tree
 * ---------------------------
 * Given a fileName, loads the contents of that file
 * into a brand new binary tree.
 */
Tree * loadTree(string fileName) {
    ifstream fileStream;
    openFile(fileStream, fileName);
    return loadBinaryTree(fileStream);
}

void printIndentation(int n) {
    for(int i = 0; i < n; i++) {
        cout << "  ";
    }
}

void printTree(Tree * root, int depth) {
    // Base case
    if(root == NULL) return;

    // Space case
    printIndentation(depth);
    cout << root->label << endl;
    printTree(root->left, depth + 1);
    printTree(root->right, depth + 1);
}

int main() {
    setConsoleFont("courier-24");

    Tree * tree = loadTree("tree2.txt");
    printTree(tree, 0);

    return 0;
}
