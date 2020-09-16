#include "stdafx.h"
#include "GlobalData.h"
#include <iostream>
#include <fstream>
using namespace std;



GlobalData::GlobalData() {
	height = 10;
	width = 30;
	cellSize = 10;
	germsNumber = 20;
	kT = 2;

	nodesNumberH = width + 1;
	nodesNumberW = height + 1;

	totalElementNumber = width * height;
	totalNodesNumber = nodesNumberH * nodesNumberW;
}

void GlobalData::showData() {
	cout << "----------------------------" << endl;
	cout << "GLOBAL DATA: \n" << endl;
	cout << "Height:\t\t\t\t" << height << endl;
	cout << "Width:\t\t\t\t" << width << endl;
	cout << "Number of nodes upright:\t" << nodesNumberH << endl;
	cout << "Number of nodes horizontally:\t" << nodesNumberW << endl;
	cout << "Total number of nodes:\t\t" << totalNodesNumber << endl;
	cout << "Total number of elements:\t" << totalElementNumber << endl;
	cout << "kT:\t\t\t\t" << kT << endl;
	cout << "Germs number:\t\t\t" << germsNumber << endl;
}