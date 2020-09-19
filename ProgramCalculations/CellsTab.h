#pragma once
#include "Cell.h"
#include "Color.h"
#include <iostream>
using namespace std;

struct CellsTab {

	Cell** cellsTab;
	Cell** copyTab;
	//int** cellsTab;

	int cellsNumberW;
	int cellsNumberH;

	CellsTab();
	void showCellsTab();
	void grainGrowth();
	void iteration();

	bool checkIfColorExists(Color c);
	int countNeighbors(int index1, int index2);
	bool checkIfColorIsWhite(Color c);
	void setNewCellColor(int nghbCounter, int indexI, int indexJ);
	Color generateRandomColor();
};