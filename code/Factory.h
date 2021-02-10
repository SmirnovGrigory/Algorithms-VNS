#ifndef FACTORY_H
#define FACTORY_H

#include <vector>
#include <string>

using namespace std;

class Factory {
private:
    int **matrix;
    vector<int> parts;
    vector<int> machines;
    int partsNumb = 0;
    int machinesNumb = 0;
    int NumberOfOnes = 0;
    int NumberOfClasters = 1;

    double bestCost = 0;
    vector<int> bestParts; //resize in costructor
    vector<int> bestMachines;

public:
    explicit Factory(const string &fileName = "");

    ~Factory();

    int getNumberOfOnesInClasters();

    int getCapacityOfClasters();

    double getCost();

    void printMatrix();

    void localSearch();

    bool switchPartCluster();

    bool switchMachineCluster();

    bool switchClaster();

    void uniteClusters();

    void divideClusters();

    void shaking();

    void VND(int iterations);
};

#endif // !FACTORY_H

