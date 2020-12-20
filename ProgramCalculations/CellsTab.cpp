#include "Cell.h"
#include "CellsTab.h"
#include "GlobalData.h"
#include "Color.h"
#include "Calculations.h"
#include "Functions.h"
#include <math.h>

#include <iostream>
#include <fstream>
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


CellsTab::CellsTab() {};

CellsTab::CellsTab(string path) {
	

	GlobalData data(path);

	cellsNumberW = data.height;
	cellsNumberH = data.width;
	germsNumber = data.germsNumber;
	kT = data.kT;
	mcSteps = data.mcSteps;
	bc = data.bc;
	nghb = data.nghb;
	modifiedCells = 0;
	t1 = data.t1;
	t2 = data.t2;
	t3 = data.t3;
	t4 = data.t4;
	polynomialType = data.polynomialType;

	temperatureVector.push_back(t1);
	temperatureVector.push_back(t2);
	temperatureVector.push_back(t3);
	temperatureVector.push_back(t4);

	this->functions = Functions(polynomialType, temperatureVector);
	
	//****************************************************
	//TEMPERATURY
	//****************************************************
	if (t1 != -1 && t2 != -1 && t3 != -1 && t4 != -1) {
		temperatureInfluence = true;
		temperatureTab = new double * [cellsNumberW + 2];

		for (int i = 0; i < cellsNumberW + 2; i++) {
			temperatureTab[i] = new double[cellsNumberH + 2];
		}

		for (int i = 0; i < cellsNumberW+2; i++) {
			for (int j = 0; j < cellsNumberH+2; j++) {
				temperatureTab[i][j] = -1;
			}
		}

		for (int i = 0; i < cellsNumberW; i++) {
			for (int j = 0; j < cellsNumberH; j++) {
				temperatureTab[i + 1][j + 1] = calculateTemperatureForOneCell(i, j);
			}
		}

		/*temperatureTab[0][0] = temperatureTab[cellsNumberW][cellsNumberH];
		temperatureTab[cellsNumberW + 1][cellsNumberH + 1] = temperatureTab[1][1];
		temperatureTab[0][cellsNumberH + 1] = temperatureTab[cellsNumberW][1];
		temperatureTab[cellsNumberW + 1][0] = temperatureTab[1][cellsNumberH];

		for (int i = 1; i < cellsNumberH + 1; i++) {
			temperatureTab[0][i] = temperatureTab[cellsNumberW][i];
			temperatureTab[cellsNumberW + 1][i] = temperatureTab[1][i];
		}
		
		for (int i = 1; i < cellsNumberW + 1; i++) {
			temperatureTab[i][0] = temperatureTab[i ][cellsNumberH ];
			temperatureTab[i][cellsNumberH + 1] = temperatureTab[i][1];
		}*/
	}


	cellsTab = new Cell * [cellsNumberW];

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

void CellsTab::grainGrowth() {
	
	vector <Color> grainsColorVector;
	Color c;
	srand(time(NULL));
	do {
		
		xIndex = (rand() % cellsNumberW);
		yIndex = (rand() % cellsNumberH);
		

		if (!cellsTab[xIndex][yIndex].grain) {
			c = functions.generateRandomColor();
			
			if (!functions.checkIfGrainColorExists(c, grainsColorVector)) {
				cellsTab[xIndex][yIndex].color = c;
				grainsColorVector.push_back(c);
				modifiedNumber++;
				cellsTab[xIndex][yIndex].grain = true;
			}
		}

	} while (modifiedNumber < germsNumber);


}

int CellsTab::countNeighbors(int index1, int index2) {
	int counter = 0;

	if (!functions.checkIfColorIsWhite(copyTab[index1 - 1][index2].color))
		counter++;

	if (!functions.checkIfColorIsWhite(copyTab[index1][index2 + 1].color))
		counter++;

	if (!functions.checkIfColorIsWhite(copyTab[index1 + 1][index2].color))
		counter++;

	if (!functions.checkIfColorIsWhite(copyTab[index1][index2 - 1].color))
		counter++;

	if (nghb == 2) {
		if (!functions.checkIfColorIsWhite(copyTab[index1 - 1][index2 - 1].color))
			counter++;

		if (!functions.checkIfColorIsWhite(copyTab[index1 + 1][index2 + 1].color))
			counter++;

		if (!functions.checkIfColorIsWhite(copyTab[index1 + 1][index2 - 1].color))
			counter++;

		if (!functions.checkIfColorIsWhite(copyTab[index1 - 1][index2 + 1].color))
			counter++;
	}

	return counter;
}

Color CellsTab::setNewCellColor(int nghbCounter, int indexI, int indexJ) {
	Color c;

	if (nghbCounter != 0) {

		int tmp;
		Color tmpColor;

		int nghbNumber;
		if (nghb == 1) nghbNumber = 4;
		if (nghb == 2) nghbNumber = 8;

		Color* colorTab = new Color[nghbNumber];

		colorTab[0] = copyTab[indexI - 1][indexJ].color;
		colorTab[1] = copyTab[indexI][indexJ + 1].color;
		colorTab[2] = copyTab[indexI + 1][indexJ].color;
		colorTab[3] = copyTab[indexI][indexJ - 1].color;

		if (nghbNumber == 8) {
			colorTab[4] = copyTab[indexI - 1][indexJ - 1].color;
			colorTab[5] = copyTab[indexI + 1][indexJ + 1].color;
			colorTab[6] = copyTab[indexI + 1][indexJ - 1].color;
			colorTab[7] = copyTab[indexI - 1][indexJ + 1].color;

		}

		int counters[8] = { 0 };


		for (int i = 0; i < nghbNumber; i++) {
			if (c.compareColors(colorTab[i], colorTab[0])) {
				counters[0];
			}
			if (c.compareColors(colorTab[i], colorTab[1])) {
				counters[1];
			}
			if (c.compareColors(colorTab[i], colorTab[2])) {
				counters[2];
			}
			if (c.compareColors(colorTab[i], colorTab[3])) {
				counters[3];
			}
			if (nghbNumber == 8) {
				if (c.compareColors(colorTab[i], colorTab[4])) {
					counters[4];
				}
				if (c.compareColors(colorTab[i], colorTab[5])) {
					counters[5];;
				}
				if (c.compareColors(colorTab[i], colorTab[6])) {
					counters[6];;
				}
				if (c.compareColors(colorTab[i], colorTab[7])) {
					counters[7];;
				}
			}
		}

		

		int* counterTab = new int[nghbNumber];

		vector <int> countersVector;

		for (int i = 0; i < nghbNumber; i++) {
			countersVector.push_back(counters[i]);
		}


		for (std::vector<int>::size_type i = 0; i != countersVector.size(); i++) {
			for (std::vector<int>::size_type j = i + 1; j != countersVector.size(); j++) {
				if (counterTab[i] > counterTab[j]) {
					tmp = countersVector[i];
					tmpColor = colorTab[i];

					countersVector[i] = countersVector[j];
					colorTab[i] = colorTab[j];

					countersVector[j] = tmp;
					colorTab[j] = tmpColor;
				}
			}
		}

		for (int i = 0; i < nghbNumber; i++) {
			if (!functions.checkIfColorIsWhite(colorTab[i])) {
				c = colorTab[i];
				modifiedNumber++;
				break;
			}
		}
	}

	return c;
}

void CellsTab::clearCopyTab() {
	for (int i = 0; i < cellsNumberW + 2; i++) {
		for (int j = 0; j < cellsNumberH + 2; j++) {
			copyTab[i][j] = Cell();
		}
	}
}

void CellsTab::copyCellTabToCopyTab() {
	//srodek tablicy
	for (int i = 0; i < cellsNumberW; i++) {
		for (int j = 0; j < cellsNumberH; j++) {
			copyTab[i + 1][j + 1] = cellsTab[i][j];
		}
	}

	if (bc == 1) {
		//rogi

		copyTab[0][0] = cellsTab[cellsNumberW - 1][cellsNumberH - 1];
		copyTab[cellsNumberW + 1][cellsNumberH + 1] = cellsTab[0][0];
		copyTab[0][cellsNumberH + 1] = cellsTab[cellsNumberW - 1][0];
		copyTab[cellsNumberW + 1][0] = cellsTab[0][cellsNumberH - 1];

		//brzegi

		for (int i = 1; i < cellsNumberH + 1; i++) {
			copyTab[0][i] = cellsTab[cellsNumberW - 1][i - 1];
			copyTab[cellsNumberW + 1][i] = cellsTab[0][i - 1];
		}

		for (int i = 1; i < cellsNumberW + 1; i++) {
			copyTab[i][0] = cellsTab[i - 1][cellsNumberH - 1];
			copyTab[i][cellsNumberH + 1] = cellsTab[i - 1][0];
		}
	}

	/*if(bc==2){
		//rogi

		copyTab[0][0] = new Cell();
		copyTab[cellsNumberW + 1][cellsNumberH + 1] = new Cell();
		copyTab[0][cellsNumberH + 1] = new Cell();
		copyTab[cellsNumberW + 1][0] = new Cell();

		//brzegi

		for (int i = 1; i < cellsNumberH + 1; i++) {
			copyTab[0][i] = new Cell();
			copyTab[cellsNumberW + 1][i] = new Cell();
		}

		for (int i = 1; i < cellsNumberW + 1; i++) {
			copyTab[i][0] = new Cell();
			copyTab[i][cellsNumberH + 1] = new Cell();
		}
	}*/


}

void CellsTab::singleIteration() {

	copyCellTabToCopyTab();

	for (int i = 1; i < cellsNumberW + 1; i++) {
		for (int j = 1; j < cellsNumberH + 1; j++) {
			if (functions.checkIfColorIsWhite(copyTab[i][j].color)) {
				cellsTab[i - 1][j - 1].color = setNewCellColor(countNeighbors(i, j), i, j);

			}
		}
	}

	//saveDataToFile();
}

void CellsTab::doIterations() {
	do {
		singleIteration();

	} while (modifiedNumber < (cellsNumberW * cellsNumberH));
}

void CellsTab::calculateEnergy(int i, int j) {

	Color c = copyTab[i + 1][j + 1].color;
	Color colorRandom;
	int energy = 0;
	int energyRandom = 0;

	double temperature = 0;
	double tempRandom = 0;

	int counter = 0;
	vector <Color> colorVector;
	vector<double> tempVector;

	int nghbNumber;
	if (nghb == 1) nghbNumber = 4;
	if (nghb == 2) nghbNumber = 8;

	Color* colorTab = new Color[nghbNumber];
	int indexI = i+1;
	int indexJ = j + 1;

	colorTab[0] = copyTab[indexI - 1][indexJ].color;
	colorTab[1] = copyTab[indexI][indexJ + 1].color;
	colorTab[2] = copyTab[indexI + 1][indexJ].color;
	colorTab[3] = copyTab[indexI][indexJ - 1].color;

	if (nghbNumber == 8) {
		colorTab[4] = copyTab[indexI - 1][indexJ - 1].color;
		colorTab[5] = copyTab[indexI + 1][indexJ + 1].color;
		colorTab[6] = copyTab[indexI + 1][indexJ - 1].color;
		colorTab[7] = copyTab[indexI - 1][indexJ + 1].color;

	}

	for (int i = 0; i < nghbNumber; i++) {
		if (!c.compareColors(c, colorTab[i]) && !functions.checkIfColorIsWhite(colorTab[i])) {
			energy++;
			colorVector.push_back(colorTab[i]);
		}
	}

	//TUTAJ!!!!!!

	if (temperatureInfluence) {
		//tempVector = { calculateTemperatureForOneCell(i + 1,j + 2),calculateTemperatureForOneCell(i + 2,j + 3) ,calculateTemperatureForOneCell(i + 3,j + 2) ,calculateTemperatureForOneCell(i + 2,j + 1) };
		//temperature = calculateTemperatureForOneCell(i + 2, j + 2);
		tempVector = { temperatureTab[indexI-1][indexJ],temperatureTab[indexI +1][indexJ], temperatureTab[indexI][indexJ -1], temperatureTab[indexI][indexJ +1] };
		temperature = calculateTemperatureForOneCell(i, j);
	}



	if (colorVector.size() != 0) {

		srand(time(NULL));
		colorRandom = colorVector[(rand() % colorVector.size())];

		for (int i = 0; i < 4; i++) {
			if (!c.compareColors(colorRandom, colorTab[i])) {
				energyRandom++;
			}

		}

		
		if (temperatureInfluence == true) {

			double valueT = 0;
			double valueTRandom = 0;

			tempRandom = tempVector[(rand() % tempVector.size())];

			valueT = functions.calculateXForTemperature(temperature);
			valueTRandom = functions.calculateXForTemperature(tempRandom);


			if (valueTRandom * energyRandom < energy * valueT) {

				copyTab[i + 1][j + 1].color = colorRandom;
				copyTab[i + 1][j + 1].energy = energyRandom;
			}
			else {

				double calculation = exp(-(energyRandom - energy) / kT);
				double probability1 = (double)(rand() % 100) / 100;

				if (valueTRandom * probability1 <= calculation * valueT) {

					copyTab[i + 1][j + 1].color = colorRandom;
					copyTab[i + 1][j + 1].energy = energyRandom;
				}

			}
		}
		if (temperatureInfluence == false) {
			

			if (energyRandom < energy) {

				copyTab[i + 1][j + 1].color = colorRandom;
				copyTab[i + 1][j + 1].energy = energyRandom;
				
			}
			else {

				double calculation = exp(-(energyRandom - energy) / kT);
				double probability1 = (double)(rand() % 100) / 100;

				if (probability1 <= calculation) {

					copyTab[i + 1][j + 1].color = colorRandom;
					copyTab[i + 1][j + 1].energy = energyRandom;
					
				}

			}
		}

	}

}

void CellsTab::monteCarloIteration() {

	copyCellTabToCopyTab();

	vector<pair<int, int> > cellsVector;

	for (int i = 0; i < cellsNumberW; i++) {
		for (int j = 0; j < cellsNumberH; j++) {
			pair<int, int> index(i, j);
			cellsVector.push_back(index);
		}
	}

	auto it = cellsVector.begin();
	srand(time(NULL));

	int vectorIndex = 0;
	auto iterator = cellsVector.begin();


	do {
		vectorIndex = (rand() % cellsVector.size());
		iterator = cellsVector.begin() + vectorIndex;

		calculateEnergy(cellsVector[vectorIndex].first, cellsVector[vectorIndex].second);


		cellsVector.erase(iterator);
		vectorIndex = 0;


	} while (cellsVector.size() > 0);

	for (int i = 0; i < cellsNumberW; i++) {
		for (int j = 0; j < cellsNumberH; j++) {
			cellsTab[i][j] = copyTab[i + 1][j + 1];

		}
	}

}

double CellsTab::getTemperatureForCell(double ksi, double eta) {

	double t = 0;

	t = (1 - ksi) * (1 - eta) * t1 / 4;
	t += (1 - ksi) * (1 + eta) * t4 / 4;
	t += (1 + ksi) * (1 + eta) * t3 / 4;
	t += (1 + ksi) * (1 - eta) * t2 / 4;


	return t;

}

void CellsTab::calculateTemperatureForEveryCell() {
	double ksi;
	double eta;

	for (int i = 1; i < cellsNumberW + 1; i++) {
		for (int j = 1; j < cellsNumberH + 1; j++) {
			ksi = (2 * (double)j - 1 - cellsNumberH) / (cellsNumberH - 1);
			eta = (2 * (double)i - 1 - cellsNumberW) / (cellsNumberW - 1);

			cout << getTemperatureForCell(ksi, eta) << "\t";
		}
		cout << endl;
	}

}

double CellsTab::calculateTemperatureForOneCell(int i, int j) {
	double ksi;
	double eta;
	int jIndex=j+1;
	int iIndex=i+1;

	ksi = (2 * (double)jIndex - 1 - cellsNumberH) / (cellsNumberH - 1);
	eta = (2 * (double)iIndex - 1 - cellsNumberW) / (cellsNumberW - 1);

	return getTemperatureForCell(ksi, eta);
}

void CellsTab::saveDataToFile() {
	ofstream saveData("calculatedData.csv", ios::app);

	saveData << "\n";
	for (int i = 0; i < cellsNumberW; i++) {
		for (int j = 0; j < cellsNumberH; j++) {
			saveData << cellsTab[i][j].color.r << ",";
			saveData << cellsTab[i][j].color.g << ",";
			saveData << cellsTab[i][j].color.b << ";";
		}
	}

	saveData.close();
}

void CellsTab::checkData() {
	for (int i = 0; i < cellsNumberW; i++) {
		for (int j = 0; j < cellsNumberH; j++) {
			
			cout << "komorka nr " << i << "," << j;
			cout<<" kolor "<< cellsTab[i][j].color.r << ',' << cellsTab[i][j].color.g << ',' << cellsTab[i][j].color.b;
			cout << " temperatura " << calculateTemperatureForOneCell(i, j);
			cout << "\n";
		}
		cout << endl;
	}
}