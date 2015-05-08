#ifndef __DLA__HL__
#define __DLA__HL__

#include <stdio.h>
#include <complex>
#include <cmath>
#include <random>
#include <map>
#include <vector>
#include <algorithm>
#include <thread>

#include "Map.h"
#include "Loop.h"

using namespace std;

using cpx = complex < double > ;

class HL {
protected:
	/*--- Data ---*/
	double alpha;
	mt19937_64 generator;
	uniform_real_distribution<double> runif;
	vector<double> lengths;
	//vector<Map> maps;
	vector<Loop> loops;
	int numParticles;
	double tol;
	int nLoops;
	double firstLoop;
	double loopSpacing;
	/*--- Virtual Functions ---*/
	void virtual initLengthsAndMaps() = 0;
	/*--- Functions --*/
	void initLoops();
public:
	HL(double alpha,
		double d,
		int numParticles,
		double tol,
		int nLoops,
		double firstLoop,
		double loopSpacing,
		long long seed);
	vector<Loop> getOuterLoops();
	~HL();
};

#endif /* defined(__DLA__HL__) */