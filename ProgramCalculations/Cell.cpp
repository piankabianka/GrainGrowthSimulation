#include "Cell.h"
#include <iostream>


using namespace std;

Cell::Cell() {

	color.r = color.g = color.b = 255;
	startX = 0;
	startY = 0;
	energy = 0;
}

void Cell::showCell() {
	cout << "----------------------------" << endl;
	cout << "CELL: \n" << endl;
	cout << "StartX:\t\t\t\t" << startX << endl;
	cout << "StartY:\t\t\t\t" << startY << endl;
	cout << "Energy:\t\t\t\t" << energy << endl;
	cout << "Color:\t\t" << color.r << "," << color.g << "," << color.b << endl;
}

