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
			//cellsTab[i][j].showCell();
			cout << cellsTab[i][j].color.r << ' ' << cellsTab[i][j].color.g << ' ' << cellsTab[i][j].color.b;
			cout << "\t";
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

void CellsTab::iteration() {
	copyTab = new Cell * [cellsNumberW+2];

	for (int i = 0; i < cellsNumberW+2; i++) {
		copyTab[i] = new Cell[cellsNumberH+2];
	}

	for (int i = 0; i < cellsNumberW+2; i++) {
		for (int j = 0; j < cellsNumberH+2; j++) {
			copyTab[i][j] = Cell();
		}
	}

	//srodek tablicy
	for (int i = 0; i < cellsNumberW; i++) {
		for (int j = 0; j < cellsNumberH; j++) {
			copyTab[i+1][j+1] = cellsTab[i][j];
		}
	}

	//rogi

	copyTab[0][0] = cellsTab[cellsNumberW - 1][cellsNumberH - 1];
	copyTab[cellsNumberW + 1][cellsNumberH + 1] = cellsTab[0][0];
	copyTab[0][cellsNumberH + 1] = cellsTab[cellsNumberW - 1][0];
	copyTab[cellsNumberW + 1][0] = cellsTab[0][cellsNumberH - 1];

	//brzegi

	for (int i = 1; i < cellsNumberH+1; i++) {
		copyTab[0][i] = cellsTab[cellsNumberW - 1][i-1];
		copyTab[cellsNumberW + 1][i] = cellsTab[0][i - 1];
	}

	for (int i = 1; i < cellsNumberW+1; i++) {
		copyTab[i][0] = cellsTab[i-1][cellsNumberH - 1];
		copyTab[i][cellsNumberH+1] = cellsTab[i-1][0];
	}

	cout << "\n Copy tab: \n";
	for (int i = 0; i < cellsNumberW + 2; i++) {
		for (int j = 0; j < cellsNumberH + 2; j++) {
			cout << copyTab[i][j].color.r << ' ' << copyTab[i][j].color.g << ' ' << copyTab[i][j].color.b;
			cout << "\t";
		}
		cout << endl;
	}
	
}

