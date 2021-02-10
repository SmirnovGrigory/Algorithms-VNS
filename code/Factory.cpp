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

Factory::Factory(const string &fileName) {
    ifstream *input;
    if (!fileName.empty()) {
        input = new ifstream("../tests/" + fileName);
        *input >> this->machinesNumb >> this->partsNumb;
    } else {
        cin >> this->machinesNumb >> this->partsNumb;
    }
    this->matrix = new int *[this->machinesNumb];
    rep(machinesNumb) this->matrix[i] = new int[this->partsNumb];
    if (!fileName.empty()) {
        rep(machinesNumb) {
            int ones;
            int index;
            *input >> ones;
            repj(ones) {
                *input >> index;
                matrix[i][--index] = 1;
            }
        }
    } else {
        rep(machinesNumb) {
            int ones;
            int index;
            cin >> ones;
            repj(ones) {
                cin >> index;
                matrix[i][--index] = 1;
            }
        }
    }
}

int Factory::getNumberOfOnesInClasters() {
  int result=0;
  rep(machinesNumb)
    repj(partsNumb)
      if (matrix[i][j] == 1 && machines[i] == parts[j])
        result++;
  return result;
}

int Factory::getCapacityOfClasters() {
  int result = 0;
  rep(NumberOfClasters) {
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
  int onesInClasters = getNumberOfOnesInClasters();
  return onesInClasters / (NumberOfOnes + getCapacityOfClasters() - onesInClasters);
}

void Factory::printMatrix() {
  rep(machinesNumb) {
    repj(partsNumb)
      cout << matrix[i][j] << " ";
    cout << "\n";
  }
}

bool Factory::switchPartCluster() {
  rep(partsNumb)
    repj(NumberOfClasters) 
      if (parts[i]!=j) {
        double oldCap = 0, oldIn1 = 0;
        for (int k=0; k<machinesNumb; k++)
          if (machines[k] == parts[i]) {
            oldCap++;
            if (matrix[k][i] == 1)
              oldIn1++;
          }
        double newCap = 0, newIn1=0;
        for (int k = 0; k < machinesNumb; k++)
          if (machines[k] == j) {
            newCap++;
            if (matrix[k][i] == 1)
              newIn1++;
          }
        if (newIn1 / newCap > oldIn1 / oldCap) {
          parts[i] = j;
          return true;
        }
      }
  return false;
}

bool Factory::switchMachineCluster() {
  rep(machinesNumb)
    repj(NumberOfClasters)
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

bool Factory::switchClaster() {
  random_device seed;
  if (seed()%2) {
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
  while (switchClaster());
}

void Factory::uniteClusters() {
  random_device seed;
  int firstCluster = seed() % NumberOfClasters;
  int secondCluster = seed() % (NumberOfClasters-1);
  if (secondCluster >= firstCluster)
    secondCluster++;
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
  NumberOfClasters--;
}

void Factory::divideClusters() {
  random_device seed;
  int clusterNumb = seed() % NumberOfClasters;

}

void Factory::shaking() {
  if (NumberOfClasters == 1) {
    divideClusters();
    return;
  }
  if (NumberOfClasters == min(partsNumb, machinesNumb)) {
    uniteClusters();
    return;
  }
  random_device seed;
  if (seed() % 2)
    uniteClusters();
  else
    divideClusters();
}

void Factory::VND(int iterations) {
  //gen start solution
  rep(iterations) {
    shaking();
    localSearch();
    if (getCost() > bestCost) {
      //copy vectors
      bestCost = getCost();
    }
  }
}

