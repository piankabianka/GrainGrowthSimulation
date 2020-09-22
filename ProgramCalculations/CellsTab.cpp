#include "Cell.h"
#include "CellsTab.h"
#include "GlobalData.h"

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <map>
#include <vector>
#include <algorithm> 
#include <string>
#include <functional>

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

	copyTab = new Cell * [cellsNumberW + 2];

	for (int i = 0; i < cellsNumberW + 2; i++) {
		copyTab[i] = new Cell[cellsNumberH + 2];
	}

	for (int i = 0; i < cellsNumberW + 2; i++) {
		for (int j = 0; j < cellsNumberH + 2; j++) {
			copyTab[i][j] = Cell();
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
bool CellsTab::checkIfColorIsWhite(Color c) {
	if (c.r == 255 && c.g == 255 && c.b == 255) {
		return true;
	}
	else {
		return false;
	}
}

int CellsTab::countNeighbors(int index1, int index2) {
	int counter = 0;

	if (!checkIfColorIsWhite(copyTab[index1-1][index2].color))
		counter++;


	if (!checkIfColorIsWhite(copyTab[index1][index2+1].color))
		counter++;
	
	if (!checkIfColorIsWhite(copyTab[index1 + 1][index2].color))
		counter++;
	
	if (!checkIfColorIsWhite(copyTab[index1][index2-1].color))
		counter++;
	
	return counter;
}


Color CellsTab::setNewCellColor(int nghbCounter, int indexI, int indexJ) {
	Color c;
	
	if(nghbCounter!=0) {

		Color colorTab[4];

		colorTab[0] = copyTab[indexI - 1][indexJ].color;
		colorTab[1] = copyTab[indexI][indexJ + 1].color;
		colorTab[2] = copyTab[indexI + 1][indexJ].color;
		colorTab[3] = copyTab[indexI][indexJ - 1].color;

		int c1 = 0;
		int c2 = 0;
		int c3 = 0;
		int c4 = 0;

		for (int i = 0; i < 4; i++) {
			if (c.compareColors(colorTab[i], colorTab[0])) {
				c1++;
			}
			if (c.compareColors(colorTab[i] ,colorTab[1])) {
				c2++;
			}
			if (c.compareColors(colorTab[i], colorTab[2])) {
				c3++;
			}
			if (c.compareColors(colorTab[i], colorTab[3])) {
				c4++;
			}
		}

		int counterTab[4] = { c1, c2, c3, c4 };
		int tmp;
		Color tmpColor;

		for (int i = 0; i < 4; i++) {
			for (int j = i + 1; j < 4; j++) {
				if (counterTab[i] > counterTab[j]) {
					tmp = counterTab[i];
					tmpColor = colorTab[i];

					counterTab[i] = counterTab[j];
					colorTab[i] = colorTab[j];

					counterTab[j] = tmp;
					colorTab[j] = tmpColor;
				}
			}
		}

		for (int i = 0; i < 4; i++) {
			if (!checkIfColorIsWhite(colorTab[i])) {
				c = colorTab[i];
				break;
			}
		}
	}
	return c;
}

void CellsTab::iteration() {
	
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

	/*cout << "\n Copy tab: \n";
	for (int i = 0; i < cellsNumberW + 2; i++) {
		for (int j = 0; j < cellsNumberH + 2; j++) {
			cout << copyTab[i][j].color.r << ' ' << copyTab[i][j].color.g << ' ' << copyTab[i][j].color.b;
			cout << "\t";
		}
		cout << endl;
	}*/

	//w�asciwa iteracja i zliczanie s�siad�w



	for (int i = 1; i < cellsNumberW + 1; i++) {
		for (int j = 1; j < cellsNumberH + 2; j++) {
			if (checkIfColorIsWhite(copyTab[i][j].color)) {
				cellsTab[i-1][j-1].color=setNewCellColor(countNeighbors(i, j), i, j); //TUTEJ!!!!!!!!!!!!!!!!!!!!!
			}
		}
		
	}

	/*for (int i = 1; i < cellsNumberW + 1; i++) {
		for (int j = 1; j < cellsNumberH + 1; j++) {
			cout << copyTab[i][j].color.r << ' ' << copyTab[i][j].color.g << ' ' << copyTab[i][j].color.b;
			cout << "\t";
		}
		cout << endl;
	}*/
	
}

