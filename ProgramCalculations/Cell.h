#pragma once
#include <iostream>
#include "Color.h"
using namespace std;

struct Cell {
	Color color;
	int energy;
	int startX;
	int startY;
	bool grain = false;

	Cell();
	void showCell();
	
};