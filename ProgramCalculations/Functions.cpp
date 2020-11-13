#include <iostream>
#include <vector>
#include <ctime>
#include <algorithm> 
#include<iomanip>

#include "Functions.h"
#include "Color.h"


using namespace std;

Functions::Functions() {}

Functions::Functions(int pType, vector<double>& temperatureVector) {
	this->polynomialType = pType;
	this->temperatures = temperatureVector;

	sort(temperatures.begin(), temperatures.end());
	coordinates.push_back(0);
	coordinates.push_back(0.333);
	coordinates.push_back(0.666);
	coordinates.push_back(1);

	calculateCoefficients();
	//cout << calculateXForTemperature(39) << endl;
	
}


double Functions::calculateTemperatureForX(double x) {
	double t=0;

	if (polynomialType == 1) {
		t = linearPolynomial(x);
	}
	if (polynomialType == 2) {
		t = secondPolynomial(x);
	}
	if (polynomialType == 3) {
		t = thirdPolynomial(x);
	}

	return t;
}

double Functions::calculateXForTemperature(double t) {
	double x = 0;

	if (polynomialType == 1) {
		x = getXFromLinear(t);
	}
	if (polynomialType == 2) {
		x = getXFromSecond(t);
	}
	if (polynomialType == 3) {
		x = getXFromThird(t);
	}

	return x;
}

double Functions::getXFromLinear(double t){
	double x = 0;
	x = (t - y0) / y1;
	return x;

}

double Functions::getXFromSecond(double t) {
	double x1 = 0;
	double x2 = 0;

	double d = (0.5 * y2 - y1) * (0.5 * y2 - y1) - 4 * y2 * (y0 - t);

	x1 = (-(0.5 * y2 - y1) - sqrt(d)) / (2 * y2);
	x2= (-(0.5 * y2 - y1) + sqrt(d)) / (2 * y2);

	if (x1 <= 1 && x1 >= 0) {
		return x1;
	}
	else {
		return x2;
	}
}

double Functions::f(double x, double t)
{
	return y0 + y1 * x + y2 * x * (x - 0.333) + y3 * x * (x - 0.333) * (x - 0.666);
}

double Functions::polowienie_przedzialow(double a, double b, double epsilon, double t)
{
	if (f(a,t) == t)return a;
	if (f(b,t) == t)return b;

	double srodek;

	cout << "Wczytano temp: " << t << endl;

	while (b - a > epsilon)
	{
		cout << "szukam rozwiazania na przedziale: " << a << "," << b << endl;
		srodek = (a + b) / 2;

		if (f(srodek,t) == t) 
			return srodek;

		if ( f(srodek,t) > t)
			b = srodek;
		else
			a = srodek;
	}
	return (a + b) / 2;
}




double Functions::getXFromThird(double t) {
	
	double a = 0, b = 1, epsilon = 0.01;

	cout << "Znalezione miejsce zerowe wynosi: ";

	return(polowienie_przedzialow(a, b, epsilon, t));

}

double Functions::linearPolynomial(double x) {
	double t = 0;
	t = y0 + x *y1;
	return t;
}

double Functions::secondPolynomial(double x) {
	double t = 0;
	t = y0 + x * y1 + y2 * x * (x - 0.5);
	return t;
}

double Functions::thirdPolynomial(double x) {
	

	double t = 0;
	t = y0 + y1 * x + y2 * x * (x - 0.333) + y3 * x * (x - 0.333) * (x - 0.666);
	return t;
}

void Functions::calculateCoefficientsForThirdPolynomial() {
	double** coefficientsTab = new double* [3];

	for (int i = 0; i < 3; i++) {
		coefficientsTab[i] = new double[3];
	}

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			coefficientsTab[i][j] = -1.0;
		}
	}

	for (std::vector<int>::size_type i = 0; i < 3; i++) {
		coefficientsTab[i][0] = ((temperatures[i + 1] - temperatures[i]) / (coordinates[i + 1] - coordinates[i]));
	}

	for (std::vector<int>::size_type i = 0; i < 2; i++) {
		coefficientsTab[i][1] = ((coefficientsTab[i + 1][0] - coefficientsTab[i][0]) / (coordinates[i + 2] - coordinates[i]));
	}

	for (std::vector<int>::size_type i = 0; i < 1; i++) {
		coefficientsTab[0][2] = ((coefficientsTab[1][1] - coefficientsTab[0][1]) / (coordinates[i + 3] - coordinates[i]));
		y0 = temperatures[0];
	}


	y1 = coefficientsTab[0][0];
	y2 = coefficientsTab[0][1];
	y3 = coefficientsTab[0][2];
}

void Functions::calculateCoefficientsForLinearPolynomial() {
	for (std::vector<int>::size_type i = 0; i < 3; i++) {
		y0 = temperatures[0];
		y1 = (temperatures[3] - temperatures[0]) / (coordinates[3] - coordinates[0]);
	}
}

void Functions::calculateCoefficientsForSecondPolynomial(){
	double average = 0;
	for (std::vector<int>::size_type i = 0; i < 4; i++) {
		average += temperatures[i];
		y0 = temperatures[0];
	}
	average = average / 4;

	for (std::vector<int>::size_type i = 0; i < 1; i++) {
		y1 = (average - temperatures[0]) / (0.5);
		y2 = ((temperatures[3] - average) / (0.5)) - y1;
	}

	
}

void Functions::calculateCoefficients() {
	if (polynomialType == 3) {
		calculateCoefficientsForThirdPolynomial();
	}
	if (polynomialType == 1) {
		calculateCoefficientsForLinearPolynomial();
	}
	if (polynomialType == 2) {
		calculateCoefficientsForSecondPolynomial();
	}
	
}

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
