#pragma once
#include "stdafx.h"
#include <iostream>
using namespace std;

struct GlobalData {
	int height;			//height
	int width;			//width
	int nodesNumberH;	//number of nodes upright
	int nodesNumberW;	//number of nodes horizontally
	int totalNodesNumber;
	int totalElementNumber;
	int cellSize;
	GlobalData();
};
