#include <iostream>
#include <fstream>
#include <random>

#include "Factory.h"

#define rep(x) for(int i = 0; i < (x); ++i)
#define repj(x) for(int j = 0; j < (x); ++j)

Factory::~Factory() {
    for (int i = 0; i < machinesNumb; i++)
        delete[] matrix[i];
    delete[] matrix;
}

vector<int> Factory::split(string &s) {
    s += ' ';
    vector<int> result;
    string number;
    for (auto x : s) {
        if (x != ' ') {
            number += x;
        } else {
            result.push_back(atoi(number.c_str()));
            number = "";
        }
    }
    return result;
}

Factory::Factory(const string &fileName) {
    ifstream input("../tests/" + fileName);
    string dim;
    getline(input, dim);
    auto dimensionsData = split(dim);
    machinesNumb = dimensionsData[0];
    partsNumb = dimensionsData[1];
    machines.resize(machinesNumb);
    parts.resize(partsNumb);
    bestMachines.resize(machinesNumb);
    parts.resize(partsNumb);
    dividableClusters.resize(min(machinesNumb, partsNumb));
    dividableClusters[0] = true;
    auto dimensions = getClusterSize(0);
    if (dimensions.first > 1 && dimensions.second > 1)
        dividableClustersCount = 1;
    this->matrix = new int *[this->machinesNumb];
    rep(machinesNumb) this->matrix[i] = new int[this->partsNumb];
}

int Factory::getNumberOfOnesInClusters() {
    int result = 0;
    rep(machinesNumb)
        repj(partsNumb)
            if (matrix[i][j] == 1 && machines[i] == parts[j])
                result++;
    return result;
}

int Factory::getCapacityOfClusters() {
    int result = 0;
    rep(NumberOfClusters) {
        int machinesInCluster = 0;
        int partsInCluster = 0;
        repj(machinesNumb)
            if (machines[j] == i)
                machinesInCluster++;
        repj(partsNumb)
            if (parts[j] == i)
                partsInCluster++;
        result += machinesInCluster * partsInCluster;
    }
    return result;
}

double Factory::getCost() {
    int onesInClasters = getNumberOfOnesInClusters();
    return static_cast<double>(onesInClasters) / (NumberOfOnes + getCapacityOfClusters() - onesInClasters);
}

void Factory::printMatrix() {
    rep(machinesNumb) {
        repj(partsNumb)cout << matrix[i][j] << " ";
        cout << "\n";
    }
}

bool Factory::switchPartCluster() {
    rep(partsNumb)
        repj(NumberOfClusters)
            if (parts[i] != j) {
                double oldCap = 0, oldIn1 = 0;
                for (int k = 0; k < machinesNumb; k++)
                    if (machines[k] == parts[i]) {
                        oldCap++;
                        if (matrix[k][i] == 1)
                            oldIn1++;
                    }
                double newCap = 0, newIn1 = 0;
                for (int k = 0; k < machinesNumb; k++)
                    if (machines[k] == j) {
                        newCap++;
                        if (matrix[k][i] == 1)
                            newIn1++;
                    }
                if (newIn1 / newCap > oldIn1 / oldCap) {
                    parts[i] = j;
                    parts[i] = j;
                    return true;
                }
            }
    return false;
}

bool Factory::switchMachineCluster() {
    rep(machinesNumb)
        repj(NumberOfClusters)
            if (machines[i] != j) {
                double oldCap = 0, oldIn1 = 0;
                for (int k = 0; k < partsNumb; k++)
                    if (parts[k] == machines[i]) {
                        oldCap++;
                        if (matrix[i][k] == 1)
                            oldIn1++;
                    }
                double newCap = 0, newIn1 = 0;
                for (int k = 0; k < partsNumb; k++)
                    if (parts[k] == j) {
                        newCap++;
                        if (matrix[i][k] == 1)
                            newIn1++;
                    }
                if (newIn1 / newCap > oldIn1 / oldCap) {
                    machines[i] = j;
                    return true;
                }
            }
    return false;
}

bool Factory::switchCluster() {
    random_device seed;
    if (seed() % 2) {
        if (switchPartCluster())
            return true;
        if (switchMachineCluster())
            return true;
    } else {
        if (switchMachineCluster())
            return true;
        if (switchPartCluster())
            return true;
    }
    return false;
}

void Factory::localSearch() {
    while (switchCluster());
}

void Factory::uniteClusters() {
    random_device generator;
    uint firstCluster = generator() % NumberOfClusters;
    uint secondCluster = generator() % (NumberOfClusters - 1);
    auto firstDimension = getClusterSize(firstCluster);
    auto secondDimension = getClusterSize(secondCluster);
    if (secondCluster >= firstCluster)
        secondCluster++;
    if (firstDimension.first > 1 &&
        firstDimension.second > 1 &&
        secondDimension.first > 1 &&
        secondDimension.second > 1) {
        dividableClustersCount--;
    }
    if (firstCluster > secondCluster)
        swap(firstCluster, secondCluster);
    rep(partsNumb) {
        if (parts[i] == secondCluster)
            parts[i] = firstCluster;
        if (parts[i] > secondCluster)
            parts[i]--;
    }
    rep(machinesNumb) {
        if (machines[i] == secondCluster)
            machines[i] = firstCluster;
        if (machines[i] > secondCluster)
            machines[i]--;
    }
    NumberOfClusters--;
    auto dimensions = getClusterSize(firstCluster);
    if (dimensions.first > 1 and dimensions.second > 1) {
        dividableClusters[firstCluster] = true;
    }

    for (int i = secondCluster; i < NumberOfClusters; ++i) {
        dividableClusters[i] = dividableClusters[i + 1];
    }
}

void Factory::divideClusters() {
    random_device generator;
    vector<int> dividableClusterNumbers;
    rep(NumberOfClusters) {
        if (dividableClusters[i]) {
            dividableClusterNumbers.push_back(i);
        }
    }
    uint clusterToDivide = dividableClusterNumbers[generator() % dividableClustersCount];
    uint newCluster = NumberOfClusters;
    NumberOfClusters++;
    auto dimension = getClusterSize(clusterToDivide);
    uint newClusterMachines = generator() % (dimension.first - 1) + 1;
    uint newClusterParts = generator() % (dimension.second - 1) + 1;
    dividableClustersCount--;
    dividableClusters[clusterToDivide] = false;
    uint changedMachines = 0;
    uint changedParts = 0;
    rep(machinesNumb) {
        if (machines[i] == clusterToDivide && changedMachines < newClusterMachines) {
            machines[i] = newCluster;
            changedMachines++;
        }
    }
    rep(partsNumb) {
        if (parts[i] == clusterToDivide && changedParts < newClusterParts) {
            parts[i] = newCluster;
            changedParts++;
        }
    }
    auto firstDimension = getClusterSize(clusterToDivide);
    auto secondDimension = getClusterSize(newCluster);
    if (firstDimension.first > 1 && firstDimension.second > 1) {
        dividableClustersCount++;
        dividableClusters[clusterToDivide] = true;
    }
    if (secondDimension.first > 1 && secondDimension.second > 1) {
        dividableClustersCount++;
        dividableClusters[newCluster] = true;
    }
}

void Factory::shaking() {
    if (NumberOfClusters == 1) {
        divideClusters();
        return;
    }
    if (NumberOfClusters == min(partsNumb, machinesNumb)) {
        uniteClusters();
        return;
    }
    random_device generator;
    if (generator() % 2)
        uniteClusters();
    else
        divideClusters();
}

void Factory::VND(int iterations) {
    generateStartSolution();
    rep(iterations) {
        shaking();
        localSearch();
        if (getCost() > bestCost) {
            copy(machines.begin(), machines.end(), bestMachines.begin());
            copy(parts.begin(), parts.end(), bestParts.end());
            bestCost = getCost();
        }
    }
}

pair<int, int> Factory::getClusterSize(int cluster) {
    int clusterMachines = 0;
    int clusterParts = 0;
    rep(machinesNumb)if (machines[i] == cluster)clusterMachines++;
    rep(partsNumb)if (parts[i] == cluster)clusterParts++;
    return {clusterMachines, clusterParts};
}

void Factory::generateStartSolution() {
    uint iterations = min(machinesNumb, partsNumb) / 3;
    rep(iterations) divideClusters();
}
