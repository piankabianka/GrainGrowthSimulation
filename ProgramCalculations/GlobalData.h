#pragma once

#pragma once
#include <iostream>
#include <fstream>
#include <string>
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
	int bc;
	int nghb;
	double kT;
	int mcSteps;
	double t1;
	double t2;
	double t3;
	double t4;
	int polynomialType;

	GlobalData(string path);
	void showData();
};