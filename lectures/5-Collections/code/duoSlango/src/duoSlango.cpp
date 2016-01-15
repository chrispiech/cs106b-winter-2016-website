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
#include "gwindow.h"
#include "gobjects.h"
#include "pqueue.h"
#include "ginteractors.h"
#include "gevents.h"

using namespace std;

// some constants
const int N_ANSWERS = 4;
const int N_DISTRACTORS = N_ANSWERS - 1;
const int SCREEN_WIDTH = 700;
const int SCREEN_HEIGHT = 400;

Map<string, string> loadTranslations(string fileName);
void askQuestion(GWindow & gw, string word, Vector<string> answers, int correctIndex);

int main() {
    GWindow gw(SCREEN_WIDTH, SCREEN_HEIGHT);
    gw.setTitle("Duo Slango");

    Map<string, string> englishToSpanish = loadTranslations("translations.txt");
    Vector<string> allSpanish = englishToSpanish.values();

    for(string question : englishToSpanish) {
        // 0. get answer
        string answer = englishToSpanish.get(question);

        // 1. make distractors
        Set<string> distractors;
        while(distractors.size() < N_DISTRACTORS) {
            int index = randomInteger(0, allSpanish.size() - 1);
            string dis = allSpanish[index];
            if(dis != answer) {
                distractors.add(dis);
            }
        }


        PriorityQueue<string> answerQueue;
        answerQueue.enqueue(answer, random());
        for(string dis : distractors) {
            answerQueue.enqueue(dis, random());
        }
        int correctIndex = 0;
        Vector<string> answers;
        for(int i = 0; i < N_ANSWERS; i++) {
            string ans = answerQueue.dequeue();
            if(ans == answer) correctIndex = i;
            answers.add(ans);
        }


        askQuestion(gw, question, answers, correctIndex);

    }

    gw.clear();
    return 0;
}

/* Load Translations
 * This method does the file reading that we have come to learn
 * live and love. I saved the translations one per line with a
 * colon separating the spanish and the english parts. This
 * function breaks apart each line, and happily adds the two
 * to a Map from english to spanish.
 */
Map<string, string> loadTranslations(string fileName) {
    ifstream fileStream;
    openFile(fileStream, fileName);

    Map<string, string> englishToSpanish;
    string line;
    while(getline(fileStream, line)) {
        int splitIndex = line.find(":");
        string english = line.substr(0, splitIndex);
        string spanish = line.substr(splitIndex + 1);
        // this is the best line in the function
        englishToSpanish[english] = spanish;
    }

    return englishToSpanish;
}

/*********************************************************************
 *                   QUESTION VISUALIZATION                          *
 * This is not required CS106B knowledge, but feel free to take a    *
 * cheeky peek in case you are curious.                              *
 *********************************************************************/

const int BUTTON_WIDTH = 300;
const int BUTTON_HEIGHT = 100;

void drawButton(GWindow & gw, string word, double px, double py) {
    int middleX = px * gw.getWidth();
    int middleY = py * gw.getHeight();
    int x = middleX - BUTTON_WIDTH / 2;
    int y = middleY - BUTTON_HEIGHT / 2;
    GLabel * label = new GLabel(word);
    label->setFont("SansSerif-24");
    GRoundRect * rect = new GRoundRect(x, y, BUTTON_WIDTH, BUTTON_HEIGHT);
    rect->setFillColor("#7DDD00");
    rect->setColor("#7DDD00");
    rect->setFilled(true);
    gw.add(rect);
    gw.add(label, middleX - label->getWidth()/2, middleY + label->getFontAscent()/2);
}

void addCenteredImage(GWindow & gw, string fileName) {
    GImage * img = new GImage(fileName);
    int x = (gw.getWidth() - img->getWidth()) / 2;
    int y = (gw.getHeight() - img->getHeight()) / 2;
    gw.add(img, x, y);
}

void askQuestion(GWindow & gw, string word, Vector<string> answers, int correctIndex) {
    gw.clear();
    GRect * bkg = new GRect(0, 0, gw.getWidth(), gw.getHeight());
    bkg->setFilled(true);
    bkg->setColor("#479DFC");
    gw.add(bkg);
    GImage* bird = new GImage("bird.png");
    bird->scale(0.3);
    gw.add(bird);
    GLabel * wordLabel = new GLabel(word);
    wordLabel->setColor("white");
    wordLabel->setFont("SansSerif-42");
    gw.add(wordLabel, (gw.getWidth() - wordLabel->getWidth())/2, gw.getHeight() * .15 );

    drawButton(gw, answers[0], 1./4, .4);
    drawButton(gw, answers[1], 3./4, .4);
    drawButton(gw, answers[2], 1./4, .8);
    drawButton(gw, answers[3], 3./4, .8);

    while (true) {
        GMouseEvent e = waitForEvent();
        if (e.getEventType() == MOUSE_PRESSED) {
            GObject * obj = gw.getGObjectAt(e.getX(), e.getY());
            if(obj != bkg) {
                bool left = e.getX() < gw.getWidth() /2;
                bool top = e.getY() < gw.getHeight() * 0.6;
                bool correct = false;
                if(top  && left  && correctIndex == 0) correct = true;
                if(top  && !left && correctIndex == 1) correct = true;
                if(!top && left  && correctIndex == 2) correct = true;
                if(!top && !left && correctIndex == 3) correct = true;
                if(correct) {
                    addCenteredImage(gw, "gold.png");
                } else {
                    addCenteredImage(gw, "sad.png");
                }
                break;
            }
        }
    }
    pause(1000);
}





