#ifndef FACTORY_H
#define FACTORY_H

#include <vector>
using namespace std;

class Factory {
private:
	bool** matrix;
	vector<int> parts;
	vector<int> machines;
	int partsNumb = 0;
	int machinesNumb = 0;
	int NumberOfOnes = 0;
	int NumberOfClasters = 1;

public:
	Factory();
	~Factory();
	int getNumberOfOnesInClasses();
	int getCapacityOfClasters();
	double getCost();
	
};

#endif // !FACTORY_H

