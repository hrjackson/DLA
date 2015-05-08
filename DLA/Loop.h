#pragma once

#include <vector>
#include <map>
#include <complex>
#include <iostream>

#include "Map.h"

using namespace std;

using cpx = complex < double > ;

class Loop {
private:
	// Key = original argument
	// Value = translated position
	map<double, cpx> loop;
	double tol;
	cpx pointUpdate(cpx z, vector<Map> s);
	bool adaptiveUpdate(vector<Map> S, int level);
	double dTheta;
	double radius;
public:
	Loop(double radius, double tol);
	void update(vector<Map> s);
	vector<cpx> getLoop();
};
