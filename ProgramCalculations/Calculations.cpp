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
	//cellsTab.saveDataToFile();
	cout << "Iteracje" << endl;
	cellsTab.doIterations();
	cout << "Monte Carlo" << endl;
	cellsTab.saveDataToFile();
	for (int i = 0; i < cellsTab.mcSteps; i++) {
		cellsTab.monteCarloIteration();
		if (i % 50 == 0) {
			cellsTab.saveDataToFile();
		}
	}
	
	/*
	cellsTab.calculateTemperatureForEveryCell();
	cout << endl;
	cellsTab.showCellsTab();
	cout << endl;
	cellsTab.checkData();
	cout << endl;

	for (int i = 0; i < cellsTab.cellsNumberW + 2; i++) {
		for (int j = 0; j < cellsTab.cellsNumberH + 2; j++) {
			cout << cellsTab.temperatureTab[i][j] << "\t";
		}
		cout << endl;
	}*/
}