#include <iostream>
#include "Color.h"
#include <cstdlib>
#include <ctime>

using namespace std;

Color::Color() {
	r = 255;
	g = 255;
	b = 255;
}


bool Color::compareColors(Color c1, Color c2) {
	if (c1.r == c2.r
		&& c1.g == c2.g
		&& c1.b == c2.b) {
		return true;
	}
	else
		return false;
}