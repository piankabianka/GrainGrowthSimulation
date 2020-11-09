#include <iostream>
#include <vector>
#include <ctime>

#include "Functions.h"
#include "Color.h"


using namespace std;

bool Functions::checkIfGrainColorExists(Color c, vector<Color>& vec) {
	bool condition = false;

	for (std::vector<int>::size_type i = 0; i != vec.size(); i++) {
		if (c.compareColors(vec[i], c)) {
			condition = true;
			break;
		}
	}
	return condition;
}
Color Functions::generateRandomColor() {
	Color c;
	srand(time(NULL));
	c.r = (rand() % 255);
	c.g = (rand() % 255);
	c.b = (rand() % 255);
	return c;
}
bool Functions::checkIfColorIsWhite(Color c) {
	if (c.r == 255 && c.g == 255 && c.b == 255) {
		return true;
	}
	else {
		return false;
	}
}