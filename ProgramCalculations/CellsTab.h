#pragma once
#include "Cell.h"
#include "Color.h"
#include <iostream>
using namespace std;

struct CellsTab {

	Cell** cellsTab;
	Cell** copyTab;

	int cellsNumberW;
	int cellsNumberH;
	int modifiedCells;
	

	CellsTab();
	void showCellsTab();
	void grainGrowth();
	void singleIteration();
	void monteCarloIteration();
	void calculations();
	void clearCopyTab();

	bool checkIfColorExists(Color c);
	int countNeighbors(int index1, int index2);
	bool checkIfColorIsWhite(Color c);
	bool checkIfAllCellsAreModified();
	Color setNewCellColor(int nghbCounter, int indexI, int indexJ);
	Color generateRandomColor();

	void calculateEnergy(int i, int j);
};