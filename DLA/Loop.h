#pragma once

#include <vector>
#include <map>
#include <complex>
#include <iostream>

#include "SlitMap.h"

using namespace std;

using cpx = complex < double > ;

class Loop {
private:
	// Key = original argument
	// Value = translated position
	map<double, cpx> loop;
	double tol;
	cpx pointUpdate(cpx z, vector<SlitMap> s);
	bool adaptiveUpdate(vector<SlitMap> S, int level);
	double dTheta;
	double radius;
public:
	Loop(double radius, double tol);
	void update(vector<SlitMap> s);
	vector<cpx> getLoop();
};
