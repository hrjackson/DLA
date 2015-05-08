#include "HL.h"

HL::HL(double alpha,
	double d,
	int numParticles,
	double tol,
	int nLoops,
	double firstLoop,
	double loopSpacing,
	long long seed)
	:numParticles(numParticles), 
	tol(tol), 
	nLoops(nLoops), 
	firstLoop(firstLoop), 
	loopSpacing(loopSpacing)
{
	generator.seed(seed);

	if (nLoops > 0)
	{
		initLoops();
	}
}

HL::~HL()
{
}



void HL::initLoops() {
	for (int i = 0; i < nLoops; ++i) {
		loops.push_back(Loop(1 + firstLoop + i*loopSpacing, tol));
	}
}

vector<Loop> HL::getOuterLoops() {
	return loops;
}