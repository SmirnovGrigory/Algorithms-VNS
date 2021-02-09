#include <iostream>
#include <fstream>

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

int Factory::getNumberOfOnesInClasses() {
    return 0;
}

int Factory::getCapacityOfClasters() {
    return 0;
}

double Factory::getCost() {
    return 0;
}
