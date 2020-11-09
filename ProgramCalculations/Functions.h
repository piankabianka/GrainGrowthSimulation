#pragma once
#include <iostream>
#include <vector>

#include "Color.h"

using namespace std;

struct Functions {
	bool checkIfGrainColorExists(Color c, vector<Color>& vec);
	Color generateRandomColor();
	bool checkIfColorIsWhite(Color c);
};