#pragma once

#include <complex>

using namespace std;

using cpx = complex<double>;

class Map
{
protected:
	double d;
	double theta;
public:
	Map(double d, double theta);
	cpx virtual derivative(cpx z) = 0;
	cpx operator()(cpx z);
	double getLength();
	double getAngle();
	~Map();
};

