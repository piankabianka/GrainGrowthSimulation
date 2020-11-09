#pragma once

#include <iostream>
#include <string>
#include "CellsTab.h"
using namespace std;

struct Calculations {

	string dataPath;
	CellsTab cellsTab;

	Calculations(string path);
	void calculate();
};