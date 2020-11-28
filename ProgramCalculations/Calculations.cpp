#include <iostream>
#include "Calculations.h"
#include "CellsTab.h"
using namespace std;

Calculations::Calculations(string path) {
	dataPath = path;
	this->cellsTab = CellsTab(dataPath);
}

void Calculations::calculate() {

	cout << "Rozrost ziaren" << endl;
	cellsTab.grainGrowth();
	cellsTab.saveDataToFile();
	cout << "Iteracje" << endl;
	cellsTab.doIterations();
	cout << "Monte Carlo" << endl;
	for (int i = 0; i < 5; i++) {
		cellsTab.monteCarloIteration();
		cellsTab.saveDataToFile();
	}
	
}