#pragma once

#include <stdio.h>
#include <complex>
#include <cmath>
#include <random>
#include <map>
#include <vector>
#include <algorithm>

#include "SlitMap.h"

using namespace std;

using cpx = complex<double>;

class Particle {
private:
	// Key = original abs. value
	// Value = translated position
	map<double, cpx> line;
	double length;
	double tol;
	double theta;
	cpx eiTheta;
	// Initialise the line
	void initLine();
	cpx pointUpdate(cpx z, vector<SlitMap> s);
	bool adaptiveUpdate(vector<SlitMap> s, int level);
public:
	Particle(double length, double tol, double theta);
	void update(vector<SlitMap> s);
	vector<cpx> getLine();
	~Particle();
};