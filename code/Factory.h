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

public:
    explicit Factory(const string &fileName = "");

    ~Factory();

    int getNumberOfOnesInClasses();

    int getCapacityOfClasters();

    double getCost();

};

#endif // !FACTORY_H

