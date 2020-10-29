#pragma once
#include "Cell.h"
#include "Color.h"
#include <iostream>
#include <string>
using namespace std;

struct CellsTab {

	Cell** cellsTab;
	Cell** copyTab;

	int cellsNumberW;
	int cellsNumberH;
	int modifiedCells;
	int germsNumber;
	double kT;
	int bc;
	int nghb;
	double t1;
	double t2;
	double t3;
	double t4;
	

	CellsTab(string path);
	void showCellsTab();
	void grainGrowth();
	void singleIteration();
	void monteCarloIteration();
	void calculations();
	void copyCellTabToCopyTab();
	void clearCopyTab();

	bool checkIfColorExists(Color c);
	int countNeighbors(int index1, int index2);
	bool checkIfColorIsWhite(Color c);
	bool checkIfAllCellsAreModified();
	Color setNewCellColor(int nghbCounter, int indexI, int indexJ);
	Color generateRandomColor();

	void calculateEnergy(int i, int j);

	void calculateTemperatureForEveryCell();
	double getTemperatureForCell(double ksi, double eta);

	void saveDataToFile();
};