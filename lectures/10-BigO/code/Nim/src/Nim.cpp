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
#include "console.h"
#include "error.h"
#include "simpio.h"
#include "map.h"
#include "strlib.h"
using namespace std;

/*
 * Type: Player
 * ------------
 * This enumerated type differentiates the human and computer players.
 */
enum Player { HUMAN, COMPUTER };


/* Constants */
const int N_COINS = 21;       /* Initial number of coins          */
const int MAX_MOVE =  3;      /* Number of coins a player may take */

int getUserMove(int nCoins);
void announceResult(int nCoins, Player whoseTurn);
int getComputerMove(int nCoins);
int bestComputerScore(int nCoins, int & bestMove);
int bestHumanScore(int nCoins);


/*
 * Method: opponent
 * Usage: Player other = opponent(player);
 * ---------------------------------------
 * Returns the opponent of the player.  The opponent of the computer
 * is the human player and vice versa.
 */

Player opponent(Player player) {
   return (player == HUMAN) ? COMPUTER : HUMAN;
}

/*
 * Constant: STARTING_PLAYER
 * -------------------------
 * Indicates which player should start the game.
 */

const Player STARTING_PLAYER = HUMAN;


/*
 * Method: play
 * Usage: game.play();
 * -------------------
 * Plays one game of Nim with the human player.
 */

void play() {
  int nCoins = N_COINS;
  Player whoseTurn = STARTING_PLAYER;
  while (nCoins > 1) {
     cout << "There are " << nCoins << " coins in the pile." << endl;
     if (whoseTurn == HUMAN) {
        nCoins -= getUserMove(nCoins);
     } else {
        int nTaken = getComputerMove(nCoins);
        cout << "I'll take " << nTaken << "." << endl;
        nCoins -= nTaken;
     }
     whoseTurn = opponent(whoseTurn);
     cout << endl;
  }
  announceResult(nCoins, whoseTurn);
}

/*
* Method: printInstructions
* Usage: game.printInstructions();
* --------------------------------
* This method explains the rules of the game to the user.
*/

void printInstructions() {
  cout << "Welcome to the game of Nim!"  << endl;
  cout << "In this game, we will start with a pile of" << endl;
  cout << N_COINS << " coins on the table.  On each turn, you" << endl;
  cout << "and I will alternately take between 1 and" << endl;
  cout << MAX_MOVE << " coins from the table.  The player who" << endl;
  cout << "takes the last coin loses." << endl << endl;
}

/*
* Method: getComputerMove
* Usage: int nTaken = getComputerMove();
* --------------------------------------
* Figures out what move is best for the computer player and returns
* the number of coins taken.  The method first calls findGoodMove
* to see if a winning move exists.  If none does, the program takes
* only one coin to give the human player more chances to make a mistake.
*/
int getComputerMove(int nCoins) {
    int bestMove = 1;
    bestComputerScore(nCoins, bestMove);
    return bestMove;
}

/*
* Method: maxScore
* Usage: int score = maxScore(nCoins, bestMove);
* --------------------------------------
* Figures out the best score the computer thinks it can
* get, assuming the human plays optimally. Populates the
* parameter bestMove with the corresponding move.
*/
int bestComputerScore(int nCoins, int & bestMove) {
    // base case
    if(nCoins == 1) return -1;


    int limit = (nCoins < MAX_MOVE) ? nCoins : MAX_MOVE;
    int bestValue = -1;
    // loop over all legal moves
    for (int nTaken = 1; nTaken <= limit; nTaken++) {
        // calculate next state
        int remaining = nCoins - nTaken;
        // whats the best the human could do?
        int minValue = bestHumanScore(remaining);
        // chose the maximum of all those best human moves
        // the maxi-min if you will....
        if(minValue > bestValue) {
            bestValue = minValue;
            // keep track of what move led to the best score
            bestMove = nTaken;
        }
    }
    return bestValue;
}

/*
* Method: minScore
* Usage: int score = bestHumanScore(nCoins);
* --------------------------------------
* Figures out the best score the human could possibly
* get from this configuration. Negative scores are good
* for the human.
*/
int bestHumanScore(int nCoins) {
    int ignoreMove;
    return -bestComputerScore(nCoins, ignoreMove);
}


/*
* Method: getUserMove
* Usage: int nTaken = getUserMove();
* ----------------------------------
* Asks the user to enter a move and returns the number of coins taken.
* If the move is not legal, the user is asked to reenter a valid move.
*/

int getUserMove(int nCoins) {
  while (true) {
     int nTaken = getInteger("How many would you like? ");
     int limit = (nCoins < MAX_MOVE) ? nCoins : MAX_MOVE;
     if (nTaken > 0 && nTaken <= limit) return nTaken;
     cout << "That's cheating!  Please choose a number";
     cout << " between 1 and " << limit << "." << endl;
     cout << "There are " << nCoins << " coins in the pile." << endl;
  }
}

/*
* Method: announceResult
* Usage: announceResult();
* ------------------------
* This method announces the final result of the game.
*/

void announceResult(int nCoins, Player whoseTurn) {
  if (nCoins == 0) {
     cout << "You took the last coin.  You lose." << endl;
  } else {
     cout << "There is only one coin left." << endl;
     if (whoseTurn == HUMAN) {
        cout << "I win." << endl;
     } else {
        cout << "I lose." << endl;
     }
  }
}



/* Main program */

int main() {
   printInstructions();
   play();
   return 0;
}
