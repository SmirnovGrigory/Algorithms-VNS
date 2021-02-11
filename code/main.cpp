#include <iostream>

#include "Factory.h"

template<typename T>
void print(T t) {
    cout << t << '\n';
}

void test20x20() {
    Factory solution("test20x20");
    solution.VND(1000000);
}

signed main() {
    test20x20();
    return 0;
}
