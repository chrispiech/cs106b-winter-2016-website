
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
   Tree * left;  // ZOMG Recursive Data
   Tree * right; // !@$#@# AGAIN!!!
};

bool isLeaf(Tree * tree) {
    if (tree->left != NULL) return false;
    if (tree->right != NULL) return false;
    return true;
}

bool wereYouThinkingOf(string category) {
    cout << "Were you thinking of ";
    cout << category;
    cout << "? ";
    string answer = getLine();
    return answer == "yes";
}

string whatWereYouThiningOf() {
    cout << "What were you thinking of? ";
    return getLine();
}

string getDiffCategory(string objectOne, string objectTwo) {
    cout << "What category separates " +objectOne;
    cout <<" from " + objectTwo;
    cout <<"? ";
    return getLine();
}

bool isObjectInCategory(string category, string object) {
    cout << "Is a " + object + " a ";
    cout << category;
    cout << "? ";
    return getLine() == "yes";
}

Tree * createNewQuestionNode(Tree * old) {
    string oldObject = old->text;
    string newObject = whatWereYouThiningOf();
    string newCategory = getDiffCategory(newObject, oldObject);

    // Create New Question Node
    Tree * questionNode = new Tree;
    questionNode->text = newCategory;

    // Create New Answer Node
    Tree * answerNode = new Tree;
    answerNode->text = newObject;
    answerNode->left = NULL;
    answerNode->right = NULL;

      // Rewire Nodes
    bool yes = isObjectInCategory(newCategory, newObject);
    if (yes) {
      questionNode->right = answerNode;
      questionNode->left = old;
    } else {
      questionNode->left = answerNode;
      questionNode->right = old;
    }
    return questionNode;
}

bool pensiveExplore(Tree * & tree) {
   bool correct = wereYouThinkingOf(tree->text);

   // Base case
   if(isLeaf(tree)) {
      if (correct) {
          cout << "I knew it!" << endl;
          return true;
      }
      cout << "Hmm that wasn't in my pensive." << endl;
      tree = createNewQuestionNode(tree);
      return false;
   }

   // Recursive case
   if (correct) {
      return pensiveExplore(tree->right);
   } else {
      return pensiveExplore(tree->left);
   }
}

int main() {
    Tree * root = new Tree;
    root->text = "Harry";
    root->left = NULL;
    root->right = NULL;

    while(true) {
        cout << "I am Dumbledore!" << endl;
        cout << "Think of an object and I will guess what you ";
        cout << "are thinking!" << endl;
        pensiveExplore(root);
        cout << endl;
    }

    return 0;
}
