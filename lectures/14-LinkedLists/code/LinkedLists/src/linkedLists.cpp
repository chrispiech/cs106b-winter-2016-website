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
#include "grid.h"
#include "strlib.h"
using namespace std;

struct Cell {
    string value;
    Cell * next;
};

void printList(Cell * head) {
    Cell * curr = head;
    while(curr != NULL) {
        cout << curr->value << " -> ";
        curr = curr->next;
    }
    cout << "NULL" << endl;
}

int main() {

    Cell * head = new Cell;
    head->value = "socks";
    head->next = NULL;
    printList(head);

    Cell * temp = new Cell;
    temp->value = "rocks";
    temp->next = head;
    head = temp;
    printList(head);

    temp = new Cell;
    temp->value = "cs106b";
    temp->next = head;
    head = temp;
    printList(head);

    return 0;
}
