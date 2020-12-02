#pragma once
#include "Cell.h"
#include "Color.h"
#include "Functions.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct CellsTab {

	Cell** cellsTab;
	Cell** copyTab;

	vector <double> temperatureVector;
	int cellsNumberW;
	int cellsNumberH;
	int modifiedCells;
	int germsNumber;
	double kT;
	int mcSteps;
	int bc;
	int nghb;
	bool temperatureInfluence = false;
	double t1;
	double t2;
	double t3;
	double t4;
	int polynomialType;

	Functions functions;
	
	

	CellsTab(string path);
	CellsTab();
	void showCellsTab();
	void grainGrowth();

	void singleIteration();
	void doIterations();
	void monteCarloIteration();
	void copyCellTabToCopyTab();
	void clearCopyTab();


	int countNeighbors(int index1, int index2);
	Color setNewCellColor(int nghbCounter, int indexI, int indexJ);


	void calculateEnergy(int i, int j);

	void calculateTemperatureForEveryCell();
	double calculateTemperatureForOneCell(int i, int j);
	double getTemperatureForCell(double ksi, double eta);

	void saveDataToFile();
};