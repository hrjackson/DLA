#pragma once
#include "Map.h"

class SlitMap :
	public Map
{
private:
	cpx eiTheta;
	double s;
	double r;
	// So we don't have to keep re-initialising cpx values
	cpx w;
public:
	SlitMap(double d, double theta);
	cpx operator()(cpx z);
	cpx derivative(cpx z);
	~SlitMap();
};

