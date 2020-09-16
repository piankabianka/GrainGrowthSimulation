#pragma once
#include <iostream>
using namespace std;

struct Cell {
	int color[3];
	int energy;
	int startX;
	int startY;

	Cell();
	void showCell();
};