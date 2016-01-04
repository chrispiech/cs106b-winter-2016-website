#include <iostream>  // This is a true classic.
#include "console.h" // This is a Stanford Library!
#include "random.h"  // Another Stanford Library
using namespace std; // The best namespace.

int main() {

    cout << "This is a guessing game. It's rad." << endl;
    cout << "Try and guess my secret number. Its between ";
    cout << "1 and 100." << endl;

    int secret = randomInteger(1,100);

    int guess = -1;
    while(guess != secret) {

        cout << "your guess: ";
        cin >> guess;

        if(guess == secret) {
            cout << "Great job!" << endl;
        } else if(guess < secret) {
            cout << "Too low" << endl;
        } else {
            cout << "Too high" << endl;
        }
    }



    return 0;
}

