#include <iostream>

#include "Factory.h"

template<typename T>
void print(T t) {
    cout << t << '\n';
}

signed main() {
    Factory solution("simple-test");
    solution.printMatrix();
    print(solution.getCost());
    solution.printAnswer();
    print(solution.getClusterCount());
    print(solution.getNumberOfOnesInClusters());
    print(solution.getCapacityOfClusters());
    solution.generateStartSolution();
    print(solution.getCapacityOfClusters());
    print(solution.getClusterCount());
    print(solution.getCost());
    solution.VND(1000);
    return 0;
}
