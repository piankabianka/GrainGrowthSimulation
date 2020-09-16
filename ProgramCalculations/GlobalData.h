#pragma once

#pragma once
#include <iostream>
#include <fstream>
using namespace std;

struct GlobalData {
	int height;			//height
	int width;			//width
	int nodesNumberH;	//number of nodes upright
	int nodesNumberW;	//number of nodes horizontally
	int totalNodesNumber;
	int totalElementNumber;
	int cellSize;
	int germsNumber;
	int kT;
	GlobalData();
	void showData();
};