
#include "GlobalData.h"
#include <iostream>
#include <fstream>
using namespace std;



GlobalData::GlobalData() {
	fstream file;
	file.open("data.txt");

	if (file.good()) {
		while (!file.eof()) {
			file >> width;
			file >> height;
			file >> germsNumber;
			file >> kT;
		}

	nodesNumberH = width + 1;
	nodesNumberW = height + 1;

	totalElementNumber = width * height;
	totalNodesNumber = nodesNumberH * nodesNumberW;
	}

	else
		cout << "Data error" << endl;

	file.close();
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
