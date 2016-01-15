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
#include "hashmap.h"
#include "map.h"
#include "set.h"
#include "simpio.h"
#include "filelib.h"

using namespace std;

// Some useful constants
const int N_MEDS = 1000;
const int RANDOM_MAX = 1000000;
const bool VERBOSE = true;

string getKey(int index);

int main() {
    cout << "M Pedigree" << endl;
    setRandomSeed(0);

    Map<string,string> medicineStatus;

    for(int i = 0; i < N_MEDS; i++) {
        string key = getKey(i);
        medicineStatus[key] = "Fresh";
        if(VERBOSE) cout << key << endl;
    }

    // this loop asks for codes to check
    while (true) {
        string key = getLine("Code to check (0 to exit)");
        if (key == "") {
            break;
        } else {
            if(!medicineStatus.containsKey(key)) {
                cout << "Fake" << endl;
            } else {
                cout << medicineStatus[key] << endl;
                medicineStatus[key] = "Checked";
            }
            cout << endl;
        }
    }

    return 0;
}

/* Get Key
 * This function takes an index (which should be a unique number
 * never before seen by getKey) and returns a code that should
 * be written on the medicine bottle.
 */
string getKey(int index) {
    int randomNum = randomInteger(0, RANDOM_MAX);
    string compound = "";
    compound += integerToString(randomNum);
    compound += integerToString(index);
    return compound;
}


