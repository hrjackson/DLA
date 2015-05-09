#pragma once

#include <iostream>

#include "Map.h"

class SlitMap :
	public Map
{
private:
	/*--- Data ---*/
	cpx eiTheta;
	double s;
	double r;
	// So we don't have to keep re-initialising cpx values
	cpx w;
	/*--- Functions ---*/
	//Transform and scale to right half plane:
	cpx DtoH(cpx z);
	// Add slit
	cpx slit(cpx z);
	// Invert back to outside of unit circle
	cpx HtoD(cpx z);
	//void testCase(double real, double im);
public:
	SlitMap(double d, double theta);
	cpx operator()(cpx z);
	cpx derivative(cpx z);
    cpx nDeriv(cpx z);
	//void testMap();
	~SlitMap();
};

