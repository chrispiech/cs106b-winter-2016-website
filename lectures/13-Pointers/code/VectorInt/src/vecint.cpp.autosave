#include "vecint.h"
#include <iostream>
#include <math.h>
#include "gwindow.h"
#include "gobjects.h"
using namespace std;

static const int INIT_SIZE = 10;

VecInt::VecInt() {
    data = new int[INIT_SIZE];
    usedSize = 0;
    allocatedSize = INIT_SIZE;
}

void VecInt::add(int v){
    data[usedSize] = v;
    usedSize++;
    if(usedSize == allocatedSize) {
        doubleAllocation();
    }
}

void VecInt::doubleAllocation() {
    allocatedSize *= 2;
    int * newData = new int[allocatedSize];
    for(int i = 0; i < usedSize; i++) {
        newData[i] = data[i];
    }
    delete[] data;
    data = newData;
}

int VecInt::get(int index){
    return data[index];
}

int VecInt::size() {
    return usedSize;
}

VecInt::~VecInt() {
    delete[] data;
}

