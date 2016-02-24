
#include <cctype>
#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include "console.h"
#include "filelib.h"
#include "grid.h"
#include "gwindow.h"
#include "simpio.h"
using namespace std;

struct Tree {
    string text;  // If leaf this is an answer else is a question
    Tree * left;  // Concepts where the answer is false
    Tree * right; // Concepts where the answer is true
};


/****************************************
 *     CHRIS HELPER METHODS             *
 ****************************************/
bool askYesOrNoCategory(string category) {
    string prompt = "Are you thinking of " + category + "?";
    return getYesOrNo(prompt);
}

string getDiffCategory(string objectOne, string objectTwo) {
    cout << "What category separates " +objectOne;
    cout <<" from " + objectTwo << "? ";
    return getLine();
}

/****************************************
 *     OUR CODE!                        *
 ****************************************/

Tree * buildTree(string text) {
    Tree * tree = new Tree;
    tree->text = text;
    tree->left = NULL;
    tree->right = NULL;
    return tree;
}

bool isLeaf(Tree * t) {
    return t->left == NULL && t->right == NULL;
}

Tree * addConcept(Tree * oldLeaf) {
    string newCategory = getLine("What were you thinking? ");
    Tree * newLeaf = buildTree(newCategory);

    string newQuestion = getDiffCategory(newCategory, oldLeaf->text);
    Tree * newQNode = buildTree(newQuestion);

    newQNode->right = newLeaf;
    newQNode->left = oldLeaf;

    return newQNode;
}

bool explorePensive(Tree * & root) {

    if(isLeaf(root)) {
        bool answer = askYesOrNoCategory(root->text);
        if(!answer) {
            root = addConcept(root);
        }
        return answer;
    } else {
        bool answer = askYesOrNoCategory(root->text);
        if(answer) {
            return explorePensive(root->right);
        } else {
            return explorePensive(root->left);
        }
    }

}

int main() {

    Tree * banana = buildTree("Banana");
    Tree * dj = buildTree("DJ Khaled");
    Tree * fruit = buildTree("Fruit");
    fruit->right = banana;
    fruit->left = dj;

    Tree * root = fruit;

    while(true) {
        cout << "I can guess what you are thinking!" << endl;
        bool correct = explorePensive(root);
        if(correct) {
            cout << "Knew it!" << endl;
        }
        cout << endl;
    }

    return 0;
}
