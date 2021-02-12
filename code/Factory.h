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
    int NumberOfClusters = 1;

    double bestCost = 0;
    vector<int> bestParts; //resize in costructor
    vector<int> bestMachines;

    vector<bool> dividableClusters;
    int dividableClustersCount;

public:
    explicit Factory(const string &fileName = "");

    //~Factory();

    static vector<int> split(string &s);

    int getNumberOfOnesInClusters();

    int getCapacityOfClusters();

    int getDividableClustersCount();

    void generateStartSolution();

    double getCost();

    void printMatrix();

    void localSearch();

    bool switchPartCluster();

    bool switchMachineCluster();

    bool switchCluster();

    void uniteClusters();

    void divideClusters();

    void shaking();

    void VND(int iterations);

    void testFunction();

    void printAnswer();

    void reduceClustersAfterMerge(int cluster);

    void updateDividableClustersVector();

    [[nodiscard]] int getClusterCount() const;

    void recountAbilityToDivide(int cluster);

    pair<int, int> getClusterSize(int cluster);
};

#endif // !FACTORY_H

