#include "Factory.h"
#include <iostream>

Factory::Factory() {
	cin >> machinesNumb >> partsNumb;
	matrix = new bool* [machinesNumb];
	for (int i = 0; i < machinesNumb; i++)
		matrix[i] = new bool[partsNumb];

	parts.resize(partsNumb);
	machines.resize(machinesNumb);

	for (int i = 0; i < machinesNumb; i++)

}

Factory::~Factory() {
	for (int i = 0; i < machinesNumb; i++)
		delete[] matrix[i];
	delete[] matrix;
}