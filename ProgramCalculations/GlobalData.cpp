
#include "GlobalData.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

GlobalData::GlobalData(string path) {
	fstream file;
	file.open(path);

	if (file.good()) {
		cout << "PLIK OK!" << endl;
		while (!file.eof()) {
			file >> width;
			file >> height;
			file >> germsNumber;
			file >> kT;
			file >> bc;
			file >> nghb;
			file >> t1;
			file >> t2;
			file >> t3;
			file >> t4;
			file >> polynomialType;
		}

	nodesNumberH = width + 1;
	nodesNumberW = height + 1;

	totalElementNumber = width * height;
	totalNodesNumber = nodesNumberH * nodesNumberW;
	}

	else
		cout << "Data error-no such file???" << endl;

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
