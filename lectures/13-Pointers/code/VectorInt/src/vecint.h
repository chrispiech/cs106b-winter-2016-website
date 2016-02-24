#ifndef VECINT
#define VECINT
#include <iostream>
#include "gwindow.h"
#include "gobjects.h"
using namespace std;

class VecInt {
public:
    VecInt();
    ~VecInt();

    void add(int v);
    int get(int index);
    int size();

private:
    void doubleAllocation();

    int * data;
    int allocatedSize;
    int usedSize;
};

#endif // VECINT
