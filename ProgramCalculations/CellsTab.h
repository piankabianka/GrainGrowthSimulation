#pragma once
#include "Cell.h"
#include "Color.h"
#include <iostream>
using namespace std;

struct CellsTab {

	Cell** cellsTab;
	//int** cellsTab;

	int cellsNumberW;
	int cellsNumberH;

	CellsTab();
	void showCellsTab();
	void grainGrowth();
	bool checkIfColorExists(Color c);
	Color generateRandomColor();
};