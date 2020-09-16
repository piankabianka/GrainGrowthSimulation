#include "Cell.h"
#include "CellsTab.h"
#include "GlobalData.h"
#include <iostream>

using namespace std;


CellsTab::CellsTab() {
	
	GlobalData data;

	cellsNumberW = data.height;
	cellsNumberH = data.width;

	cellsTab = new int* [cellsNumberW];

	for (int i = 0; i < cellsNumberW; i++) {
		cellsTab[i] = new int[cellsNumberH];
	}

	for (int i = 0; i < cellsNumberW; i++) {
		for (int j = 0; j < cellsNumberH; j++) {
			cellsTab[i][j] = 1;
		}
	}
}

void CellsTab::showCellsTab() {
	for (int i = 0; i < cellsNumberW; i++) {
		for (int j = 0; j < cellsNumberH; j++) {
			cout << cellsTab[i][j] << " ";
		}
		cout << endl;
	}
}