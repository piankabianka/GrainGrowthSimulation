#pragma once
#include <iostream>
#include <vector>

#include "Color.h"

using namespace std;

struct Functions {

	int polynomialType;
	vector<double> temperatures;
	vector<double> coordinates;
	double q = 0;
	double y0 = 0;
	double y1 = 0;
	double y2 = 0;
	double y3 = 0;

	bool checkIfGrainColorExists(Color c, vector<Color>& vec);
	Color generateRandomColor();
	bool checkIfColorIsWhite(Color c);

	double linearPolynomial(double x);
	double secondPolynomial(double x);
	double thirdPolynomial(double x);

	double calculateTemperatureForX(double x);
	double calculateXForTemperature(double t);

	double getXFromLinear(double t);
	double getXFromSecond(double t);
	double getXFromThird(double t);
	double f(double x, double t);
	double polowienie_przedzialow(double a, double b, double epsilon, double t);

	void calculateCoefficients();
	void calculateCoefficientsForLinearPolynomial();
	void calculateCoefficientsForThirdPolynomial();
	void calculateCoefficientsForSecondPolynomial();

	Functions();
	Functions(int pType, vector<double>& temperatureVector);

};