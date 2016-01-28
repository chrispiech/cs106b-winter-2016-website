/*
 * CS 106B, Chris Piech
 * This program demonstrates the use of the Stanford C++ Set class.
 * A set is a collection without duplicates that efficiently supports
 * the core operations of adding, removing, and searching for elements.
 */

#include <fstream>
#include <iostream>
#include <iomanip>
#include "console.h"
#include "timer.h"
#include "hashset.h"
#include "lexicon.h"
#include "set.h"
#include "vector.h"
#include "filelib.h"

using namespace std;

void searchFiles(string currPath, string & goal) {
    // is it a regular file (eg not a folder)
    if(!isDirectory(currPath)) {
        // "websites/asdfsdf/asdfasdfasdf/treasure.jpg" -> "treasure.jpg"
        if(getTail(currPath) == goal) {
            cout << currPath << endl;
        }
    } else {

        // get all next states
        Vector<string> dirFiles;
        listDirectory(currPath, dirFiles);

        // recurse on all next states
        for(string file : dirFiles) {
            string next = currPath + "/" + file;
            searchFiles(next, goal);
        }
    }
}

void exploreFiles(string currPath) {
    // is it a regular file (eg not a folder)
    if(!isDirectory(currPath)) {
        // does nothing...
    } else {

        // get all next states
        Vector<string> dirFiles;
        listDirectory(currPath, dirFiles);

        // recurse on all next states
        for(string file : dirFiles) {
            string next = currPath + "/" + file;
            exploreFiles(next);
        }

        cout << currPath << endl;
    }
}

int main() {

    string root = "/Users/cpiech/Documents/Teaching/cs106b/2016-winter/website";
    string goal = "treasure.jpg";

    cout << "looking..." << endl;

    searchFiles(root, goal);

    cout << "done" << endl;
    return 0;
}

