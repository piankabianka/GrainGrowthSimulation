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
	cellsTab.monteCarloIteration();
	cellsTab.saveDataToFile();
}