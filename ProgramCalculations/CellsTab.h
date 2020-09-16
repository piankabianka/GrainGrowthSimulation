#pragma once
#include "Cell.h"
#include <iostream>
using namespace std;

struct CellsTab {

	//Cell** cellsTab;
	int** cellsTab;

	int cellsNumberW;
	int cellsNumberH;

	CellsTab();
	void showCellsTab();
};