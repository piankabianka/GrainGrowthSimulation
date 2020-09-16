#include "Cell.h"
#include "CellsTab.h"
#include "GlobalData.h"

#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int xIndex = 0;
int yIndex = 0;
int modifiedNumber = 0;

CellsTab::CellsTab() {
	
	GlobalData data;

	cellsNumberW = data.height;
	cellsNumberH = data.width;

	cellsTab = new Cell* [cellsNumberW];

	for (int i = 0; i < cellsNumberW; i++) {
		cellsTab[i] = new Cell[cellsNumberH];
	}

	for (int i = 0; i < cellsNumberW; i++) {
		for (int j = 0; j < cellsNumberH; j++) {
			cellsTab[i][j] = Cell();
		}
	}
}

void CellsTab::showCellsTab() {
	for (int i = 0; i < cellsNumberW; i++) {
		for (int j = 0; j < cellsNumberH; j++) {
			cellsTab[i][j].showCell();
		}
		cout << endl;
	}
}

bool CellsTab::checkIfColorExists(Color c) {
	Color color;
	bool condition = false;
	for (int i = 0; i < cellsNumberW; i++) {
		for (int j = 0; j < cellsNumberH; j++) {
			if (color.compareColors(cellsTab[i][j].color, c)) {
				condition=true;
				break;
			}
		}
	}
	return condition;
}

 Color CellsTab::generateRandomColor() {
	Color c;
	srand(time(NULL));
	c.r = (rand() % 255);
	c.g = (rand() % 255);
	c.b = (rand() % 255);
	return c;
}

void CellsTab::grainGrowth() {
	srand(time(NULL));
	GlobalData data;

	do {

		xIndex = (rand() % cellsNumberW);
		yIndex = (rand() % cellsNumberH);

		if (!cellsTab[xIndex][yIndex].grain) {
			Color c = generateRandomColor();
			if (!checkIfColorExists(c)) {
				cellsTab[xIndex][yIndex].color = c;
				modifiedNumber++;
				cellsTab[xIndex][yIndex].grain = true;
			}
		}

	} while (modifiedNumber < data.germsNumber);
	

}

