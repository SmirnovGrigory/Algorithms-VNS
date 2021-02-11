#include <iostream>

#include "Factory.h"

template<typename T>
void print(T t) {
    cout << t << '\n';
}

signed main() {
    Factory solution("simple-test");
    solution.printMatrix();
    solution.printAnswer();
    solution.generateStartSolution();
    solution.VND(1000);
    return 0;
}
