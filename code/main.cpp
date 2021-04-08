#include <iostream>

#include "Factory.h"

template<typename T>
void print(T t) {
    cout << t << '\n';
}

void test20x20() {
    Factory solution("test20x20");
    solution.VND(10000);
}

void test24x40() {
    Factory solution("test24x40");
    solution.VND(10000);
}

void test28x46() {
    Factory solution("test28x46");
    solution.VND(10000);
}

void test30x90() {
    Factory solution("test30x90");
    solution.VND(10000);
}

void test37x53() {
    Factory solution("test37x53");
    solution.VND(10000);
}

void test50x150() {
    Factory solution("test50x150");
    solution.VND(10000);
}

signed main() {
//    test20x20();
    test20x20();
    return 0;
}
