
#include <fstream>
#include <iostream>
#include <iomanip>
#include <math.h>
#include "console.h"
#include "filelib.h"
#include "simpio.h"

using namespace std;

int gcd(int a, int b) {
    if(b == 0) {
        return a;
    } else {
        return gcd(b, a % b);
    }
}

void test(int a, int b, int expected) {
    int result = gcd(a, b);
    cout << "gcd(" << a << ", " << b << ") = ";
    cout << result << "\t";
    if(result == expected) {
        cout << "[passed]";
    } else {
        cout << "[failed]";
    }
    cout << endl;
}

int main() {
    test(462, 1071, 21);
    test(1071, 462, 21);
    test(54, 24, 6);
    test(42, 56, 14);
    return 0;
}

