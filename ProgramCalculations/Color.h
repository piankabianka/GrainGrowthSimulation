#pragma once
#include <iostream>

using namespace std;

struct Color {
	int r;
	int g;
	int b;

	Color();
	
	bool compareColors(Color c1, Color c2);
};